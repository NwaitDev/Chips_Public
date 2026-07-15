#include "LQGController.hpp"

#include <stdexcept>

LQGController::LQGController(int nStates, int nInputs, int nOutputs)
    : _n(nStates), _m(nInputs), _p(nOutputs),
      _kf(nStates, nInputs, nOutputs),
      _lqr(nStates, nInputs, nOutputs),
      _r(static_cast<size_t>(nOutputs), 0.0f),
      _y(static_cast<size_t>(nOutputs), 0.0f),
      _x_hat(static_cast<size_t>(nStates), 0.0f),
      _u(static_cast<size_t>(nInputs), 0.0f),
      _last_applied_u(static_cast<size_t>(nInputs), 0.0f)
{
    if (_n <= 0 || _m <= 0 || _p <= 0)
        throw std::runtime_error("LQG: invalid dimensions");
}

void LQGController::setSystemMatrices(const std::vector<float>& A, const std::vector<float>& B) {
    // forward to LQR and Kalman (transition + command)
    _lqr.setSystemMatrices(A, B);
    _kf.setTransitionMatrix(A);
    _kf.setCommandMatrix(B);
}

void LQGController::setObservationMatrix(const std::vector<float>& H) {
    _kf.setObservationMatrix(H);
}

void LQGController::setEstimatorNoise(const std::vector<float>& Q_proc, const std::vector<float>& R_meas) {
    _kf.setNoiseMatrices(Q_proc, R_meas);
}

void LQGController::setLQRCost(const std::vector<float>& Ql, const std::vector<float>& Rl) {
    _lqr.setCostMatrices(Ql, Rl);
}

void LQGController::setTarget(const std::vector<float>& r) {
    if (static_cast<int>(r.size()) != _p) throw std::invalid_argument("LQG:setTarget size");
    _r = r;
    _lqr.setTarget(r);
}

void LQGController::setCurrentOutput(const std::vector<float>& y) {
    if (static_cast<int>(y.size()) != _p) throw std::invalid_argument("LQG:setCurrentOutput size");
    _y = y;
    _kf.setCurrentOutput(y);
}

void LQGController::setCurrentState(const std::vector<float>& x) {
    if (static_cast<int>(x.size()) != _n) throw std::invalid_argument("LQG:setCurrentState size");
    _x_hat = x;
    _kf.setCurrentState(x);
    _lqr.setCurrentState(x);
}

std::vector<float> LQGController::compute(float dt) {
    // Ensure estimator knows last applied control (assumed applied to plant)
    _kf.setControl(_last_applied_u);

    // Update state estimate
    const std::vector<float> est = _kf.compute(dt);
    if (static_cast<int>(est.size()) != _n) throw std::runtime_error("LQG: estimator returned bad state size");
    _x_hat = est;

    // Give state to LQR and compute control
    _lqr.setCurrentState(_x_hat);
    const std::vector<float> ucmd = _lqr.compute(dt);
    if (static_cast<int>(ucmd.size()) != _m) throw std::runtime_error("LQG: LQR returned bad control size");

    _u = ucmd;
    // remember applied control for next predict step
    _last_applied_u = _u;
    return _u;
}

void LQGController::reset() {
    _kf.reset();
    _lqr.reset();
    std::fill(_r.begin(), _r.end(), 0.0f);
    std::fill(_y.begin(), _y.end(), 0.0f);
    std::fill(_x_hat.begin(), _x_hat.end(), 0.0f);
    std::fill(_u.begin(), _u.end(), 0.0f);
    std::fill(_last_applied_u.begin(), _last_applied_u.end(), 0.0f);
}

std::vector<float> LQGController::getEstimatorCovariance() const {
    return _kf.getCovariance();
}

std::vector<float> LQGController::getEstimatorKalmanGain() const {
    return _kf.getKalmanGain();
}

std::vector<float> LQGController::getEstimatorSigma() const {
    return _kf.getUncertainy();
}
