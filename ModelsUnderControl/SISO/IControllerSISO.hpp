#ifndef ICONTROLLERSISO_H
#define ICONTROLLERSISO_H

/**
 * @file IControllerSISO.hpp
 * @brief Interface for Single Input Single Output (SISO) Controllers
 * 
 * This interface defines the basic structure and functionality for SISO controllers, 
 * including methods to get and set target and current values, compute control outputs, and reset the controller state.
 * 
 * The interface defines the common API shared by all SISO controllers (PController, PIController, PIDController, OrientationController, etc.)
 */
class IControllerSISO {
    public:
        /**
         * @brief Get the target value object
         * 
         * @return float The current target value (setpoint)
         */
        virtual float getTargetValue() const = 0;

        /**
         * @brief Get the current value object
         * 
         * @return float The current measured value
         */
        virtual float getCurrentValue() const = 0;

        /**
         * @brief Get the correction object
         * 
         * @return float The current controller output (correction)
         */
        virtual float getCorrection() const = 0;

        /**
         * @brief Set the target value object
         * 
         * @param targetValue The desired setpoint value
         */
        virtual void setTargetValue(float targetValue) = 0;

        /**
         * @brief Set the current value object
         * 
         * @param currentValue The measured value from the system
         */
        virtual void setCurrentValue(float currentValue) = 0;

        /**
         * @brief Compute the control output based on the current error
         * 
         * @param dt Time step
         * @return float The computed control output (correction)
         */
        virtual float compute(float dt) = 0;

        /**
         * @brief Reset the controller state
         */
        virtual void reset() = 0; 

        /**
         * @brief Virtual destructor for proper cleanup of derived classes
         */
        virtual ~IControllerSISO() = default;
};

#endif