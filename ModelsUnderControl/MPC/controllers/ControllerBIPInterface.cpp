/**
 * @file ControllerBIPInterface.cpp
 * @brief Implementation of the MPC wrapper for the BIP project
 *
 * This file implements the high-level interface used to bridge the
 * generic MPC logic with the specific requirements of the BIP system.
 */

#include "ControllerBIPInterface.hpp"

/**
 * @brief Constructor
 *
 * Instantiates the underlying MPC controller and initializes the target to 0.
 */
ControllerBIPInterface::ControllerBIPInterface() : _target(0.0f) {
    _mpc = std::make_unique<MPCController>();
}

/**
 * @brief Initializes the MPC configuration with default parameters
 *
 * Sets up a standard first-order system model (a=0.9, b=0.1), default weights
 * prioritizing error tracking, and open constraints.
 *
 * @param horizon The prediction horizon depth (N) to be used by the Receding Horizon algorithm.
 */
void ControllerBIPInterface::init(int horizon) {
    // Default model parameters (High inertia assumption)
    _mpc->setModelParams(0.9f, 0.1f);

    _mpc->setPredictionHorizon(horizon);

    // Default weights: Q=1.0 (Error priority), R=0.1 (Low effort penalty)
    _mpc->setWeights(1.0f, 0.1f);

    // Default constraints: Motor 0-100%, No output safety limits initially
    _mpc->setConstraints(0.0f, 1.0f, -99999.0f, 99999.0f);
}

/**
 * @brief Updates the physical model of the system
 *
 * Allows dynamic tuning of the internal State Space model (y_k+1 = a*y_k + b*u_k).
 *
 * @param a The inertia coefficient (State matrix)
 * @param b The input gain coefficient (Input matrix)
 */
void ControllerBIPInterface::setSystemModel(float a, float b) {
    _mpc->setModelParams(a, b);
}

/**
 * @brief Sets the desired setpoint
 *
 * @param value The target value the controller should aim for
 */
void ControllerBIPInterface::setTarget(float value) {
    _target = value;
}

/**
 * @brief Configures safety constraints for the system output
 *
 * Defines the "Safe Zone". The controller will try to keep the system output
 * within [min, max]. Motor commands remain constrained between 0.0 and 1.0.
 *
 * @param min The minimum safe output value (e.g., minimum battery voltage)
 * @param max The maximum safe output value
 */
void ControllerBIPInterface::setSafetyLimits(float min, float max) {
    _mpc->setConstraints(0.0f, 1.0f, min, max);
}

/**
 * @brief Main control loop update
 *
 * Computes the next control action based on the latest measurement and the current target.
 *
 * @param measurement The latest physical measurement from the sensors
 * @return float The optimal control command (u) computed by the MPC
 */
float ControllerBIPInterface::update(float measurement) {
    return _mpc->compute(measurement, _target);
}