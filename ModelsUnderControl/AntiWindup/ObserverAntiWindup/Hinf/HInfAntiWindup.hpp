#ifndef H_INFINITY_ANTI_WINDUP_HPP
#define H_INFINITY_ANTI_WINDUP_HPP

#include "../ObserverAntiWindup.hpp"
#include <stdexcept>

/**
 * @brief H infinity-based anti-windup for SISO controllers.
 *
 * Minimises the H infinity norm of the transfer from the saturation nonlinearity
 * to the performance output.  For SISO systems this reduces to a static
 * gain  E_hinf  applied to the saturation error, plus an optional
 * first-order low-pass on the correction signal to limit high-frequency
 * injection (roll-off filter, time constant tau_r):
 *
 *   Without roll-off (tau_r = 0):
 *     Δintegral = E * e_aw * dt
 *
 *   With roll-off (tau_r > 0):
 *     y_r[k] = alpha * y_r[k-1] + (1-alpha) * E * e_aw    alpha = tau_r/(tau_r+dt)
 *     Δintegral = y_r[k] * dt
 *
 * The roll-off filter prevents the H∞ correction from amplifying
 * measurement noise at frequencies above 1/tau_r.  Typical choice:
 *   tau_r ~ 3 / omega_c   where omega_c is the closed-loop bandwidth.
 *
 * @param E_hinf  Pre-computed H infinity gain  (from offline hinfsyn solve)
 * @param tauRolloff Roll-off time constant [s].  0 = no roll-off.
 */
class HInfAntiWindup : public ObserverAntiWindup {

private:
    float m_E;         // H infinity gain (offline-computed)
    float m_tau;       // Roll-off filter time constant (0 = disabled)
    float m_yRolloff;  // Roll-off filter state

public:
    /**
     * @param E_hinf     H∞ gain (from offline hinfsyn).
     *                   Typically negative for proper anti-windup action
     *                   (sign convention: correction opposes windup direction).
     * @param tauRolloff Roll-off filter time constant [s].  0 = disabled.
     *                   Must be >= 0.
     */
    explicit HInfAntiWindup(float E_hinf, float tauRolloff = 0.f)
        : m_E(E_hinf), m_tau(tauRolloff), m_yRolloff(0.f)
    {
        if (tauRolloff < 0.f)
            throw std::invalid_argument(
                "HInfAntiWindup: tauRolloff must be >= 0 "
                "(0 to disable roll-off filtering)");
    }

    void  setGain(float E)            { m_E   = E;   }
    void  setTauRolloff(float tau)    {
        if (tau < 0.f)
            throw std::invalid_argument("HInfAntiWindup: tauRolloff >= 0");
        m_tau = tau;
    }
    float getGain()        const { return m_E;        }
    float getTauRolloff()  const { return m_tau;      }
    float getRolloffState() const { return m_yRolloff; }

    /**
     * @brief Convenience factory: compute an approximate H∞ gain from plant
     *        parameters using the simplified SISO formula.
     *
     * For a first-order plant  G(s) = Kp / (tau_p * s + 1)  and a target
     * L2 gain bound gamma, the approximate static H∞ anti-windup gain is:
     *
     *   E ~ -1 / (2 * gamma² * Kp)
     *
     * This is a rough estimate - use hinfsyn for production designs.
     *
     * @param plantGain   DC gain of the plant  Kp
     * @param gamma       Target H infinity L2-gain bound (must be > 0)
     * @param tauRolloff  Optional roll-off [s]
     */
    static HInfAntiWindup fromPlantApprox(float plantGain,
                                          float gamma,
                                          float tauRolloff = 0.f)
    {
        if (gamma <= 0.f)
            throw std::invalid_argument("HInfAntiWindup::fromPlantApprox: gamma > 0");
        if (plantGain == 0.f)
            throw std::invalid_argument("HInfAntiWindup::fromPlantApprox: plantGain != 0");
        const float E = -1.f / (2.f * gamma * gamma * plantGain);
        return HInfAntiWindup(E, tauRolloff);
    }

protected:
    /**
     * @brief Apply E_hinf with optional roll-off low-pass filter.
     */
    float applyGain(float e_aw, float dt) override {
        const float raw_correction = m_E * e_aw;

        if (m_tau <= 0.f) {
            // No roll-off: direct static gain
            return raw_correction * dt;
        }

        // First-order low-pass roll-off (Tustin discretisation)
        const float alpha = m_tau / (m_tau + dt);
        m_yRolloff = alpha * m_yRolloff + (1.f - alpha) * raw_correction;
        return m_yRolloff * dt;
    }

    void resetState() override { m_yRolloff = 0.f; }
};

#endif