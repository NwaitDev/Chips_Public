#ifndef BUTTERWORTH_LOW_PASS_FILTER_HPP
#define BUTTERWORTH_LOW_PASS_FILTER_HPP

#include "../StatefulFilter.hpp"
#include <cmath>
#include <stdexcept>

class LowPassFilterOrder2 : public StatefulFilter {
private:
    float m_cutoff; // Hz

    float x1 = 0.f;
    float x2 = 0.f;
    float y1 = 0.f;
    float y2 = 0.f;

public:
    explicit LowPassFilterOrder2(float cutoff)
        : m_cutoff(cutoff) {
        if (cutoff <= 0.0f)
            throw std::invalid_argument("cutoff must be > 0");
    }

protected:
    float applyImpl(float x0, float dt) override {
        if (dt <= 0.0f) {
            return x0; // évite de rester bloqué à 0
        }

        const float fs = 1.0f / dt;
        const float nyquist = fs * 0.5f;

        if (m_cutoff >= nyquist) {
            return x0; // impossible de filtrer correctement
        }

        constexpr float PI = 3.14159265358979323846f;
        const float Q = 1.0f / std::sqrt(2.0f);

        const float omega = 2.0f * PI * m_cutoff / fs;
        const float sn = std::sin(omega);
        const float cs = std::cos(omega);
        const float alpha = sn / (2.0f * Q);

        float b0 = (1.0f - cs) / 2.0f;
        float b1 = 1.0f - cs;
        float b2 = (1.0f - cs) / 2.0f;
        float a0 = 1.0f + alpha;
        float a1 = -2.0f * cs;
        float a2 = 1.0f - alpha;

        b0 /= a0;
        b1 /= a0;
        b2 /= a0;
        a1 /= a0;
        a2 /= a0;

        const float y0 = b0 * x0 + b1 * x1 + b2 * x2
                       - a1 * y1 - a2 * y2;

        x2 = x1;
        x1 = x0;
        y2 = y1;
        y1 = y0;

        return y0;
    }

    void seedState(float v) override {
        x1 = v;
        x2 = v;
        y1 = v;
        y2 = v;
    }

    void resetState() override {
        x1 = x2 = 0.f;
        y1 = y2 = 0.f;
    }
};

#endif