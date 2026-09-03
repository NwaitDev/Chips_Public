/**
 * @file PIController.cpp
 * @brief Implementation of the Proportional-Integral (PI) Controller for SISO systems
 */

#include "PIController.hpp"
#include "../../../Filters/StatelessFilter/PassThrough/PassThroughFilter.hpp"
#include "../../../AntiWindup/StatelessAntiWindup/NoAntiWindup/NoAntiWindup.hpp"
#include <algorithm>

ControllerPtr create_pi_controller(float kp, float ki) {
    return new PIController(kp, ki);
}

ControllerPtr create_pi_controller_with_limits(float kp, float ki, float minOutput, float maxOutput) {
    return new PIController(kp, ki, minOutput, maxOutput);
}


PIController::PIController(float kp, float ki, std::shared_ptr<IFilter> inputFilter, std::shared_ptr<IFilter> outputFilter, std::shared_ptr<IAntiWindup> antiwindup)
    : m_kp(kp),
      m_ki(ki),
      m_minOutput(-std::numeric_limits<float>::infinity()),
      m_maxOutput(std::numeric_limits<float>::infinity()),
      m_hasLimits(false),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_integral(0.0f),
      m_correction(0.0f),
      m_filteredMeasure(0.0f),
      m_inputFilter(inputFilter ? std::move(inputFilter)
                                : std::make_shared<PassThroughFilter>()),
      m_outputFilter(inputFilter ? std::move(outputFilter)
                                : std::make_shared<PassThroughFilter>()),
      m_antiwindup(antiwindup ? std::move(antiwindup)
                              : std::make_shared<NoAntiWindup>())
{
}

PIController::PIController(float kp, float ki, float minOutput, float maxOutput)
    : m_kp(kp),
      m_ki(ki),
      m_minOutput(minOutput),
      m_maxOutput(maxOutput),
      m_hasLimits(true),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_integral(0.0f),
      m_correction(0.0f),
      m_inputFilter(std::make_shared<PassThroughFilter>()),
      m_outputFilter(std::make_shared<PassThroughFilter>()),
      m_antiwindup(std::make_shared<NoAntiWindup>())
{
}

float PIController::getTargetValue() const {
    return m_targetValue;
}

float PIController::getCurrentValue() const {
    return m_currentValue;
}

float PIController::getCorrection() const {
    return m_correction;
}

void PIController::setTargetValue(float targetValue) {
    m_targetValue = targetValue;
}

void PIController::setCurrentValue(float currentValue) {
    m_currentValue = currentValue;
}

float PIController::compute(float dt) {
    m_filteredMeasure = m_inputFilter->apply(m_currentValue, dt);

    float error = m_targetValue - m_filteredMeasure;

    m_integral += error * dt;

    float rawCorrection = m_kp * error + m_ki * m_integral;

    rawCorrection = clamp(rawCorrection);

    const float filtered = m_outputFilter->apply(rawCorrection, dt);

    // Anti-Windup : correct the integral using (filtered - raw)
    m_integral = m_antiwindup->correct(rawCorrection, filtered, m_integral, error, dt);

    m_correction = filtered;

    return m_correction;
}

void PIController::reset() {
    m_integral   = 0.0f;
    m_correction = 0.0f;
}


void PIController::setOutputLimits(float minOutput, float maxOutput) {
    m_minOutput = minOutput;
    m_maxOutput = maxOutput;
    m_hasLimits = true;
}

void PIController::removeOutputLimits() {
    m_minOutput = -std::numeric_limits<float>::infinity();
    m_maxOutput = std::numeric_limits<float>::infinity();
    m_hasLimits = false;
}


float PIController::clamp(float value) const {
    if (!m_hasLimits) {
        return value;
    }
    return std::max(m_minOutput, std::min(value, m_maxOutput));
}
