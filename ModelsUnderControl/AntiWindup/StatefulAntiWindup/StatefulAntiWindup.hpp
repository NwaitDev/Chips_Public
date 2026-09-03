#ifndef STATEFUL_ANTI_WINDUP_HPP
#define STATEFUL_ANTI_WINDUP_HPP

#include "../IAntiWindup.hpp"


/**
 * @brief Base for anti-windup strategies that maintain state across calls.
 *
 * Provides:
 *   - m_initialized : false until the first correct() call
 *   - correct() [final] : handles the first-step seed, then calls correctImpl()
 *   - reset() [final] : clears flag and calls resetState()
 *
 * Subclasses must implement:
 *   - float correctImpl(rawOutput, satOutput, integral, error, dt)
 *   - void seedState  (rawOutput, satOutput, integral, error)
 *   - void resetState ()
 */
class StatefulAntiWindup : public IAntiWindup {
public:
    float correct(float rawOutput, float satOutput,
                  float integral,  float error, float dt) final
    {
        if (!m_initialized) {
            seedState(rawOutput, satOutput, integral, error);
            m_initialized = true;
            return integral;   // no correction on first step
        }
        return correctImpl(rawOutput, satOutput, integral, error, dt);
    }

    void reset() final {
        m_initialized = false;
        resetState();
    }

    bool isInitialized() const { return m_initialized; }

protected:
    virtual float correctImpl(float rawOutput, float satOutput,
                              float integral,  float error, float dt) = 0;
    virtual void  seedState  (float rawOutput, float satOutput,
                              float integral,  float error)           = 0;
    virtual void  resetState ()                                       = 0;

private:
    bool m_initialized = false;
};

#endif