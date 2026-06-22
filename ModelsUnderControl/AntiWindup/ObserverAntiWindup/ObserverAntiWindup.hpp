#ifndef OBSERVER_ANTI_WINDUP_HPP
#define OBSERVER_ANTI_WINDUP_HPP

#include "../IAntiWindup.hpp"

/**
 * @brief Base for observer-based anti-windup using a pre-computed gain matrix.
 *
 * At each step the saturation error  e_aw = satOutput - rawOutput  is
 * computed, and a correction  Δintegral = E * x_aw * dt  is applied,
 * where x_aw is a small state vector and E is the gain supplied by the
 * offline design (LMI solve, H∞ synthesis, …).
 *
 * Subclasses must implement:
 *   - float applyGain (e_aw, dt) : compute the integral correction
 *   - void resetState() : zero the observer state
 *
 * reset() clears the state; correct() dispatches to applyGain().
 */
class ObserverAntiWindup : public IAntiWindup {
public:
    float correct(float rawOutput, float satOutput,
                  float integral,  float /*error*/, float dt) final
    {
        const float e_aw = satOutput - rawOutput;   // saturation error
        integral += applyGain(e_aw, dt);
        return integral;
    }

    void reset() final { resetState(); }

protected:
    /**
     * @brief Apply the pre-computed gain to the saturation error.
     *
     * @param e_aw satOutput - rawOutput (≡ 0 when not saturated)
     * @param dt Time step
     * @return float Integral increment to add this step
     */
    virtual float applyGain(float e_aw, float dt) = 0;

    /** @brief Zero the observer's internal state vector. */
    virtual void resetState() = 0;
};

#endif