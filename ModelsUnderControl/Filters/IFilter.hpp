#ifndef I_FILTER_HPP
#define I_FILTER_HPP

/**
 * @brief Strategy interface for output filters applied to controller signals.
 *
 * An output filter transforms the raw controller output before it is sent to
 * the actuator.  Filters are stateless OR stateful (e.g. rate-limiter keeps
 * the previous output), but they always expose the same two-method contract.
 *
 * Filters are intentionally decoupled from any specific controller so they
 * can be reused by PIController, PIDController, OrientationController, etc.
 *
 * Chaining: use CompositeFilter to apply several filters in sequence.
 *
 * Usage inside a controller's compute() loop:
 * @code
 *   float filtered = m_inputFilter->apply(input, dt);
 *   float error = targetValue - filtered;
 *   float raw = kp * error + ki * integral;
 *   float out = m_outputFilter->apply(raw, dt);
 *   return out;
 * @endcode
 */
class IFilter {
public:
    /**
     * @brief Apply the filter to a raw controller output sample.
     *
     * @param value  Raw value to filter
     * @param dt     Time step since the last call  [s]
     * @return float Filtered value
     */
    virtual float apply(float value, float dt) = 0;
 
    /**
     * @brief Reset any internal state the filter may hold.
     *
     * Called by the controller's own reset() so both are kept in sync.
     */
    virtual void reset() = 0;
 
    virtual ~IFilter() = default;
};

#endif