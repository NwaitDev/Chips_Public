#ifndef STATEFUL_FILTER_HPP
#define STATEFUL_FILTER_HPP

#include "../IFilter.hpp"

/**
 * @brief Base for filters that maintain state across calls (IIR, trackers…).
 *
 * Provides:
 *   - m_initialized flag     : false until the first apply() call
 *   - onFirstSample(value)   : hook called on the first sample to seed the state
 *   - reset()                : clears the flag and calls resetState()
 *
 * Derived classes must implement:
 *   - float applyImpl(float value, float dt)  : one filter step (state already seeded)
 *   - void  seedState(float value)            : initialise internal state from first sample
 *   - void  resetState()                      : zero-out internal state
 */
class StatefulFilter : public IFilter {
public:
    /**
     * @brief Dispatches to seedState() on the first call, then to applyImpl().
     */
    float apply(float value, float dt) final {
        if (!m_initialized) {
            seedState(value);
            m_initialized = true;
            return value;
        }
        return applyImpl(value, dt);
    }

    void reset() final {
        m_initialized = false;
        resetState();
    }

    bool isInitialized() const { return m_initialized; }

protected:
    virtual float applyImpl(float value, float dt) = 0;
    virtual void  seedState(float firstValue)       = 0;
    virtual void  resetState()                      = 0;

private:
    bool m_initialized = false;
};

#endif