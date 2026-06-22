#ifndef ALPHA_BETA_GAMMA_FILTER_HPP
#define ALPHA_BETA_GAMMA_FILTER_HPP

#include "../StatefulFilter.hpp"
#include <stdexcept>

/**
 * @brief Alpha-Beta-Gamma (g-h-k) tracker - 3-state observer:
 *        position + velocity + acceleration.
 *
 * Extension of the Alpha-Beta filter with a third correction term gamma for
 * acceleration.  Better suited to signals with non-constant velocity
 * (e.g. drone altitude, robot arm with varying load).
 *
 * Equations:
 * @code
 *   // Predict
 *   x_pred = x_est + dt*v_est + 0.5*dt²*a_est
 *   v_pred = v_est + dt*a_est
 *   a_pred = a_est
 *
 *   // Residual
 *   r = measurement - x_pred
 *
 *   // Correct
 *   x_est = x_pred +  alpha         * r
 *   v_est = v_pred + (beta / dt)   * r
 *   a_est = a_pred + (gamma / dt²)  * r    // note: 2gamma in some formulations
 * @endcode
 *
 * Parameter guidelines (Benedict-Bordner optimum for white noise):
 *   beta = alpha(2 − alpha) / 2
 *   gamma = beta² / (2alpha)   →   use the static factory `whitenoise()` for this.
 *
 * @param alpha  Position gain  ∈ (0, 1)
 * @param beta   Velocity gain  ∈ (0, 1)
 * @param gamma  Acceleration gain ∈ (0, 2)
 */
class AlphaBetaGammaFilter : public StatefulFilter{
    private:
        float m_alpha, m_beta, m_gamma;
        float m_position, m_velocity, m_accel;

        static void validateParams(float a, float b, float g){
            if(a < 0.f || a > 1.f){
                throw std::invalid_argument("AlphaBetaGammaFilter: alpha must be in (0, 1)");
            }
            if(b < 0.f || b > 1.f){
                throw std::invalid_argument("AlphaBetaGammaFilter: beta must be in (0, 1)");
            }
            if(g < 0.f || g > 2.f){
                throw std::invalid_argument("AlphaBetaGammaFilter: gamma must be in (0, 2)");
            }
        }

    public:
        AlphaBetaGammaFilter(float alpha, float beta, float gamma)
            : m_alpha(alpha), m_beta(beta), m_gamma(gamma),
              m_position(0.f), m_velocity(0.f), m_accel(0.f){
            validateParams(alpha, beta, gamma);
        }

        float getVelocity() const { return m_velocity; }
        float getAcceleration() const { return m_accel; }

        void setAlpha(float a){
            validateParams(a, m_beta, m_gamma);
            m_alpha = a;
        }

        void setBeta(float b){
            validateParams(m_alpha, b, m_gamma);
            m_beta = b;
        }

        void setGamma(float g){
            validateParams(m_alpha, m_beta, g);
            m_gamma = g;
        }

        float getAlpha() const { return m_alpha; }
        float getBeta() const { return m_beta; }
        float getGamma() const { return m_gamma; }

        /**
         * @brief Factory: Benedict-Bordner optimal gains for white measurement noise.
         *
         *   beta = alpha(2 - alpha) / 2
         *   gamma = beta² / (2alpha)
         *
         * @param alpha  Position gain ∈ (0, 1)
         */
        static AlphaBetaGammaFilter whitenoise(float alpha) {
            const float beta  = alpha * (2.f - alpha) / 2.f;
            const float gamma = (beta * beta) / (2.f * alpha);
            return AlphaBetaGammaFilter(alpha, beta, gamma);
        }

    protected:

        float applyImpl(float measure, float dt) override {
            const float dt2 = dt * dt;

            // Predict
            const float x_pred = m_position + dt * m_velocity + 0.5f * dt2 * m_accel;
            const float y_pred = m_velocity + dt * m_accel;
            const float a_pred = m_accel;

            // Residual
            const float r = measure - x_pred;

            // Correct
            m_position = x_pred + m_alpha * r;
            m_velocity = y_pred + (m_beta / dt) * r;
            m_accel = a_pred + (m_gamma / dt2) * r;

            return m_position;
        }

        void seedState(float v) override {
            m_position = v;
            m_velocity = m_accel = 0.f;
        }
        void resetState() override { m_position = m_velocity = m_accel = 0.f; }
};

#endif