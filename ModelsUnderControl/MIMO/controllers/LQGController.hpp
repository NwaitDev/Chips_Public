#ifndef LQG_CONTROLLER_HPP
#define LQG_CONTROLLER_HPP

#include "../IControllerMIMO.hpp"
#include "KalmanFilter.hpp"
#include "LQRController.hpp"

#include <vector>

/**
 * @brief Linear-Quadratic-Gaussian controller combining a Kalman estimator and LQR
 *
 * Usage:
 *  - configure system matrices (A/B), observation H, estimator noises (Q/R)
 *  - configure LQR cost matrices (Q_lqr/R_lqr)
 *  - call setCurrentOutput(measurement) each step before compute()
 *  - compute() returns control u = -K_lqr * x_hat
 */
class LQGController : public IControllerMIMO {
public:
    LQGController(int nStates, int nInputs, int nOutputs);
    ~LQGController() override = default;

    int getStateSize() const override { return _n; }
    int getInputSize() const override { return _m; }
    int getOutputSize() const override { return _p; }

    const std::vector<float>& getTarget() const override { return _r; }
    const std::vector<float>& getCurrentOutput() const override { return _y; }
    const std::vector<float>& getCurrentState() const override { return _x_hat; }
    const std::vector<float>& getControl() const override { return _u; }

    // System / estimator / controller configuration
    void setSystemMatrices(const std::vector<float>& A, const std::vector<float>& B);
    void setObservationMatrix(const std::vector<float>& H);
    void setEstimatorNoise(const std::vector<float>& Q_proc, const std::vector<float>& R_meas);
    void setLQRCost(const std::vector<float>& Ql, const std::vector<float>& Rl);

    // IControllerMIMO
    void setTarget(const std::vector<float>& r) override;
    void setCurrentOutput(const std::vector<float>& y) override;
    void setCurrentState(const std::vector<float>& x) override;
    std::vector<float> compute(float dt) override;
    void reset() override;

    // --- Introspection helpers (delegated to internal Kalman) ---
    std::vector<float> getEstimatorCovariance() const;
    std::vector<float> getEstimatorKalmanGain() const;
    std::vector<float> getEstimatorSigma() const;

private:
    int _n; // state dim
    int _m; // input dim
    int _p; // output dim (measurement)

    KalmanFilter _kf;
    LQRController _lqr;

    std::vector<float> _r;      // target (size p)
    std::vector<float> _y;      // last measurement (size p)
    std::vector<float> _x_hat;  // last state estimate (size n)
    std::vector<float> _u;      // last control (size m)
    std::vector<float> _last_applied_u; // for estimator prediction
};

#endif // LQG_CONTROLLER_HPP
