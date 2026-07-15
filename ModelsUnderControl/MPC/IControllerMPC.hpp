#ifndef ICONTROLLER_MPC_HPP
#define ICONTROLLER_MPC_HPP

#include <vector>

/**
 * @file IControllerMPC.hpp
 * @brief Interface for Model Predictive Controllers (MPC)
 *
 * This interface defines the standard API for MPC implementations using State Space models.
 * It includes methods to define the system model, set physical constraints (Safety & Actuator),
 * configure the prediction horizon, and tune the optimization weights (Q & R).
 */
class IControllerMPC {
    public:
        /**
         * @brief Set the State Space model parameters
         *
         * Configures the internal physical model of the system: y(k+1) = a*y(k) + b*u(k)
         *
         * @param a The system inertia coefficient (State Matrix A)
         * @param b The control gain coefficient (Input Matrix B)
         */
        virtual void setModelParams(float a, float b) = 0;
        
        /**
         * @brief Set the prediction horizon (Receding Horizon)
         *
         * Defines how many steps into the future the controller predicts.
         * Note: A larger horizon improves stability but increases computation time.
         *
         * @param N The number of time steps to predict
         */
        virtual void setPredictionHorizon(int N) = 0;

        /**
         * @brief Set the physical constraints of the system
         *
         * Defines the limits for both the actuator (u) and the system output (y).
         *
         * @param u_min Minimum control signal allowed
         * @param u_max Maximum control signal allowed
         * @param y_safe_min Minimum safe output value (Zone Rouge low)
         * @param y_safe_max Maximum safe output value (Zone Rouge high)
         */
        virtual void setConstraints(float u_min, float u_max, float y_safe_min, float y_safe_max) = 0;

        /**
         * @brief Set the optimization weights (Cost Function)
         *
         * Tunes the trade-off between tracking accuracy and energy expenditure.
         *
         * @param Q_error Weight for the tracking error (Importance of reaching target)
         * @param R_effort Weight for the control effort (Importance of minimizing changes/energy)
         */
        virtual void setWeights(float Q_error, float R_effort) = 0;

        /**
         * @brief Compute the optimal control output
         *
         * Uses the model and horizon to predict the future and calculate the best
         * control input to reach the target while respecting constraints.
         *
         * @param current_val The current measured value of the system
         * @param target_val The desired target value (setpoint)
         * @return float The computed control output (u)
         */
        virtual float compute(float current_val, float target_val) = 0;

        /**
         * @brief Reset the controller state
         *
         * Clears internal memory (e.g., previous control values) to restart the control process.
         */
        virtual void reset() = 0;

        /**
         * @brief Virtual destructor for proper cleanup of derived classes
         */
        virtual ~IControllerMPC() = default;
};

#endif