#ifndef ALPHA_BETA_FILTER_HPP
#define ALPHA_BETA_FILTER_HPP

#include "../StatefulFilter.hpp"
#include <stdexcept>

/**
 * @brief Alpha-Beta (g-h) tracker - 2-state observer : position + velocity
 * 
 * At each step the filter:
 *  1. Predicts the next state using the estimated velocity
 *  2. Computes the redisudal (measurement - prediction)
 *  3. Corrects position and velocity with gains alpha and beta
 * 
 * Equations:
 * @code
 *  // Predict
 *  x_pred = x_est + dt * y_est
 *  y_pred = y_est
 * 
 *  // Residual
 *  r = measurement - x_pred
 * 
 *  // Correct
 *  x_est = x_pred + alpha * r
 *  y_est = y_pred + (beta / dt) *r
 * @endcode
 * 
 * Parameter guidelines:
 *  - alpha ∈ (0, 1) : position smoothing. Closer to 1 -> faster tracking
 *                                         closer to 0 -> stronger smoothing
 *  - beta ∈ (0, 1)  : velocity smoothing. beta <= alpha(2-alpha) ensures stability
 *                      A common critically-damped choice: beta = alpha² / (2-alpha)
 * 
 * Typical use case: smooth a position/angle sensor while estimating the underlying
 * velocity - feeds the velocity estimate back to the controller via getVelocity() to
 * avoid a separate noisy derivative term.
 * 
 * @param alpha Position correction gain ∈ (0, 1)
 * @param beta  Velocity correction gain ∈ (0, 1)
 */
class AlphaBetaFilter : public StatefulFilter {
    private:
        float m_alpha, m_beta;
        float m_position, m_velocity;

        static void validateParams(float a, float b){
            if(a < 0.f || a > 1.f){
                throw std::invalid_argument("AlphaBetaFilter: alpha must be in (0, 1)");
            }
            if(b < 0.f || b > 1.f){
                throw std::invalid_argument("AlphaBetaFilter: beta must be in (0, 1)");
            }
        }

    public:
        AlphaBetaFilter(float alpha, float beta) 
            : m_alpha(alpha), m_beta(beta),
              m_position(0.f), m_velocity(0.f){
            validateParams(alpha, beta);
        }


        float getVelocity() const { return m_velocity; }

        void setAlpha(float a){
            validateParams(a, m_beta);
            m_alpha = a;
        }

        void setBeta(float b){
            validateParams(m_alpha, b);
            m_beta = b;
        }

        float getAlpha() const { return m_alpha; }
        float getBeta() const { return m_beta; }
        
        /**
         * @brief Compute the critically-damped beta from alpha: beta = alpha² / (2-alpha)
         * 
         * Convenience factory: AlphaBetaFilter f = AlphaBetaFilter::criticallyDamped(0.85f);
         */
        static AlphaBetaFilter criticallyDamped(float alpha){
            const float beta = (alpha * alpha) / (2.f - alpha);
            return AlphaBetaFilter(alpha, beta);
        }
    
    protected:
        
        float applyImpl(float measure, float dt) override {
            // Predict
            const float x_pred = m_position + dt * m_velocity;

            // Residual
            const float r = measure - x_pred;

            // Correct
            m_position = x_pred + m_alpha * r;
            m_velocity = m_velocity + (m_beta / dt) * r;

            return m_position;
        }

        void seedState(float v) override {
            m_position = v;
            m_velocity = 0.f;
        }
        void resetState() override {
            m_position = 0.f;
            m_velocity = 0.f;
        }
};

#endif