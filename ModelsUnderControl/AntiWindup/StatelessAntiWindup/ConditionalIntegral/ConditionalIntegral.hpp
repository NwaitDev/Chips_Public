#ifndef CONDITIONAL_INTEGRAL_ANTI_WINDUP_HPP
#define CONDITIONAL_INTEGRAL_ANTI_WINDUP_HPP

#include "../StatelessAntiWindup.hpp"
#include <stdexcept>
#include <cmath>

/**
 * @brief Conditional integration - pause the integrator below an error threshold.
 *
 * Integration only runs when |error| > threshold. Near the setpoint where
 * the error is small and sensor noise dominates, the integral is frozen,
 * preventing noise-driven drift (chatter reduction).
 *
 * Compare with IntegralSeparation: this pauses integration near the setpoint;
 * IntegralSeparation disables it far from it.
 *
 * @param threshold  Error magnitude below which integration is paused [units]
 */
class ConditionalIntegral : public StatelessAntiWindup {
private:
    float m_threshold;

public:
    explicit ConditionalIntegral(float threshold) : m_threshold(threshold) {
        if (threshold < 0.f)
            throw std::invalid_argument("ConditionalIntegral: threshold >= 0");
    }

    float correct(float /*rawOutput*/, float /*satOutput*/,
                  float integral, float error, float dt) override
    {
        if (std::fabs(error) < m_threshold)
            integral -= error * dt;
        return integral;
    }

    void  setThreshold(float t) { m_threshold = (t >= 0.f) ? t : m_threshold; }
    float getThreshold() const { return m_threshold; }


};

#endif