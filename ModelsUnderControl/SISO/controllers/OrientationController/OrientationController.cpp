/**
 * @file OrientationController.cpp
 * @brief Implementation of the OrientationController class for a SISO system
 */

#include "OrientationController.hpp"

OrientationController::OrientationController(): 
    targetValue(0.0f),
    correction(0.0f),
    currentValue(0.0f)
{
}

OrientationController::OrientationController(float targetValue): 
    targetValue(targetValue),
    correction(0.0f),
    currentValue(0.0f)
{
}

float OrientationController::getTargetValue() const {
    return targetValue;
}

float OrientationController::getCurrentValue() const {
    return currentValue;
}

float OrientationController::getCorrection() const {
    return correction;
}

void OrientationController::setTargetValue(float targetValue) {
    this->targetValue = targetValue;
}

void OrientationController::setCurrentValue(float currentValue) {
    this->currentValue = currentValue;
}


float OrientationController::compute(float dt) {
    correction = targetValue - currentValue;

    return correction;
}

OrientationPtr create_orientation(float targetValue) {
    return new OrientationController(targetValue);
}

float execute_orientation(OrientationPtr ptr, float targetValue, float currentValue) {
    ptr->setTargetValue(targetValue);
    ptr->setCurrentValue(currentValue);

    return ptr->compute(0);
}

float choisirEntre1et4() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(1, 4);

    return static_cast<float>(dist(gen));
}

double cast_as_float(float n) { return (double)n; }
