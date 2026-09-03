#ifndef BACK_CALCULATION_ANTI_WINDUP_HPP
#define BACK_CALCULATION_ANTI_WINDUP_HPP

#include "../StatefulAntiWindup.hpp"
#include <stdexcept>
#include <cmath>

/**
 * @brief Back-calculation anti-windup
 *
 *   integral += (satOutput - rawOutput) / Tt * dt
 *
 * Smoother than clamping; works well for PI and PID.
 *
 * @param Tt  Tracking time constant [s] > 0.
 *            PI  rule of thumb : Tt = sqrt(Ti * Td) or 1/Ki
 *            PID rule of thumb : Tt = sqrt(Ti * Td)
 */
class BackCalculationAntiWindup : public StatefulAntiWindup {
private:
    float m_Tt;

public:
    explicit BackCalculationAntiWindup(float Tt) : m_Tt(Tt) {
        if (Tt <= 0.f)
            throw std::invalid_argument("BackCalculationAntiWindup: Tt must be > 0");
    }

    void  setTt(float t) { if (t > 0.f) m_Tt = t; }
    float getTt() const { return m_Tt; }

protected:
    float correctImpl(float rawOutput, float satOutput,
                      float integral, float /*error*/, float dt) override {
        integral += (satOutput - rawOutput) / m_Tt * dt;
        return integral;
    }

    void seedState(float /*raw*/, float /*sat*/,
                   float /*integral*/, float /*error*/) override {
        // No explicit state to seed beyond the m_initialized flag
    }

    void resetState() override {}
};

#endif