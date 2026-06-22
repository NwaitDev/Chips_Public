#ifndef INTEGRAL_SEPARATION_ANTI_WINDUP_HPP
#define INTEGRAL_SEPARATION_ANTI_WINDUP_HPP

#include "../StatelessAntiWindup.hpp"
#include <stdexcept>
#include <cmath>

/**
 * @brief Integral separation - disable the integrator outside an error band.
 *
 * When |error| > band, the integral is completely frozen.  Only within the
 * band does integration resume, avoiding large windup during large transients
 * or startup.
 *
 * This is the complement of ConditionalIntegral:
 *   - ConditionalIntegral : freeze integral when error is SMALL (noise near SP)
 *   - IntegralSeparation  : freeze integral when error is LARGE (far from SP)
 *
 * Typical use: band ~ 10-20% of the full operating range.
 *
 * @param band  Error magnitude above which integration is disabled [units]
 */
class IntegralSeparation : public StatelessAntiWindup {
public:
    explicit IntegralSeparation(float band) : m_band(band) {
        if (band <= 0.f)
            throw std::invalid_argument("IntegralSeparation: band must be > 0");
    }

    float correct(float /*rawOutput*/, float /*satOutput*/,
                  float integral, float error, float dt) override {
        if (std::fabs(error) > m_band)
            integral -= error * dt;
        return integral;
    }

    void  setBand(float b)          { if (b > 0.f) m_band = b; }
    float getBand() const           { return m_band; }

private:
    float m_band;
};

#endif