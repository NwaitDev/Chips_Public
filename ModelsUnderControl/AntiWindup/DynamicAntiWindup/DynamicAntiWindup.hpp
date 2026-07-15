#ifndef DYNAMIC_ANTI_WINDUP_HPP
#define DYNAMIC_ANTI_WINDUP_HPP

#include "../IAntiWindup.hpp"

/**
 * @brief Base for dynamic compensator anti-windup strategies.
 *
 * All dynamic methods (Full-Order, Reduced-Order, Low-Order) share:
 *
 *   e_aw = satOutput - rawOutput
 *   y_c = compensatorStep(e_aw, dt)    [internal W(s) step]
 *   integral += y_c * dt
 *
 * correct() and reset() are final.
 * Subclasses implement: compensatorStep(), resetCompensator()
 */
class DynamicAntiWindup : public IAntiWindup {
public:
    float correct(float rawOutput, float satOutput,
                  float integral, float /*error*/, float dt) final {
        const float e_aw = satOutput - rawOutput;
        const float y_c  = compensatorStep(e_aw, dt);
        integral += y_c * dt;
        return integral;
    }
 
    void reset() final { resetCompensator(); }
 
protected:
    virtual float compensatorStep (float e_aw, float dt) = 0;
    virtual void resetCompensator() = 0;
};

#endif