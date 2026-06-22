#ifndef PICONTROLLER_H
#define PICONTROLLER_H

#include "../../IControllerSISO.hpp"
#include "../../../Filters/IFilter.hpp"
#include "../../../AntiWindup/IAntiWindup.hpp"
#include <limits>
#include <memory>

typedef IControllerSISO* ControllerPtr;

ControllerPtr create_pi_controller(float kp, float ki);
ControllerPtr create_pi_controller_with_limits(float kp, float ki, float minOutput, float maxOutput);

/**
 * @file PIController.hpp
 * @brief Header for Proportional-Integral SISO Controller
 * 
 * This class implements a Proportional-Integral (PI) controller for Single Input Single Output (SISO) systems.
 * It computes the control output based on the error between the target value and the current value,
 * scaled by a proportional gain (Kp) and an integral gain (Ki).
 * 
 * Optional output limits can be set to constrain the controller's output.
 */
class PIController : public IControllerSISO {
public:
    /**
     * @brief Construct a new PIController object
     * 
     * @param kp Proportional gain
     * @param ki Integral gain
     * @param inputFilter nullptr -> PassThroughFilter  (applied to the measurement)
     * @param outputFilter nullptr -> PassThroughFilter (applied to the PI output)
     * @param antiwindup nullptr -> NoAntiWindup
     */
    PIController(float kp, float ki, std::shared_ptr<IFilter> inputFilter = nullptr, std::shared_ptr<IFilter> outputFilter = nullptr, std::shared_ptr<IAntiWindup> antiwindup = nullptr);

    /**
     * @brief Construct a new PIController object with output limits
     * 
     * @param kp Proportional gain
     * @param ki Integral gain
     * @param minOutput Minimum output limit
     * @param maxOutput Maximum output limit
     */
    PIController(float kp, float ki, float minOutput, float maxOutput);

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
     * The correction is calculated as: correction = Kp * error + Ki * integral
     * 
     * @param dt Time step for integration
     * @return float The computed control output (correction)
     */
    float compute(float dt) override;

    /**
     * @brief Reset the controller state
     * 
     * For a PI controller, this resets the correction and integral to zero.
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
     * @brief Set the input filter (applied to the raw measurement).
     *
     * Typical choices: LowPassFilter (sensor noise), DeadbandFilter (sensor
     * quantization), or a CompositeFilter combining both.
     * nullptr -> PassThroughFilter.
     */
    void setInputFilter(std::shared_ptr<IFilter> inputFilter) { m_inputFilter = std::move(inputFilter); }

    /**
     * @brief Set the output filter (applied to the raw P command).
     *
     * Typical choices: ClampFilter (saturation), RateLimiterFilter (slew
     * rate), or a CompositeFilter. nullptr -> PassThroughFilter.
     */
    void setOutputFilter(std::shared_ptr<IFilter> outputFilter) { m_outputFilter = std::move(outputFilter); }

    /**
     * @brief Set an anti-windup to correct the integrator when the output is satured
     * 
     * nullptr -> NoAntiWindup
     */
    void setAntiWindup(std::shared_ptr<IAntiWindup> antiwindup) { m_antiwindup = std::move(antiwindup); }

    /**
     * @brief Set the Output Limits object
     * 
     * @param minOutput Minimum output limit
     * @param maxOutput Maximum output limit
     */
    void setOutputLimits(float minOutput, float maxOutput);

    /**
     * @brief Remove output limits, allowing the controller to output any value
     */
    void removeOutputLimits();

    const IFilter* getInputFilter()  const { return m_inputFilter.get();  }
    const IFilter* getOutputFilter() const { return m_outputFilter.get(); }
    const IAntiWindup* getAntiWindup() const { return m_antiwindup.get(); }
 
    /**
     * @brief Return the last input-filtered measurement used in compute().
     *
     * Useful for debugging: compare with getCurrentValue() to see what the
     * input filter removed.
     */
    float getFilteredMeasure() const { return m_filteredMeasure; }

    float getIntegral() const { return m_integral; }

private:
    float m_kp;             // Proportional gain
    float m_ki;             // Integral gain
    float m_minOutput;      // Minimum output limit
    float m_maxOutput;      // Maximum output limit
    bool  m_hasLimits;      // Flag indicating if output limits are set

    float m_targetValue;    // Target setpoint value
    float m_currentValue;   // Current measured value
    float m_integral;       // Integral term accumulator
    float m_correction;     // Current controller output
    float m_filteredMeasure; // Last value after the input filter

    std::shared_ptr<IFilter> m_inputFilter;
    std::shared_ptr<IFilter> m_outputFilter;
    std::shared_ptr<IAntiWindup> m_antiwindup;

    /**
     * @brief Clamp the given value within the output limits if they are set
     * 
     * @param value The value to be clamped
     * @return float The clamped value
     */
    float clamp(float value) const;
};

#endif
