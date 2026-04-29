/**
 * @file PIController.cpp
 * @brief Implementation of the Proportional-Integral (PI) Controller for SISO systems
 */

#include "PIController.hpp"
#include <algorithm>

ControllerPtr create_pi_controller(float kp, float ki) {
    return new PIController(kp, ki);
}

ControllerPtr create_pi_controller_with_limits(float kp, float ki, float minOutput, float maxOutput) {
    return new PIController(kp, ki, minOutput, maxOutput);
}


PIController::PIController(float kp, float ki)
    : m_kp(kp),
      m_ki(ki),
      m_minOutput(-std::numeric_limits<float>::infinity()),
      m_maxOutput(std::numeric_limits<float>::infinity()),
      m_hasLimits(false),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_integral(0.0f),
      m_correction(0.0f)
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
      m_correction(0.0f)
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
    float error = m_targetValue - m_currentValue;

    m_integral += error * dt;

    float rawCorrection = m_kp * error + m_ki * m_integral;

    m_correction = clamp(rawCorrection);

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
