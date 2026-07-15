#ifndef LINEAR_MATRIX_INEQUALITIES_ANTI_WINDUP_HPP
#define LINEAR_MATRIX_INEQUALITIES_ANTI_WINDUP_HPP

#include "../ObserverAntiWindup.hpp"
#include <stdexcept>

/**
 * @brief LMI-based anti-windup for SISO controllers.
 *
 * Correction at each step:
 *   Δintegral = E * (satOutput - rawOutput) * dt
 *
 * where E is the scalar gain computed offline by solving the LMI SDP.
 *
 * An optional first-order observer state x_aw can be enabled by setting
 * a non-zero observer pole λ < 0 (disabled by default, λ = 0):
 *
 *   dx_aw/dt = λ * x_aw + e_aw (observer dynamics)
 *   Δintegral = E * x_aw * dt  (correction uses filtered e_aw)
 *
 * This makes the correction smoother at the cost of one extra state.
 * Leave λ = 0 for the pure static-gain version (most common case).
 *
 * @param E Pre-computed LMI gain  (positive scalar for minimum-phase plants)
 * @param lambda Observer pole [rad/s], must be < 0 if used, 0 = disabled
 */
class LMIAntiWindup : public ObserverAntiWindup {

private:
    float m_E;        // LMI gain (offline-computed)
    float m_lambda;   // Observer pole (0 = disabled)
    float m_xAw;      // Observer state

public:
    /**
     * @param E      LMI gain (from offline SDP solve).
     *               Positive for minimum-phase plants.
     *               Typical range: 0.1 … 10 depending on plant bandwidth.
     * @param lambda Observer pole [rad/s]. 0 = static gain (default).
     *               If non-zero must be strictly negative (stable observer).
     */
    explicit LMIAntiWindup(float E, float lambda = 0.f)
        : m_E(E), m_lambda(lambda), m_xAw(0.f)
    {
        if (lambda > 0.f)
            throw std::invalid_argument(
                "LMIAntiWindup: observer pole lambda must be <= 0 "
                "(negative for a stable observer, 0 to disable)");
    }

    void  setGain(float E)        { m_E      = E; }
    void  setLambda(float lambda) {
        if (lambda > 0.f)
            throw std::invalid_argument("LMIAntiWindup: lambda must be <= 0");
        m_lambda = lambda;
    }
    float getGain()   const { return m_E;      }
    float getLambda() const { return m_lambda;  }
    float getState()  const { return m_xAw;    }

protected:
    /**
     * @brief Apply E to the saturation error, optionally filtered through
     *        the first-order observer state x_aw.
     */
    float applyGain(float e_aw, float dt) override {
        if (m_lambda == 0.f) {
            // Static gain: Δintegral = E * e_aw * dt
            return m_E * e_aw * dt;
        }
        // Observer: Euler-integrate dx_aw = lambda*x_aw + e_aw
        m_xAw += (m_lambda * m_xAw + e_aw) * dt;
        return m_E * m_xAw * dt;
    }

    void resetState() override { m_xAw = 0.f; }
};

#endif