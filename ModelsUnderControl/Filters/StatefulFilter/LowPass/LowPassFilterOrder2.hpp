#ifndef LOW_PASS_FILTER_2_HPP
#define LOW_PASS_FILTER_2_HPP

#include "../StatefulFilter.hpp"
#include <stdexcept>

/**
 * @brief First-order low-pass filter discretised with BDF2
 *        (Backward Differentiation Formula, order 2).
 *
 *  --- ODE ---
 *   tau * dy/dt = x(t) − y(t)
 *   ⟹  dy/dt = (x − y) / tau
 *
 * --- BDF2 scheme ----
 * BDF2 approximates the derivative using the last TWO output values:
 *
 *   (3*y[n+1] − 4*y[n] + y[n-1]) / (2*dt) = f(t[n+1], y[n+1])
 *
 * Substituting f = (x[n+1] − y[n+1]) / tau  and solving for y[n+1]:
 *
 *   (3*y[n+1] − 4*y[n] + y[n-1]) / 2 * dt = (x[n+1] − y[n+1]) * tau
 *
 *   y[n+1] * (3/(2dt) + 1/tau) = 4*y[n]/(2dt) − y[n-1]/(2dt) + x[n+1]/tau
 *
 *   Let  alpha = 2*dt / (3*tau + 2*dt)
 *
 *   y[n+1] = alpha * x[n+1]
 *           + (1−alpha) * (4/3*y[n] − 1/3*y[n-1])
 *
 * --- Derivation step by step ---
 *   Multiply both sides by 2dt:
 *     3*y[n+1] − 4*y[n] + y[n-1] = (2dt/tau)*(x[n+1] − y[n+1])
 *
 *   Collect y[n+1]:
 *     y[n+1]*(3 + 2dt/tau) = 4*y[n] − y[n-1] + (2dt/tau)*x[n+1]
 *
 *   Define beta = 2dt/tau:
 *     y[n+1] = (4*y[n] − y[n-1] + beta*x[n+1]) / (3 + beta)
 *
 *   Which is identical to the alpha form above with alpha = beta/(3+beta) = 2dt/(3tau+2dt).
 *
 * --- Bootstrapping ---
 * BDF2 is a 2-step method: it needs y[n] AND y[n-1].
 * On the very first step (n=0 -> computing y[1]) only y[0] is available.
 * We bootstrap with ONE Euler step:
 *
 *   y[1] = y[0] + dt * (x[1] − y[0]) / tau         (Euler, 1st-order)
 *
 * From step 2 onward, BDF2 takes over and delivers 2nd-order accuracy.
 *
 *
 * --- When BDF2 is overkill ---
 * When dt << tau (typical embedded loop at high sample rate), Euler is
 * already extremely accurate and BDF2's extra complexity is unnecessary.
 * BDF2 shines when dt ≈ tau or dt > tau (rare but possible for slow tau values
 * like thermal or altitude filters).
 *
 * @param tau  Time constant [s].  Larger tau => stronger smoothing.
 */
class LowPassFilterOrder2 : public StatefulFilter {
public:
    explicit LowPassFilterOrder2(float tau)
        : m_tau(tau), m_y(0.f), m_yPrev(0.f), m_bootstrapped(false)
    {
        if (tau <= 0.f)
            throw std::invalid_argument("LowPassFilterBDF2: tau must be > 0");
    }

    void  setTau(float tau) {
        if (tau <= 0.f)
            throw std::invalid_argument("LowPassFilterBDF2: tau must be > 0");
        m_tau = tau;
    }
    float getTau()            const { return m_tau;        }
    float getState()          const { return m_y;          }
    float getPreviousState()  const { return m_yPrev;      }
    bool  isBootstrapped()    const { return m_bootstrapped; }

protected:
    // BDF2 step 
    float applyImpl(float x, float dt) override {
        float yNew;

        if (!m_bootstrapped) {
            // Bootstrap: one Euler step to get y[1] from y[0] 
            // Euler:  y[1] = y[0] + dt * (x - y[0]) / tau
            const float alpha = m_tau / (m_tau + dt);   // Euler coeff
            yNew           = alpha * m_y + (1.f - alpha) * x;
            m_yPrev        = m_y;       // save y[0] as y[n-1]
            m_bootstrapped = true;
        } else {
            // BDF2: y[n+1] = (4*y[n] - y[n-1] + beta*x[n+1]) / (3 + beta) 
            // beta = 2*dt / tau
            const float beta = 2.f * dt / m_tau;
            yNew       = (4.f * m_y - m_yPrev + beta * x) / (3.f + beta);
            m_yPrev    = m_y;           // shift: y[n-1] <- y[n]
        }

        m_y = yNew;
        return m_y;
    }

    // ── State management (StatefulFilter contract)
    void seedState(float v) override {
        m_y           = v;
        m_yPrev       = v;      // assume steady state: y[n-1] = y[n] = v
        m_bootstrapped = false;  // reset bootstrap flag — next step = Euler
    }

    void resetState() override {
        m_y           = 0.f;
        m_yPrev       = 0.f;
        m_bootstrapped = false;
    }

private:
    float m_tau;
    float m_y;           // Current state   y[n]
    float m_yPrev;       // Previous state  y[n-1]
    bool  m_bootstrapped; // true once the Euler boot step is done
};

#endif