#pragma once
#include "../IControllerSISO.hpp"
#include <optional>
#include <random>

/**
 * @file OrientationController.hpp
 * @brief Implementation of a simple orientation controller for a SISO system
 * 
 * This controller computes the correction needed to reach a target orientation based on the current orientation. 
 * It provides methods to set and get the target and current values, as well as to compute the correction. 
 * The controller can be used in a SISO control loop to adjust the orientation of a system towards a desired setpoint.
 */
class OrientationController : public IControllerSISO {
    private:
        float targetValue;  // Desired orientation (setpoint)
        float correction;   // Computed correction to apply
        float currentValue; // Current orientation 
    public:
        /**
         * @brief Construct a new Orientation Controller object
         */
        OrientationController();

        /**
         * @brief Construct a new Orientation Controller object with a specified target value
         * 
         * @param targetValue The desired orientation (setpoint)
         */
        OrientationController(float targetValue);

        /**
         * @brief Get the target value object
         * 
         * @return float The current target value (setpoint)
         */
        float getTargetValue() const override;

        /**
         * @brief Get the current value object
         * 
         * @return float The current measured value
         */
        float getCurrentValue() const override;

        /**
         * @brief Get the correction object
         * 
         * @return float The current controller output (correction)
         */
        float getCorrection() const override;

        /**
         * @brief Set the target value object
         * 
         * @param targetValue The desired setpoint value
         */
        void setTargetValue(float targetValue) override;

        /**
         * @brief Set the current value object
         * 
         * @param currentValue The measured value from the system
         */
        void setCurrentValue(float currentValue) override;

        /**
         * @brief Compute the correction based on the current and target values
         * 
         * The correction is calculated as the difference between the target value and the current value.
         * 
         * @param dt The time step for the computation
         * @return float The computed correction
         */
        float compute(float dt) override;
};

/** 
 * @brief Enumeration for cardinal orientations
 */
enum Orientation { Nord = 1, Est = 2, Sud = 3, Ouest = 4 };

typedef OrientationController* OrientationPtr;

/**
 * @brief Create a orientation object
 * 
 * @param targetValue The desired target orientation
 * @return OrientationPtr A pointer to the created orientation controller
 */
OrientationPtr create_orientation(float targetValue);

/**
 * @brief Execute the orientation controller by setting the target and current values, then computing the correction
 * 
 * @param ptr           A pointer to the orientation controller
 * @param targetValue   The desired target orientation
 * @param currentValue  The current measured orientation
 * @return float The computed correction
 */
float execute_orientation(
    OrientationPtr ptr, 
    float targetValue,
    float currentValue
);

/**
 * @brief Choose a random orientation between 1 and 4 corresponding to the cardinal directions
 * 
 * @return float A random orientation value between 1 and 4
 */
float choisirEntre1et4();

/**
 * @brief Cast a float value to double
 * 
 * @param n The float value to cast
 * @return double The casted double value
 */
double cast_as_float(float n);
