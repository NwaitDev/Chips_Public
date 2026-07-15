#ifndef BUTTERWORTH_HIGH_PASS_FILTER_HPP
#define BUTTERWORTH_HIGH_PASS_FILTER_HPP

#include "../StatefulFilter.hpp"
#include <cmath>
#include <stdexcept>

class HighPassFilterOrder2 : public StatefulFilter {
private:
    float m_cutoff;

    float x1 = 0.f;
    float x2 = 0.f;

    float y1 = 0.f;
    float y2 = 0.f;

public:
    explicit HighPassFilterOrder2(float cutoff)
        : m_cutoff(cutoff) {

        if (cutoff <= 0.0f)
            throw std::invalid_argument(
                "ButterworthHighPassFilter: cutoff must be > 0");
    }

    void setCutoff(float cutoff) {
        if (cutoff <= 0.0f)
            throw std::invalid_argument(
                "ButterworthHighPassFilter: cutoff must be > 0");

        m_cutoff = cutoff;
    }

protected:
    float applyImpl(float x0, float dt) override {

        if (dt <= 0.0f)
            return y1;

        const float fs = 1.0f / dt;

        if (m_cutoff >= fs * 0.5f)
            return 0.0f;

        constexpr float Q = 0.70710678118f;

        const float omega =
            2.0f * static_cast<float>(M_PI)
            * m_cutoff / fs;

        const float sn = std::sin(omega);
        const float cs = std::cos(omega);

        const float alpha =
            sn / (2.0f * Q);

        float b0 = (1.0f + cs) * 0.5f;
        float b1 = -(1.0f + cs);
        float b2 = (1.0f + cs) * 0.5f;

        float a0 = 1.0f + alpha;
        float a1 = -2.0f * cs;
        float a2 = 1.0f - alpha;

        b0 /= a0;
        b1 /= a0;
        b2 /= a0;

        a1 /= a0;
        a2 /= a0;

        const float y0 =
              b0 * x0
            + b1 * x1
            + b2 * x2
            - a1 * y1
            - a2 * y2;

        x2 = x1;
        x1 = x0;

        y2 = y1;
        y1 = y0;

        return y0;
    }

    void seedState(float value) override {
        x1 = x2 = value;
        y1 = y2 = 0.0f;
    }

    void resetState() override {
        x1 = x2 = 0.0f;
        y1 = y2 = 0.0f;
    }
};

#endif