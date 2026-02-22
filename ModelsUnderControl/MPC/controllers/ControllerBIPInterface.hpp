#ifndef CONTROLLER_BIP_INTERFACE_HPP
#define CONTROLLER_BIP_INTERFACE_HPP

#include "MPCController.hpp"
#include <memory>

/**
 * @file ControllerBIPInterface.hpp
 * @brief Wrapper interface for the BIP project MPC controller
 *
 * This class acts as a high-level abstraction layer (Facade) for the MPC logic.
 * It simplifies the interaction with the MPCController by encapsulating
 * initialization, parameter tuning, and the control loop update specifically
 * configured for the BIP robot/system.
 */
class ControllerBIPInterface {
private:
    /**
     * @brief Pointer to the actual MPC logic implementation
     */
    std::unique_ptr<MPCController> _mpc;

    /**
     * @brief Current target value (setpoint)
     */
    float _target;

public:
    /**
     * @brief Default constructor
     *
     * Instantiates the internal MPCController object.
     */
    ControllerBIPInterface();

    /**
     * @brief Default destructor
     */
    ~ControllerBIPInterface() = default;

    /**
     * @brief Initializes the controller with default or specific parameters
     *
     * Sets up the weights, constraints, and system model with default values
     * suitable for the BIP system.
     *
     * @param horizon The number of steps for the prediction horizon (default is 10).
     */
    void init(int horizon = 10);

    /**
     * @brief Updates the physical system model
     *
     * Allows manual tuning of the State Space model parameters: y(k+1) = a*y(k) + b*u(k)
     *
     * @param a System inertia coefficient
     * @param b Control input gain coefficient
     */
    void setSystemModel(float a, float b);

    /**
     * @brief Sets the desired target value
     *
     * @param value The setpoint the controller should aim for (e.g., 5.0V)
     */
    void setTarget(float value);

    /**
     * @brief Defines the safety limits for the system output
     *
     * Configures the hard constraints on the output variable (y) to prevent
     * physical damage (e.g., keeping voltage above a minimum threshold).
     *
     * @param min Minimum safe value
     * @param max Maximum safe value
     */
    void setSafetyLimits(float min, float max);

    /**
     * @brief Main control loop method
     *
     * Calculates the optimal control signal based on the current measurement
     * and the internal target state.
     *
     * @param measurement The current value read from the system sensors
     * @return float The computed control command (u) to apply to the actuators
     */
    float update(float measurement);
};

#endif