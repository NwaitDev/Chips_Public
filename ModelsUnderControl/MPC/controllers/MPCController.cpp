/**
 * @file MPCController.cpp
 * @brief Implementation of the core Model Predictive Control logic
 *
 * This file contains the mathematical implementation of the MPC algorithm,
 * including the State Space prediction, the Receding Horizon optimization,
 * and the safety constraint handling.
 */

#include "MPCController.hpp"
#include <algorithm>

/**
 * @brief Default constructor
 */
MPCController::MPCController() {}

/**
 * @brief Configures the internal State Space model
 *
 * Sets the physical parameters of the system: y(k+1) = a*y(k) + b*u(k).
 *
 * @param a The inertia coefficient (State matrix A)
 * @param b The input gain coefficient (Input matrix B)
 */
void MPCController::setModelParams(float a, float b) {
    _a = a;
    _b = b;
}

/**
 * @brief Sets the length of the prediction horizon
 *
 * @param N The number of time steps into the future to predict.
 * If N < 1, it is clamped to 1.
 */
void MPCController::setPredictionHorizon(int N) {
    if (N < 1) _horizon = 1;
    else _horizon = N;
}

/**
 * @brief Defines physical and safety constraints
 *
 * @param u_min Minimum command value (Actuator saturation)
 * @param u_max Maximum command value (Actuator saturation)
 * @param y_safe_min Minimum allowed output value (Safety threshold)
 * @param y_safe_max Maximum allowed output value (Safety threshold)
 */
void MPCController::setConstraints(float u_min, float u_max, float y_safe_min, float y_safe_max) {
    _u_min = u_min;
    _u_max = u_max;
    _y_safe_min = y_safe_min;
    _y_safe_max = y_safe_max;
}

/**
 * @brief Tunes the cost function weights
 *
 * @param Q_error Weight applied to the tracking error (Target - Current)
 * @param R_effort Weight applied to the control effort (Regularization)
 */
void MPCController::setWeights(float Q_error, float R_effort) {
    _weight_error = Q_error;
    _weight_effort = R_effort;
}

/**
 * @brief Core MPC algorithm: Computes the optimal control signal
 *
 * The computation is performed in three steps:
 * 1. **Unconstrained Optimization:** Calculates the ideal 'u' that minimizes the error
 * over the horizon using an analytic Least Squares solution based on the Free Response.
 * 2. **Predictive Safety Check:** Simulates the future trajectory with this ideal 'u'.
 * If the predicted curve violates safety limits (Receding Horizon Check),
 * a "Rescue" command is calculated to keep the system on the boundary.
 * 3. **Actuator Saturation:** Clamps the final result between u_min and u_max.
 *
 * @param current_val The current state of the system
 * @param target_val The target setpoint
 * @return float The optimal control command to apply for the next step
 */
float MPCController::compute(float current_val, float target_val) {
    double numerator = 0.0;
    double denominator = 0.0;
    
    // --- Step 1: Analytic Solution for Unconstrained Optimal Control ---
    double free_response = current_val;
    
    for (int k = 1; k <= _horizon; ++k) {
        // Predict evolution without new input (Free Response)
        free_response = _a * free_response; 
        
        // Calculate influence of input 'u' over time (Geometric sum)
        double influence_u = 0.0;
        double a_pow = 1.0;
        for(int j=0; j<k; j++) {
            influence_u += a_pow * _b;
            a_pow *= _a;
        }

        double error_free = target_val - free_response;
        
        // Accumulate terms for Least Squares optimization
        numerator   += (error_free * influence_u) * _weight_error;
        denominator += (influence_u * influence_u) * _weight_error;
    }

    // Add regularization term (R)
    denominator += _weight_effort;

    double u_optimal = 0.0;
    if (std::abs(denominator) > 1e-6) {
        u_optimal = numerator / denominator;
    }

    // --- Step 2: Predictive Safety Constraints (The "Curve" Check) ---
    double temp_state = current_val;
    
    for (int k = 1; k <= _horizon; ++k) {
        // Project future state
        temp_state = (_a * temp_state) + (_b * u_optimal);
        
        // Check Low Safety Limit
        if (temp_state < _y_safe_min) {
            // Calculate rescue command to land exactly on the limit
            double u_rescue = (_y_safe_min - (_a * current_val)) / _b;
            // Apply the most restrictive constraint (closest to safety)
            if (u_rescue > u_optimal) u_optimal = u_rescue;
        }
        
        // Check High Safety Limit
        if (temp_state > _y_safe_max) {
             double u_rescue = (_y_safe_max - (_a * current_val)) / _b;
             if (u_rescue < u_optimal) u_optimal = u_rescue;
        }
    }

    // --- Step 3: Actuator Saturation ---
    if (u_optimal > _u_max) u_optimal = _u_max;
    if (u_optimal < _u_min) u_optimal = _u_min;

    _prev_u = static_cast<float>(u_optimal);
    return _prev_u;
}

/**
 * @brief Resets the internal controller state
 *
 * Sets the previous command memory to 0.
 */
void MPCController::reset() {
    _prev_u = 0.0f;
}