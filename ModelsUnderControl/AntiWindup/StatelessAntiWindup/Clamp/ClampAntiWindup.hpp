#ifndef CLAMP_ANTI_WINDUP_HPP
#define CLAMP_ANTI_WINDUP_HPP

#include "../StatelessAntiWindup.hpp"
#include <stdexcept>


/**
 * @brief Integral clamp anti-windup.
 *
 * @param minOutput  Lower saturation limit (must match the output ClampFilter)
 * @param maxOutput  Upper saturation limit
 */
class ClampingAntiWindup : public StatelessAntiWindup {
private:
    float m_min, m_max;
    float m_minIntegral;
    float m_maxIntegral;
    bool m_hasIntegralLimits;
    
public:
    ClampingAntiWindup(float minOutput, float maxOutput)
        : m_min(minOutput), m_max(maxOutput),
          m_minIntegral(minOutput), m_maxIntegral(maxOutput),
          m_hasIntegralLimits(false) {
        if (m_min >= m_max)
            throw std::invalid_argument("ClampingAntiWindup: min must be < max");
    }

    void setLimits(float lo, float hi) {
        if (lo >= hi) throw std::invalid_argument("ClampingAntiWindup: min < max");
        m_min = lo; m_max = hi;
    }

    void setIntegralLimits(float lo, float hi) {
        if (lo > hi) throw std::invalid_argument("ClampingAntiWindup: integral min must be <= max");
        m_minIntegral = lo;
        m_maxIntegral = hi;
        m_hasIntegralLimits = true;
    }

    void clearIntegralLimits() {
        m_hasIntegralLimits = false;
    }

    float correct(float /*rawOutput*/, float /*satOutput*/,
                  float integral, float /*error*/, float /*dt*/) override {
        if (m_hasIntegralLimits) {
            if (integral < m_minIntegral) integral = m_minIntegral;
            if (integral > m_maxIntegral) integral = m_maxIntegral;
        }
        return integral;
    }
};

#endif