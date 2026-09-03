#include "LQRController.hpp"

#include <stdexcept>
#include <algorithm>

static void ensure_size_or_throw(const std::vector<float>& v, int expected, const char* name) {
    if (static_cast<int>(v.size()) != expected) {
        throw std::runtime_error(std::string(name) + " size mismatch: expected " +
                                 std::to_string(expected) + ", got " + std::to_string(v.size()));
    }
}

LQRController::LQRController(int nStates, int nInputs, int nOutputs)
    : _n(nStates), _m(nInputs), _p(nOutputs),
      _A(linalg::zeros(nStates, nStates)),
      _B(linalg::zeros(nStates, nInputs)),
      _Q(linalg::identity(nStates)),
      _R(linalg::identity(nInputs)),
      _x(static_cast<size_t>(nStates), 0.0f),
      _y(static_cast<size_t>(nOutputs), 0.0f),
      _r(static_cast<size_t>(nOutputs), 0.0f),
      _u(static_cast<size_t>(nInputs), 0.0f),
      _K(linalg::zeros(nInputs, nStates))
{
    if (_n <= 0) throw std::runtime_error("nStates must be > 0");
    if (_m <= 0) throw std::runtime_error("nInputs must be > 0");
    if (_p <= 0) throw std::runtime_error("nOutputs must be > 0");
}

void LQRController::setSystemMatrices(const std::vector<float>& A, const std::vector<float>& B) {
    ensure_size_or_throw(A, _n * _n, "A");
    ensure_size_or_throw(B, _n * _m, "B");

    for (int i = 0; i < _n * _n; ++i) {
        _A[static_cast<size_t>(i)] = static_cast<double>(A[static_cast<size_t>(i)]);
    }
    for (int i = 0; i < _n * _m; ++i) {
        _B[static_cast<size_t>(i)] = static_cast<double>(B[static_cast<size_t>(i)]);
    }

    _dirtyGain = true;
}

void LQRController::setCostMatrices(const std::vector<float>& Q, const std::vector<float>& R) {
    ensure_size_or_throw(Q, _n * _n, "Q");
    ensure_size_or_throw(R, _m * _m, "R");

    for (int i = 0; i < _n * _n; ++i) {
        _Q[static_cast<size_t>(i)] = static_cast<double>(Q[static_cast<size_t>(i)]);
    }
    for (int i = 0; i < _m * _m; ++i) {
        _R[static_cast<size_t>(i)] = static_cast<double>(R[static_cast<size_t>(i)]);
    }

    _dirtyGain = true;
}

void LQRController::setRiccatiOptions(int maxIterations, double tolerance) {
    if (maxIterations <= 0) throw std::runtime_error("maxIterations must be > 0");
    if (tolerance <= 0.0) throw std::runtime_error("tolerance must be > 0");

    _maxIter = maxIterations;
    _tol = tolerance;
    _dirtyGain = true;
}

void LQRController::setTarget(const std::vector<float>& r) {
    ensure_size_or_throw(r, _p, "target r");
    _r = r; 
}

void LQRController::setCurrentOutput(const std::vector<float>& y) {
    ensure_size_or_throw(y, _p, "output y");
    _y = y; 
}

void LQRController::setCurrentState(const std::vector<float>& x) {
    ensure_size_or_throw(x, _n, "state x");
    _x = x;
}

void LQRController::reset() {
    std::fill(_x.begin(), _x.end(), 0.0f);
    std::fill(_y.begin(), _y.end(), 0.0f);
    std::fill(_r.begin(), _r.end(), 0.0f);
    std::fill(_u.begin(), _u.end(), 0.0f);
}

void LQRController::recomputeGainOrThrow() {
    const int qExpected = _n * _n;
    if (static_cast<int>(_Q.size()) != qExpected) {
        throw std::runtime_error("Q size mismatch: expected " + std::to_string(qExpected) +
                                 " (" + std::to_string(_n) + "x" + std::to_string(_n) + ") but got " +
                                 std::to_string(_Q.size()));
    }

    const int rExpected = _m * _m;
    if (static_cast<int>(_R.size()) != rExpected) {
        throw std::runtime_error("R size mismatch: expected " + std::to_string(rExpected) +
                                 " (" + std::to_string(_m) + "x" + std::to_string(_m) + ") but got " +
                                 std::to_string(_R.size()));
    }

    const linalg::Mat P = solveDARE(_A, _n, _B, _m, _Q, _R, _maxIter, _tol);
    _K = computeK(_A, _n, _B, _m, P, _R);

    _dirtyGain = false;
}

std::vector<float> LQRController::compute(float /*dt*/) {
    if (_dirtyGain) {
        recomputeGainOrThrow();
    }

    // u = -K x
    linalg::Vec xvec;
    xvec.resize(static_cast<size_t>(_n));
    for (int i = 0; i < _n; ++i) {
        xvec[static_cast<size_t>(i)] = static_cast<double>(_x[static_cast<size_t>(i)]);
    }

    const linalg::Vec uvec = linalg::mul(_K, _m, _n, xvec);

    for (int i = 0; i < _m; ++i) {
        _u[static_cast<size_t>(i)] = static_cast<float>(-uvec[static_cast<size_t>(i)]);
    }

    return _u;
}

linalg::Mat LQRController::solveDARE(const linalg::Mat& A, int n,
                                     const linalg::Mat& B, int m,
                                     const linalg::Mat& Q, const linalg::Mat& R,
                                     int maxIter, double tol) {
    // Iterative solution:
    // P_{k+1} = A' P A - A' P B (R + B' P B)^(-1) B' P A + Q
    linalg::Mat P = Q;

    const linalg::Mat At = linalg::transpose(A, n, n);
    const linalg::Mat Bt = linalg::transpose(B, n, m);

    for (int it = 0; it < maxIter; ++it) {
        const linalg::Mat PB    = linalg::mul(P, n, n, B, n, m);
        const linalg::Mat BtPB  = linalg::mul(Bt, m, n, PB, n, m);
        const linalg::Mat S     = linalg::add(R, BtPB);
        const linalg::Mat Sinv  = linalg::inv(S, m);

        const linalg::Mat PA    = linalg::mul(P, n, n, A, n, n);
        const linalg::Mat BtPA  = linalg::mul(Bt, m, n, PA, n, n);

        const linalg::Mat term  = linalg::mul(PB, n, m, Sinv, m, m);
        const linalg::Mat term2 = linalg::mul(term, n, m, BtPA, m, n);

        const linalg::Mat AtPA  = linalg::mul(At, n, n, PA, n, n);
        const linalg::Mat nextP = linalg::add(linalg::sub(AtPA, term2), Q);

        const double diff = linalg::normF(linalg::sub(nextP, P));
        P = nextP;

        if (diff < tol) break;
    }

    return P;
}

linalg::Mat LQRController::computeK(const linalg::Mat& A, int n,
                                    const linalg::Mat& B, int m,
                                    const linalg::Mat& P, const linalg::Mat& R) {
    // K = (R + B' P B)^(-1) * (B' P A)
    const linalg::Mat Bt   = linalg::transpose(B, n, m);
    const linalg::Mat PB   = linalg::mul(P, n, n, B, n, m);
    const linalg::Mat BtPB = linalg::mul(Bt, m, n, PB, n, m);
    const linalg::Mat S    = linalg::add(R, BtPB);
    const linalg::Mat Sinv = linalg::inv(S, m);

    const linalg::Mat PA   = linalg::mul(P, n, n, A, n, n);
    const linalg::Mat BtPA = linalg::mul(Bt, m, n, PA, n, n);

    return linalg::mul(Sinv, m, m, BtPA, m, n);
}