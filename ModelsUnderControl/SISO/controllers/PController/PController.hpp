#ifndef PCONTROLLER_H
#define PCONTROLLER_H

#include "../../IControllerSISO.hpp"
#include "../../../Filters/IFilter.hpp"
#include "../../../AntiWindup/IAntiWindup.hpp"
#include <limits>
#include <vector>
#include <memory>

typedef IControllerSISO* ControllerPtr;

ControllerPtr create_p_controller(float kp);
ControllerPtr create_p_controller_with_limits(float kp, float minOutput, float maxOutput);

/**
 * @file PController.hpp
 * @brief Header for Proportional SISO Controller
 * 
 * This class implements a simple Proportional controller for Single Input Single Output (SISO) systems.
 * It computes the control output based on the error between the target value and the current value,
 * scaled by a proportional gain (Kp). 
 * 
 * Optional output limits can be set to constrain the controller's output.
 */
class PController : public IControllerSISO {
public:
    // /**
    //  * @brief Construct a new PController object
    //  * 
    //  * @param kp Proportional gain
    //  */
    // explicit PController(float kp);

    /**
     * @brief Construct a new PController object with output limits
     * 
     * @param kp Proportional gain
     * @param minOutput Minimum output limit
     * @param maxOutput Maximum output limit
     */
    PController(float kp, float minOutput, float maxOutput);

    /**
     * @brief Construct a new PController object
     * 
     * @param kp Proportional gain
     * @param inputFilter nullptr -> PassThroughFilter  (applied to the measurement)
     * @param outputFilter nullptr -> PassThroughFilter (applied to the P output)
     * @param antiwindup nullptr -> NoAntiWindup
     */
    PController(float kp, std::shared_ptr<IFilter> inputFilter = nullptr, std::shared_ptr<IFilter> outputFilter = nullptr, std::shared_ptr<IAntiWindup> antiwindup = nullptr);

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
     * @brief Get the Proportional Gain (Kp) object
     * 
     * @return float The current proportional gain
     */
    float getKp() const { return m_kp; }

    /**
     * @brief Set the Target Value object
     * 
     * @param targetValue The desired setpoint value
     */
    void setTargetValue(float targetValue) override;

    /**
     * @brief Set the Current Value object
     * 
     * @param currentValue The measured value from the system
     */
    void setCurrentValue(float currentValue) override;

    /**
     * @brief Set the Proportional Gain (Kp) object
     * 
     * @param kp The new proportional gain value
     */
    void setKp(float kp) { m_kp = kp; }

    /**
     * @brief Set the input filter (applied to the raw measurement).
     *
     * Typical choices: LowPassFilter (sensor noise), DeadbandFilter (sensor
     * quantization), or a CompositeFilter combining both.
     * nullptr -> PassThroughFilter.
     */
    void setInputFilter(std::shared_ptr<IFilter> inputFilter);

    /**
     * @brief Set the output filter (applied to the raw P command).
     *
     * Typical choices: ClampFilter (saturation), RateLimiterFilter (slew
     * rate), or a CompositeFilter. nullptr -> PassThroughFilter.
     */
    void setOutputFilter(std::shared_ptr<IFilter> outputFilter);

    /**
     * @brief Set an anti-windup to correct the integrator when the output is satured
     * 
     * nullptr -> NoAntiWindup
     */
    void setAntiWindup(std::shared_ptr<IAntiWindup> aw);

    /**
     * @brief Set output limits for the controller
     * 
     * @param minOutput Minimum output limit
     * @param maxOutput Maximum output limit
     */
    void setOutputLimits(float minOutput, float maxOutput);

    /**
     * @brief Compute the control output based on the current error
     * 
     * The correction is calculated as: correction = Kp * (targetValue - currentValue)
     * 
     * @param dt Time step (not used in P controller but included for interface consistency)
     * @return float The computed control output (correction)
     */
    float compute(float dt) override;

    /**
     * @brief Reset the controller state
     * 
     * For a P controller, this resets the correction to zero.
     */
    void reset() override;

    /**
     * @brief Remove output limits, allowing the controller to output any value
     */
    void removeOutputLimits();

    const IFilter* getInputFilter()  const { return m_inputFilter.get();  }
    const IFilter* getOutputFilter() const { return m_outputFilter.get(); }
    const IAntiWindup* getAntiWindup() const { return m_antiWindup.get(); }
 
    /**
     * @brief Return the last input-filtered measurement used in compute().
     *
     * Useful for debugging: compare with getCurrentValue() to see what the
     * input filter removed.
     */
    float getFilteredMeasure() const { return m_filteredMeasure; }

private:
    float m_kp;           // Proportional gain
    float m_minOutput;    // Minimum output limit
    float m_maxOutput;    // Maximum output limit
    bool m_hasLimits;     // Indicates if limits are active
    
    float m_targetValue;  // Setpoint
    float m_currentValue; // Measured value
    float m_correction;   // Controller output
    float m_filteredMeasure; // Last value after the input filter

    std::shared_ptr<IFilter> m_inputFilter;
    std::shared_ptr<IFilter> m_outputFilter;
    std::shared_ptr<IAntiWindup> m_antiWindup;
    
    /**
     * @brief Clamps the value within the set output limits if limits are active
     * 
     * @param value Value to be limited
     * @return float Limited value (or unchanged if no limits)
     */
    float clamp(float value) const;
};

#endif