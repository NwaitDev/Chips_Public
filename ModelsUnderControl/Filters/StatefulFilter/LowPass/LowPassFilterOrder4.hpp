#ifndef LOW_PASS_FILTER_4_HPP
#define LOW_PASS_FILTER_4_HPP

#include "../StatefulFilter.hpp"
#include <stdexcept>

/**
 * @brief First-order low-pass filter discretised with Runge-Kutta 4.
 *
 * --- ODE ---
 * The continuous first-order low-pass filter satisfies:
 *
 *   tau * dy/dt = x(t) - y(t)
 *   ->  dy/dt = f(y, x) = (x - y) / tau
 *
 * --- RK4 scheme ---
 * Classic 4th-order Runge-Kutta applied to the ODE above:
 *
 *   k1 = f(y[n],           x[n])
 *   k2 = f(y[n] + dt/2*k1, x_mid)     x_mid ≈ x[n]  (ZOH assumption)
 *   k3 = f(y[n] + dt/2*k2, x_mid)
 *   k4 = f(y[n] + dt*k3,   x[n])
 *
 *   y[n+1] = y[n] + dt/6 * (k1 + 2*k2 + 2*k3 + k4)
 *
 * Under zero-order hold (x constant over [t, t+dt]):
 *   x_mid = x[n], so k2 = k3 and the formula reduces to:
 *
 *   k1 =  (x - y[n])          / tau
 *   k2 =  (x - (y[n]+dt/2*k1))/ tau
 *   k3 =  (x - (y[n]+dt/2*k2))/ tau
 *   k4 =  (x - (y[n]+dt*k3))  / tau
 *
 *   y[n+1] = y[n] + dt/6 * (k1 + 2k2 + 2k3 + k4)
 *
 * --- Closed form (ZOH) ---
 * For a linear ODE with constant input the RK4 update simplifies to:
 *
 *   e = dt / tau
 *   c = 1 + e/2 + e²/12 + e³/24    (polynomial in e)
 *   y[n+1] = y[n]*(1 − e*c/tau*dt)  + x*e*c/tau*dt
 *
 * We compute this directly to avoid four separate divisions by tau.
 *
 *
 * --- When to prefer RK4 ---
 * - When dt is large relative to tau (dt/tau > 0.1)
 * - When phase accuracy matters (e.g. derivative filtering in a PID)
 * - When you want to verify your Euler filter's accuracy
 *
 * --- When Euler is fine ---
 * - When dt/tau < 0.05 (Euler error is already negligible)
 * - When tau >> dt  (most embedded control loops)
 *
 * @param tau  Time constant [s].  Larger tau => stronger smoothing.
 */
class LowPassFilterOrder4 : public StatefulFilter {
public:
    explicit LowPassFilterOrder4(float tau)
        : m_tau(tau), m_y(0.f)
    {
        if (tau <= 0.f)
            throw std::invalid_argument("LowPassFilterRK4: tau must be > 0");
    }

    void  setTau(float tau) {
        if (tau <= 0.f)
            throw std::invalid_argument("LowPassFilterRK4: tau must be > 0");
        m_tau = tau;
    }
    float getTau()    const { return m_tau; }
    float getState()  const { return m_y;   }

protected:
    // --- RK4 step ---
    float applyImpl(float x, float dt) override {
        // dy/dt = f(y) = (x - y) / tau
        // Under ZOH: x is constant over [t, t+dt]
        const float k1 = (x - m_y)               / m_tau;
        const float k2 = (x - (m_y + dt*0.5f*k1))/ m_tau;
        const float k3 = (x - (m_y + dt*0.5f*k2))/ m_tau;
        const float k4 = (x - (m_y + dt*k3))      / m_tau;

        m_y += (dt / 6.f) * (k1 + 2.f*k2 + 2.f*k3 + k4);
        return m_y;
    }

    // --- State management (StatefulFilter contract) ---
    void seedState(float v)  override { m_y = v; }
    void resetState()        override { m_y = 0.f; }

private:
    float m_tau;
    float m_y;      // Current filter state y[n]
};

#endif