#ifndef KALMAN_FILTER_CONTROLLER_HPP
#define KALMAN_FILTER_CONTROLLER_HPP

#include "../IControllerMIMO.hpp"
#include "../utils/LinearAlgebra.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief Filtre de Kalman discret implémentant IControllerMIMO
 *
 * Modèle d'état discret :
 *  x(k) = F(dt) * x(k-1) + B * u(k-1) + w(k)    w ~ N(0, Q)
 *  z(k) = H * x(k)       + v(k)                  v ~ N(0, R)
 *
 * Dimensions :
 *  n = nStates  : taille de l'état x
 *  c = nInputs  : taille de la commande u
 *  m = nOutputs : taille de la mesure z
 *
 * Matrices :
 *  F  (n x n) : transition d'état         — init : identité
 *  B  (n x c) : commande                  — init : zéros
 *  H  (m x n) : observation               — init : identité tronquée (min(m,n))
 *  Q  (n x n) : covariance bruit processus — init : identité
 *  R  (m x m) : covariance bruit mesure   — init : identité
 *  P  (n x n) : covariance erreur courante — init : identité
 *  K  (n x m) : gain de Kalman            — init : zéros
 */
class KalmanFilter : public IControllerMIMO {

public:

    /**
     * @brief Construit le filtre et alloue tous les buffers internes.
     *
     * @param nStates  Dimension de l'état x        (n > 0)
     * @param nInputs  Dimension de la commande u   (c > 0)
     * @param nOutputs Dimension de la mesure z     (m > 0)
     * @throws std::runtime_error si une dimension est invalide
     */
    KalmanFilter(const int nStates, const int nInputs, const int nOutputs);

    ~KalmanFilter() override = default;

    // ── Dimensions 
    int getStateSize()  const override { return _n; }
    int getInputSize()  const override { return _c; }
    int getOutputSize() const override { return _m; }

    // ── Getters interface 
    const std::vector<float>& getTarget()        const override { return _u_vec;    }
    const std::vector<float>& getCurrentOutput() const override { return _z_vec;    }
    const std::vector<float>& getCurrentState()  const override { return _x_vec;    }
    const std::vector<float>& getControl() const override { return _ctrl_vec; }

    // ── Setters interface 
    void setTarget(const std::vector<float>& r) override {
        checkSize(r, _c, "setTarget/u");
        for(int i = 0; i < _c; i++){
            _u_vec[static_cast<size_t>(i)] = static_cast<double>(r[static_cast<size_t>(i)]);
        }
    }

    void setCurrentOutput(const std::vector<float>& y) override {
        checkSize(y, _m, "setCurrentOutput/z");
        for(int i = 0; i < _m; i++){
            _z_vec[static_cast<size_t>(i)] = static_cast<double>(y[static_cast<size_t>(i)]);
        }
    }

    void setCurrentState(const std::vector<float>& x) override {
        checkSize(x, _n, "setCurrentState");
        for(int i = 0; i < _n; ++i){
            _x_vec[static_cast<size_t>(i)] = static_cast<double>(x[static_cast<size_t>(i)]);
        }
    }

    // Calcul principal 
    /**
     * @brief Exécute un cycle complet predict + update.
     *
     *  1. Prédiction  : x̂⁻ = F·x̂ + B·u        P⁻ = F·P·Fᵀ + Q
     *  2. Gain        : K   = P⁻·Hᵀ·(H·P⁻·Hᵀ + R)⁻¹
     *  3. État        : x̂   = x̂⁻ + K·(z − H·x̂⁻)
     *  4. Covariance  : P   = (I−KH)·P⁻·(I−KH)ᵀ + K·R·Kᵀ  (Joseph)
     *
     * @param dt  Pas de temps — ignoré si F est déjà discret.
     * @return    État estimé x̂(k|k) sous forme std::vector<float> (taille n).
     */
    std::vector<float> compute(float dt) override;

    // Reset
    void reset() override {
        _x = _x0;
        _P = _P0;
        _K = linalg::zeros(_n, _m);
        std::fill(_u_vec.begin(),    _u_vec.end(),    0.0f);
        std::fill(_z_vec.begin(),    _z_vec.end(),    0.0f);
        std::fill(_x_vec.begin(),    _x_vec.end(),    0.0f);
        std::fill(_ctrl_vec.begin(), _ctrl_vec.end(), 0.0f);
    }

    // API propre au filtre de Kalman

    /**
     * @brief Covariance d'erreur P aplatie en row-major (taille n*n).
     */
    std::vector<float> getCovariance() const {
        std::vector<float> result(static_cast<size_t>(_n * _n));
        for (int i = 0; i < _n * _n; ++i)
            result[static_cast<size_t>(i)] = static_cast<float>(_P[static_cast<size_t>(i)]);
        return result;
    }

    /**
     * @brief Gain de Kalman K aplati en row-major (taille n*m).
     */
    std::vector<float> getKalmanGain() const {
        std::vector<float> result(static_cast<size_t>(_n * _m));
        for (int i = 0; i < _n * _m; ++i)
            result[static_cast<size_t>(i)] = static_cast<float>(_K[static_cast<size_t>(i)]);
        return result;
    }

    /**
     * @brief Incertitude σᵢ = √P[i,i] pour chaque état (taille n).
     */
    std::vector<float> getUncertainy() const {
        std::vector<float> result(static_cast<size_t>(_n));
        for (int i = 0; i < _n; ++i)
            result[static_cast<size_t>(i)] =
                std::sqrt(static_cast<float>(_P[static_cast<size_t>(i * _n + i)]));
        return result;
    }

    /**
     * @brief Met à jour les covariances de bruit Q et R.
     * @param Q Vecteur row-major de taille n*n
     * @param R Vecteur row-major de taille m*m
     */
    void setNoiseMatrices(const std::vector<float>& Q, const std::vector<float>& R) {
        checkSize(Q, _n * _n, "Q");
        checkSize(R, _m * _m, "R");
        for (int i = 0; i < _n * _n; ++i)
            _Q[static_cast<size_t>(i)] = static_cast<double>(Q[static_cast<size_t>(i)]);
        for (int i = 0; i < _m * _m; ++i)
            _R[static_cast<size_t>(i)] = static_cast<double>(R[static_cast<size_t>(i)]);
    }

    /**
     * @brief Remplace la matrice de transition F (n*n, row-major).
     */
    void setTransitionMatrix(const std::vector<float>& F) {
        checkSize(F, _n * _n, "F");
        for (int i = 0; i < _n * _n; ++i)
            _F[static_cast<size_t>(i)] = static_cast<double>(F[static_cast<size_t>(i)]);
    }

    /**
     * @brief Remplace la matrice d'observation H (m*n, row-major).
     */
    void setObservationMatrix(const std::vector<float>& H) {
        checkSize(H, _m * _n, "H");
        for (int i = 0; i < _m * _n; ++i)
            _H[static_cast<size_t>(i)] = static_cast<double>(H[static_cast<size_t>(i)]);
    }

    /**
     * @brief Remplace la matrice de commande B (n*c, row-major).
     */
    void setCommandMatrix(const std::vector<float>& B) {
        checkSize(B, _n * _c, "B");
        for (int i = 0; i < _n * _c; ++i)
            _B[static_cast<size_t>(i)] = static_cast<double>(B[static_cast<size_t>(i)]);
    }

    /** @brief Alias explicite pour setTarget (commande u appliquée au système). */
    void setControl(const std::vector<float>& u) { setTarget(u); }

private:
    int _n; // Dimension état
    int _m; // Dimension mesure
    int _c; // Dimension commande

    // Matrices du système
    linalg::Mat _F; // (n x n) Transition d'état
    linalg::Mat _B; // (n x c) Commande
    linalg::Mat _H; // (m x n) Observation
    linalg::Mat _Q; // (n x n) Bruit processus
    linalg::Mat _R; // (m x m) Bruit mesure

    // Valeurs initiales (pour reset)
    linalg::Mat _P0;
    linalg::Mat _x0;

    // État interne
    linalg::Mat _P;  // (n x n) Covariance d'erreur courante
    linalg::Mat _x;  // (n x 1) État estimé courant
    linalg::Mat _K;  // (n x m) Gain de Kalman

    // Buffers std::vector exposés par l'interface
    std::vector<float> _x_vec;    // Taille n - état estimé
    std::vector<float> _u_vec;    // Taille c - commande u
    std::vector<float> _z_vec;    // Taille m - mesure z
    std::vector<float> _ctrl_vec; // Taille n - sortie de compute()

    static void checkSize(const std::vector<float>& v, int expected,
                          const std::string& ctx) {
        if (static_cast<int>(v.size()) != expected)
            throw std::invalid_argument(
                ctx + ": taille " + std::to_string(v.size()) +
                " != " + std::to_string(expected));
    }
};

#endif // KALMAN_FILTER_CONTROLLER_HPP