#ifndef HIGH_PASS_FILTER_HPP
#define HIGH_PASS_FILTER_HPP

#include "../StatefulFilter.hpp"
#include <stdexcept>

class HighPassFilter : public StatefulFilter {
private:
    float m_tau;
    float m_prevInput;
    float m_prevOutput;

public:
    explicit HighPassFilter(float tau)
        : m_tau(tau),
          m_prevInput(0.0f),
          m_prevOutput(0.0f)
    {
        if (tau <= 0.0f)
            throw std::invalid_argument("HighPassFilter: tau must be > 0");
    }

    void setTau(float tau) {
        if (tau <= 0.0f)
            throw std::invalid_argument("HighPassFilter: tau must be > 0");
        m_tau = tau;
    }

    float getTau() const { return m_tau; }

protected:
    float applyImpl(float value, float dt) override {
        const float alpha = m_tau / (m_tau + dt);

        m_prevOutput = alpha * (m_prevOutput + value - m_prevInput);

        m_prevInput = value;

        return m_prevOutput;
    }

    void seedState(float v) override {
        m_prevInput  = v;
        m_prevOutput = 0.0f;
    }

    void resetState() override {
        m_prevInput  = 0.0f;
        m_prevOutput = 0.0f;
    }
};

#endif