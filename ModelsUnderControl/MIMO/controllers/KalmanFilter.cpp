#include "KalmanFilter.hpp"
#include <iostream>

KalmanFilter::KalmanFilter(const int nStates, const int nInputs, const int nOutputs)
    : _n(nStates), _c(nInputs), _m(nOutputs),
      _F(linalg::identity(_n)),
      _B(linalg::zeros(_n, _c)),
      _H(linalg::zeros(_m, _n)),
      _Q(linalg::identity(_n)),
      _R(linalg::identity(_m)),
      _x0(linalg::zeros(_n, 1)),
      _x(_x0),
      _P0(linalg::identity(_n)),
      _P(_P0),
      _K(linalg::zeros(_n, _m))
{
    if (_n <= 0) throw std::runtime_error("nStates must be > 0");
    if (_m <= 0) throw std::runtime_error("nOutputs must be > 0");
    if (_c <= 0) throw std::runtime_error("nInputs must be > 0");

    // FIX 1 : allouer tous les buffers std::vector à la bonne taille
    // Sans ce resize(), toute écriture dans compute() via operator[]
    // sur un vecteur vide est un undefined behavior → segfault
    _x_vec.resize(static_cast<size_t>(_n), 0.0f);
    _u_vec.resize(static_cast<size_t>(_c), 0.0f);
    _z_vec.resize(static_cast<size_t>(_m), 0.0f);
    _ctrl_vec.resize(static_cast<size_t>(_n), 0.0f);
}

std::vector<float> KalmanFilter::compute(float /*dt*/) {

    linalg::Vec u(static_cast<size_t>(_c));
    for (int i = 0; i < _c; ++i)
        u[static_cast<size_t>(i)] = static_cast<double>(_u_vec[static_cast<size_t>(i)]);

    linalg::Vec z(static_cast<size_t>(_m));
    for (int i = 0; i < _m; ++i)
        z[static_cast<size_t>(i)] = static_cast<double>(_z_vec[static_cast<size_t>(i)]);

    // Transposées réutilisées plusieurs fois
    const linalg::Mat Ft = linalg::transpose(_F, _n, _n);
    const linalg::Mat Ht = linalg::transpose(_H, _m, _n); 

    // Etape 1 : Prédiction
    // x̂⁻ = F·x̂ + B·u
    const linalg::Mat Fx = linalg::mul(_F, _n, _n, _x, _n, 1);
    const linalg::Mat Bu = linalg::mul(_B, _n, _c, u);
    const linalg::Mat x_prior = linalg::add(Fx, Bu);

    // P⁻ = F·P·Fᵀ + Q
    const linalg::Mat FP = linalg::mul(_F, _n, _n, _P, _n, _n);
    const linalg::Mat P_prior = linalg::add(
        linalg::mul(FP, _n, _n, Ft, _n, _n), _Q);

    // Etape 2 : Gain de Kalman
    // S = H·P⁻·Hᵀ + R
    const linalg::Mat HP_prior = linalg::mul(_H, _m, _n, P_prior, _n, _n);
    const linalg::Mat HPHt = linalg::mul(HP_prior, _m, _n, Ht, _n, _m);
    const linalg::Mat S = linalg::add(HPHt, _R);

    // K = P⁻·Hᵀ·S⁻¹
    const linalg::Mat P_Ht = linalg::mul(P_prior, _n, _n, Ht, _n, _m);
    _K = linalg::mul(P_Ht, _n, _m, linalg::inv(S, _m), _m, _m);

    // Etape 3 : Mise à jour de l'état
    // innovation = z - H·x̂⁻
    const linalg::Mat Hx_prior = linalg::mul(_H, _m, _n, x_prior, _n, 1);
    const linalg::Mat innovation = linalg::sub(z, Hx_prior);

    // x̂ = x̂⁻ + K·innovation
    _x = linalg::add(x_prior, linalg::mul(_K, _n, _m, innovation, _m, 1));

    // Etape 4 : Mise à jour de P (formule de Joseph)
    // I_KH = I − K·H
    const linalg::Mat KH = linalg::mul(_K, _n, _m, _H, _m, _n);
    const linalg::Mat I_KH = linalg::sub(linalg::identity(_n), KH);

    // P = (I−KH)·P⁻·(I−KH)ᵀ + K·R·Kᵀ
    const linalg::Mat I_KHt = linalg::transpose(I_KH, _n, _n);
    const linalg::Mat I_KHP_prior = linalg::mul(I_KH, _n, _n, P_prior, _n, _n);
    const linalg::Mat Kt = linalg::transpose(_K, _n, _m);
    const linalg::Mat KR = linalg::mul(_K, _n, _m, _R, _m, _m);

    _P = linalg::add(
        linalg::mul(I_KHP_prior, _n, _n, I_KHt, _n, _n),
        linalg::mul(KR, _n, _m, Kt, _m, _n));

    // Mise à jour des buffers interface
    for (int i = 0; i < _n; ++i) {
        const float val = static_cast<float>(_x[static_cast<size_t>(i)]);
        _x_vec[static_cast<size_t>(i)]    = val;
        _ctrl_vec[static_cast<size_t>(i)] = val;
    }

    return _ctrl_vec;
}