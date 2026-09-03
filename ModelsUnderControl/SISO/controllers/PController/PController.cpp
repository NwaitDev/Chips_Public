/**
 * @file PController.cpp
 * @brief Implementation of the Proportional (P) SISO Controller
 */

#include "PController.hpp"
#include "../../../Filters/StatelessFilter/PassThrough/PassThroughFilter.hpp"
#include "../../../AntiWindup/StatelessAntiWindup/NoAntiWindup/NoAntiWindup.hpp"
#include <algorithm>

ControllerPtr create_p_controller(float kp) {
    return new PController(kp);
}

ControllerPtr create_p_controller_with_limits(float kp, float minOutput, float maxOutput) {
    return new PController(kp, minOutput, maxOutput);
}

// PController::PController(float kp)
//     : m_kp(kp),
//       m_minOutput(-std::numeric_limits<float>::infinity()),
//       m_maxOutput(std::numeric_limits<float>::infinity()),
//       m_hasLimits(false),
//       m_targetValue(0.0f),
//       m_currentValue(0.0f),
//       m_correction(0.0f),
//       m_inputFilter(std::make_shared<PassThroughFilter>()),
//       m_outputFilter(std::make_shared<PassThroughFilter>())
// {
// }

PController::PController(float kp, float minOutput, float maxOutput)
    : m_kp(kp),
      m_minOutput(minOutput),
      m_maxOutput(maxOutput),
      m_hasLimits(true),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_correction(0.0f),
      m_filteredMeasure(0.0f),
      m_inputFilter(std::make_shared<PassThroughFilter>()),
      m_outputFilter(std::make_shared<PassThroughFilter>()),
      m_antiWindup(std::make_shared<NoAntiWindup>())
{
}

PController::PController(float kp, std::shared_ptr<IFilter> inputFilter, std::shared_ptr<IFilter> outputFilter, std::shared_ptr<IAntiWindup> antiwindup)
    : m_kp(kp),
      m_targetValue(0.0f),
      m_currentValue(0.0f),
      m_correction(0.0f),
      m_filteredMeasure(0.0f),
      m_inputFilter(inputFilter ? std::move(inputFilter)
                                : std::make_shared<PassThroughFilter>()),
      m_outputFilter(outputFilter ? std::move(outputFilter)
                                  : std::make_shared<PassThroughFilter>()),
      m_antiWindup(antiwindup ? std::move(antiwindup)
                              : std::make_shared<NoAntiWindup>()){}

void PController::setInputFilter(std::shared_ptr<IFilter> inputFilter) {
    m_inputFilter = inputFilter ? std::move(inputFilter)
                                : std::make_shared<PassThroughFilter>();
}

void PController::setOutputFilter(std::shared_ptr<IFilter> outputFilter) {
    m_outputFilter = outputFilter ? std::move(outputFilter)
                                  : std::make_shared<PassThroughFilter>();
}

void PController::setAntiWindup(std::shared_ptr<IAntiWindup> antiwindup){
    m_antiWindup = antiwindup ? std::move(antiwindup)
                              : std::make_shared<NoAntiWindup>();
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


float PController::compute(float dt) {

    m_filteredMeasure = m_inputFilter->apply(m_currentValue, dt);

    float error = m_targetValue - m_filteredMeasure;
    float rawCorrection = m_kp * error;

    rawCorrection = clamp(rawCorrection);

    const float filtered = m_outputFilter->apply(rawCorrection, dt);

    m_correction = filtered;
    
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