#ifndef ICONTROLLER_MIMO_HPP
#define ICONTROLLER_MIMO_HPP

#include <vector>

/**
 * @brief Generic interface for a discrete-time MIMO state-feedback controller.
 *
 * This interface is intentionally close in spirit to the SISO and MPC controllers in this project:
 * - you set a target (reference) vector and the current measured output/state,
 * - you call compute(dt) and obtain a correction (control) vector.
 */
class IControllerMIMO {
public:
    /**
     * @brief Get the state size object
     * 
     * @return int State size
     */
    virtual int getStateSize() const = 0;

    /**
     * @brief Get the input size object
     * 
     * @return int Input size
     */
    virtual int getInputSize() const = 0;

    /**
     * @brief Get the output size object
     * 
     * @return int Output size
     */
    virtual int getOutputSize() const = 0;

    /**
     * @brief Get the target object
     * 
     * @return const std::vector<float>& Target vector
     */
    virtual const std::vector<float>& getTarget() const = 0;

    /**
     * @brief Get the current output object
     * 
     * @return const std::vector<float>& Current output vector
     */
    virtual const std::vector<float>& getCurrentOutput() const = 0;

    /**
     * @brief Get the current state object
     * 
     * @return const std::vector<float>& Current state vector
     */
    virtual const std::vector<float>& getCurrentState() const = 0;

    /**
     * @brief Get the control object
     * 
     * @return const std::vector<float>& Control vector
     */
    virtual const std::vector<float>& getControl() const = 0;

    /**
     * @brief Set the target object
     * 
     * @param r Target vector
     */
    virtual void setTarget(const std::vector<float>& r) = 0;

    /**
     * @brief Set the current output object
     * 
     * @param y Current output vector
     */
    virtual void setCurrentOutput(const std::vector<float>& y) = 0;

    /**
     * @brief Set the current state object
     * 
     * @param x Current state vector
     */
    virtual void setCurrentState(const std::vector<float>& x) = 0;

    /**
     * @brief Compute the control vector based on the current state and target
     *
     * @param dt Time step
     * @return std::vector<float> Control vector
     */
    virtual std::vector<float> compute(float dt) = 0;

    /**
     * @brief Reset the controller's internal state
     */
    virtual void reset() = 0;

    /**
     * @brief Destroy the IControllerMIMO object
     */
    virtual ~IControllerMIMO() = default;
};

#endif
