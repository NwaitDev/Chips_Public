/**
 * @file PController.cpp
 * @brief Implementation of the Proportional (P) SISO Controller
 */

#include "PController.hpp"
#include <algorithm>

ControllerPtr create_p_controller(float kp) {
    return new PController(kp);
}

ControllerPtr create_p_controller_with_limits(float kp, float minOutput, float maxOutput) {
    return new PController(kp, minOutput, maxOutput);
}

PController::PController(float kp)
    : m_kp(kp),
      m_minOutput(-std::numeric_limits<float>::infinity()),
      m_maxOutput(std::numeric_limits<float>::infinity()),
      m_hasLimits(false),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_correction(0.0f)
{
}

PController::PController(float kp, float minOutput, float maxOutput)
    : m_kp(kp),
      m_minOutput(minOutput),
      m_maxOutput(maxOutput),
      m_hasLimits(true),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_correction(0.0f)
{
}


float PController::getTargetValue() const {
    return m_targetValue;
}

float PController::getCurrentValue() const {
    return m_currentValue;
}

float PController::getCorrection() const {
    return m_correction;
}


void PController::setTargetValue(float targetValue) {
    m_targetValue = targetValue;
}

void PController::setCurrentValue(float currentValue) {
    m_currentValue = currentValue;
}

void PController::setOutputLimits(float minOutput, float maxOutput) {
    m_minOutput = minOutput;
    m_maxOutput = maxOutput;
    m_hasLimits = true;
}


float PController::compute(float /*dt*/) {
    float error = m_targetValue - m_currentValue;
    float rawCorrection = m_kp * error;
    m_correction = clamp(rawCorrection);
    
    return m_correction;
}

void PController::reset() {
    m_correction = 0.0f;
}

void PController::removeOutputLimits() {
    m_minOutput = -std::numeric_limits<float>::infinity();
    m_maxOutput = std::numeric_limits<float>::infinity();
    m_hasLimits = false;
}

float PController::clamp(float value) const {
    if (!m_hasLimits) {
        return value;
    }
    
    return std::max(m_minOutput, std::min(value, m_maxOutput));
}