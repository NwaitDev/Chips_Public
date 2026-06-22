#ifndef LOW_PASS_FILTER_HPP
#define LOW_PASS_FILTER_HPP

#include "../StatefulFilter.hpp"
#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>
#include <stdexcept>

/**
 * @brief First-order low-pass filter.
 *
 * Discrete transfer function (Tustin):
 *   y[k] = alpha * y[k-1] + (1 - alpha) * x[k]
 *   where alpha = tau / (tau + dt)
 *
 * Typical use case: smooth a noisy derivative or damp high-frequency
 * oscillations in the control output.
 *
 * @param tau  Time constant [s].  Larger tau => stronger smoothing.
 *             Rule of thumb: tau ~ 3–10× the dominant noise period.
 */
class LowPassFilter : public StatefulFilter {
    private:
    float m_tau;
    float m_prevOutput;
public:
    explicit LowPassFilter(float tau)
        : m_tau(tau), m_prevOutput(0.0f){
        if (tau <= 0.0f)
            throw std::invalid_argument("LowPassFilter: tau must be > 0");
    }

    void setTau(float tau) {
        if (tau <= 0.0f)
            throw std::invalid_argument("LowPassFilter: tau must be > 0");
        m_tau = tau;
    }

    float getTau() const { return m_tau; }

protected:
    float applyImpl(float value, float dt) override {
        const float alpha = m_tau / (m_tau + dt);
        m_prevOutput = alpha * m_prevOutput + (1.f - alpha) * value;
        return m_prevOutput;
    }

    void seedState(float v)  override { m_prevOutput = v; }
    void resetState()        override { m_prevOutput = 0.f; }
};


#endif