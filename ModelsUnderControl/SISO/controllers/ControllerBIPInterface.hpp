#ifndef CONTROLLER_BIP_INTERFACE_HPP
#define CONTROLLER_BIP_INTERFACE_HPP

#include "../IControllerSISO.hpp"

/**
 * @file ControllerBIPInterface.hpp
 * @brief C++ interface for BIP to interact with SISO controllers
 *
 * This interface provides functions to create, execute, reset, and destroy SISO controllers (P, PI, PID) from BIP.
 * It also includes utility functions to get controller values and convert floats to doubles for BIP compatibility.
 *
 */

typedef IControllerSISO* ControllerPtr;

float execute_controller(ControllerPtr controller, float targetValue, float currentValue, float dt);

/**
 * @brief Execute the controller with a default time step of 1.0f
 *
 * @param controller Pointer to the controller object
 * @param targetValue Desired target value
 * @param currentValue Current measured value
 * @return Computed control output, or 0.0f if the controller is null
 */
float execute_controller_simple(ControllerPtr controller, float targetValue, float currentValue);

/**
 * @brief Reset the controller state
 *
 * @param controller Pointer to the controller object
 */
void reset_controller(ControllerPtr controller);

/**
 * @brief Destroy the controller object and free resources
 *
 * @param controller Pointer to the controller object
 */
void destroy_controller(ControllerPtr controller);

/**
 * @brief Get the controller correction object
 *
 * @param controller Pointer to the controller object
 * @return float The current correction value of the controller
 */
float get_controller_correction(ControllerPtr controller);

/**
 * @brief Get the controller target value
 *
 * @param controller Pointer to the controller object
 * @return float The current target value of the controller
 */
float get_controller_target(ControllerPtr controller);

/**
 * @brief Get the controller current value
 *
 * @param controller Pointer to the controller object
 * @return float The current measured value of the controller
 */
float get_controller_current(ControllerPtr controller);

/**
 * @brief Cast a float to double for BIP compatibility
 *
 * @param n The float value to cast
 * @return double The casted double value
 */
double cast_as_float(float n);

#endif