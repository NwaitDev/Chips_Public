#ifndef MPC_CONTROLLER_HPP
#define MPC_CONTROLLER_HPP

#include "../IControllerMPC.hpp"
#include <cmath>
#include <vector>

/**
 * @file MPCController.hpp
 * @brief Concrete implementation of the Model Predictive Controller
 *
 * This class implements the IControllerMPC interface using a State Space model approach.
 * It predicts the system's future behavior over a defined horizon to optimize the control input
 * while respecting physical constraints.
 */
class MPCController : public IControllerMPC {
private:
    /**
     * @brief System inertia coefficient (State Matrix A)
     * Model: y(k+1) = _a * y(k) + _b * u(k)
     */
    float _a = 0.9f; 

    /**
     * @brief Control input gain coefficient (Input Matrix B)
     */
    float _b = 0.1f; 

    /**
     * @brief Prediction Horizon (N)
     * Number of future time steps to simulate in the Receding Horizon loop.
     */
    int _horizon = 5; 
    
    /**
     * @brief Weight for tracking error (Q)
     * Higher value = Stricter adherence to the target.
     */
    float _weight_error = 1.0f;

    /**
     * @brief Weight for control effort (R)
     * Higher value = Smoother control changes, less aggressive actuator usage.
     */
    float _weight_effort = 0.1f;

    /**
     * @brief Minimum allowed control value (Actuator saturation low)
     */
    float _u_min = 0.0f;

    /**
     * @brief Maximum allowed control value (Actuator saturation high)
     */
    float _u_max = 1.0f;

    /**
     * @brief Minimum allowed output value (Safety Constraint low)
     */
    float _y_safe_min = -1000.0f; 

    /**
     * @brief Maximum allowed output value (Safety Constraint high)
     */
    float _y_safe_max = 1000.0f;

    /**
     * @brief Previous control input applied
     * Used to store the state of the controller between updates.
     */
    float _prev_u = 0.0f; 

public:
    /**
     * @brief Default constructor
     * Initializes parameters with safe default values.
     */
    MPCController();

    /**
     * @brief Default destructor
     */
    ~MPCController() override = default;

    /**
     * @brief Updates the internal State Space model parameters
     * @param a Inertia coefficient
     * @param b Input gain coefficient
     */
    void setModelParams(float a, float b) override;
    
    /**
     * @brief Sets the prediction horizon depth
     * @param N Number of steps (must be >= 1)
     */
    void setPredictionHorizon(int N) override;
    
    /**
     * @brief Configures all physical constraints
     * @param u_min Minimum control signal
     * @param u_max Maximum control signal
     * @param y_safe_min Minimum safety threshold for system output
     * @param y_safe_max Maximum safety threshold for system output
     */
    void setConstraints(float u_min, float u_max, float y_safe_min, float y_safe_max) override;

    /**
     * @brief Sets the optimization weights
     * @param Q_error Priority on target tracking
     * @param R_effort Priority on energy saving/smoothness
     */
    void setWeights(float Q_error, float R_effort) override;
    
    /**
     * @brief Computes the optimal control signal
     * Uses analytic prediction and receding horizon safety checks.
     * @param current_val Current system measurement
     * @param target_val Desired target
     * @return float Optimal control command u
     */
    float compute(float current_val, float target_val) override;

    /**
     * @brief Resets the controller state
     */
    void reset() override;
};

#endif