#ifndef I_ANTI_WINDUP_HPP
#define I_ANTI_WINDUP_HPP


/**
 * @brief Root strategy interface for anti-windup correction on integrators.
 *
 * @code
 *   float raw      = Kp*e + Ki*integral + Kd*derivative;
 *   float filtered = outputFilter->apply(raw, dt); saturation here
 *   integral = antiWindup->correct(raw, filtered, integral, error, dt);
 * @endcode
 *
 * The interface is intentionally minimal so that all three families
 * (Stateless, Stateful, Observer) implement the same two-method contract.
 */
class IAntiWindup {
public:
    /**
     * @param rawOutput   PI(D) output before the output filter  (what was wanted)
     * @param satOutput   PI(D) output after  the output filter  (what was sent)
     * @param integral    Current integral accumulator
     * @param error       Current error  (setpoint - filtered_measurement)
     * @param dt          Time step
     * @return float      Corrected integral to store for the next step
     */
    virtual float correct(float rawOutput,
                          float satOutput,
                          float integral,
                          float error,
                          float dt) = 0;
 
    virtual void reset() = 0;
    virtual ~IAntiWindup() = default;
};


#endif