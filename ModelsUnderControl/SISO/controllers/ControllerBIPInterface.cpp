/**
 * @file ControllerBIPInterface.cpp
 * @brief C++ interface implementation for BIP to interact with SISO controllers
*/

#include "ControllerBIPInterface.hpp"
#include "PController/PController.hpp"
#include "PIController/PIController.hpp"
#include "PIDController/PIDController.hpp"


float execute_controller(ControllerPtr controller, float targetValue, float currentValue, float dt) {
    if (controller == nullptr) {
        return 0.0f;
    }

    controller->setTargetValue(targetValue);
    controller->setCurrentValue(currentValue);

    return controller->compute(dt);
}

float execute_controller_simple(ControllerPtr controller, float targetValue, float currentValue) {
    return execute_controller(controller, targetValue, currentValue, 1.0f);
}

void reset_controller(ControllerPtr controller) {
    if (controller != nullptr) {
        controller->reset();
    }
}

void destroy_controller(ControllerPtr controller) {
    if (controller != nullptr) {
        delete controller;
    }
}

float get_controller_correction(ControllerPtr controller) {
    if (controller == nullptr) {
        return 0.0f;
    }
    return controller->getCorrection();
}

float get_controller_target(ControllerPtr controller) {
    if (controller == nullptr) {
        return 0.0f;
    }
    return controller->getTargetValue();
}

float get_controller_current(ControllerPtr controller) {
    if (controller == nullptr) {
        return 0.0f;
    }
    return controller->getCurrentValue();
}

double cast_as_float(float n) {
    return static_cast<double>(n);
}