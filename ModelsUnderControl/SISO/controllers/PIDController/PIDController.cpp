/**
 * @file PIDController.cpp
 * @brief Implementation of the Proportional-Integral-Derivative (PID) Controller for SISO systems
 */

#include "PIDController.hpp"
#include <iostream>

ControllerPtr create_pid_controller(float kp, float ki, float kd) {
    return new PIDController(kp, ki, kd);
}

ControllerPtr create_pid_controller_with_limits(float kp, float ki, float kd, float minOutput, float maxOutput) {
    return new PIDController(kp, ki, kd, minOutput, maxOutput);
}

PIDController::PIDController(float kp, float ki, float kd) 
    : m_kp(kp),
      m_ki(ki), 
      m_kd(kd), 
      m_minOutput(-std::numeric_limits<float>::infinity()),
      m_maxOutput(std::numeric_limits<float>::infinity()),
      m_hasLimits(false),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_integral(0.0f),
      m_correction(0.0f),
      m_prevError(0.0f)
{
}

PIDController::PIDController(float kp, float ki, float kd, float minOutput, float maxOutput) 
    : m_kp(kp),
      m_ki(ki), 
      m_kd(kd), 
      m_minOutput(minOutput),
      m_maxOutput(maxOutput),
      m_hasLimits(true),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_integral(0.0f),
      m_correction(0.0f),
      m_prevError(0.0f)
{
}

float PIDController::getTargetValue() const {
    return m_targetValue;
}

float PIDController::getCurrentValue() const {
    return m_currentValue;
}

float PIDController::getCorrection() const {
    return m_correction;
}

void PIDController::setTargetValue(float targetValue) {
    m_targetValue = targetValue;
}

void PIDController::setCurrentValue(float currentValue) {
    m_currentValue = currentValue;
}

float PIDController::compute(float dt) {
    // 1. Erreur
    float error = m_targetValue - m_currentValue;

    // 2. Terme P
    float p_out = m_kp * error;

    // 3. Terme I
    m_integral += error * dt;
    float i_out = m_ki * m_integral;

    // 4. Terme D
    float derivative = 0.0f;
    if (dt > 0.0f) {
        derivative = (error - m_prevError) / dt;
    }
    float d_out = m_kd * derivative;

    // 5. Sortie
    m_correction = clamp(p_out + i_out + d_out);

    // 6. Mémoire
    m_prevError = error;

    return m_correction;
}

void PIDController::reset() {
    m_integral   = 0.0f;
    m_prevError  = 0.0f;
    m_correction = 0.0f;
}

void PIDController::setOutputLimits(float minOutput, float maxOutput) {
    m_minOutput = minOutput;
    m_maxOutput = maxOutput;
    m_hasLimits = true;
}

void PIDController::removeOutputLimits() {
    m_minOutput = -std::numeric_limits<float>::infinity();
    m_maxOutput = std::numeric_limits<float>::infinity();
    m_hasLimits = false;
}


float PIDController::clamp(float value) const {
    if (!m_hasLimits) {
        return value;
    }
    return std::max(m_minOutput, std::min(value, m_maxOutput));
}