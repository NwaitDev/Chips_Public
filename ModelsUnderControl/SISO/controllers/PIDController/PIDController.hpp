#ifndef PID_CONTROLLER_HPP
#define PID_CONTROLLER_HPP

#include "../../IControllerSISO.hpp"
#include <limits>

/**
 * @file PIDController.hpp
 * @brief Header for Proportional-Integral-Derivative) SISO Controller
 *
 * This class implements a Proportional-Integral-Derivative (PID) controller for Single Input Single Output (SISO) systems.
 * It computes the control output based on the error between the target value and the current value,
 * scaled by a proportional gain (Kp), an integral gain (Ki), and a derivative gain (Kd).
 *
 * Optional output limits can be set to constrain the controller's output.
 */

typedef IControllerSISO* ControllerPtr;

ControllerPtr create_pid_controller(float kp, float ki, float kd);
ControllerPtr create_pid_controller_with_limits(float kp, float ki, float kd, float minOutput, float maxOutput);

class PIDController : public IControllerSISO{
public:
    /**
     * @brief Construct a new PIDController object
     *
     * @param kp Proportional gain
     * @param ki Integral gain
     * @param kd Derivative gain
     */
    PIDController(float kp, float ki, float kd);

    /**
     * @brief Construct a new PIDController object with output limits
     *
     * @param kp Proportional gain
     * @param ki Integral gain
     * @param kd Derivative gain
     * @param minOutput Minimum output limit
     * @param maxOutput Maximum output limit
     */
    PIDController(float kp, float ki, float kd, float minOutput, float maxOutput);

    /**
     * @brief Get the target value object
     *
     * @return float The current target value (setpoint)
     */
    float getTargetValue() const override;

    /**
     * @brief Get the current value object
     *
     * @return float The current measured value
     */
    float getCurrentValue() const override;

    /**
     * @brief Get the correction object
     *
     * @return float The current controller output (correction)
     */
    float getCorrection() const override;

    /**
     * @brief Set the target value object
     *
     * @param targetValue The desired setpoint value
     */
    void setTargetValue(float targetValue) override;

    /**
     * @brief Set the current value object
     *
     * @param currentValue The measured value from the system
     */
    void setCurrentValue(float currentValue) override;

    /**
     * @brief Compute the control output based on the current error
     *
     * The correction is calculated as: correction = Kp * error + Ki * integral + Kd * derivative
     *
     * @param dt Time step for integration and differentiation
     * @return float The computed control output (correction)
     */
    float compute(float dt) override;

    /**
     * @brief Reset the controller state
     *
     * For a PID controller, this resets the correction, integral, and derivative state to zero.
     */
    void reset() override;

    /**
     * @brief Get the Kp object
     *
     * @return float The current proportional gain
     */
    float getKp() const { return m_kp; }

    /**
     * @brief Get the Ki object
     *
     * @return float The current integral gain
     */
    float getKi() const { return m_ki; }

    /**
     * @brief Get the Kd object
     *
     * @return float The current derivative gain
     */
    float getKd() const { return m_kd; }

    /**
     * @brief Set the Kp object
     *
     * @param kp The new proportional gain value
     */
    void setKp(float kp) { m_kp = kp; }

    /**
     * @brief Set the Ki object
     *
     * @param ki The new integral gain value
     */
    void setKi(float ki) { m_ki = ki; }

    /**
     * @brief Set the Kd object
     *
     * @param kd The new derivative gain value
     */
    void setKd(float kd) { m_kd = kd; }

    /**
     * @brief Set the output limits object
     *
     * @param minOutput Minimum output limit
     * @param maxOutput Maximum output limit
     */
    void setOutputLimits(float minOutput, float maxOutput);

    /**
     * @brief Remove output limits, allowing the controller to output any value
     */
    void removeOutputLimits();

private:
    float m_kp;             // Proportional gain
    float m_ki;             // Integral gain
    double m_kd;            // Derivative gain
    float m_minOutput;      // Minimum output limit
    float m_maxOutput;      // Maximum output limit
    bool  m_hasLimits;      // Flag indicating if output limits are set

    float m_targetValue;    // Target setpoint value
    float m_currentValue;   // Current measured value
    float m_integral;       // Integral of the error
    float m_correction;     // Controller output (correction)
    float m_prevError;

    /**
     * @brief Clamp the given value within the output limits if they are set
     *
     * @param value The value to be clamped
     * @return float The clamped value
     */
    float clamp(float value) const;
};

#endif