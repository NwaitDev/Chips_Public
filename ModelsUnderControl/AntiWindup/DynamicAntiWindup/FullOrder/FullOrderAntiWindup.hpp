#ifndef FULL_ORDER_ANTI_WINDUP_HPP
#define FULL_ORDER_ANTI_WINDUP_HPP

#include "../DynamicAntiWindup.hpp"
#include <cmath>
#include <array>
#include <stdexcept>

/**
 * @file AntiWindupDynamic.hpp
 * @brief Dynamic anti-windup compensators: Full-Order, Reduced-Order, Low-Order.
 *
 * All three inherit DynamicAntiWindup and implement compensatorStep().
 * The common pipeline (in DynamicAntiWindup::correct()) is:
 *
 *   e_aw     = satOutput − rawOutput          (saturation error, 0 when not saturated)
 *   y_c      = compensatorStep(e_aw, dt)      (run the internal compensator)
 *   integral += y_c * dt                      (inject correction into integrator)
 *
 * ─────────────────────────────────────────────────────────────────────────────
 * OFFLINE DESIGN WORKFLOW
 * ─────────────────────────────────────────────────────────────────────────────
 * All three compensators are parametrised by (Ac, Bc, Cc, Dc) — the state-space
 * matrices of the compensator W(s) = Cc*(sI-Ac)^{-1}*Bc + Dc.
 * For SISO PI/PID controllers these are all scalars.
 *
 * The design steps are:
 *   1. Identify the controller as a state-space system (Ak, Bk, Ck, Dk).
 *      For a PI:  Ak=0,  Bk=Ki,  Ck=1,  Dk=Kp
 *      For a PID: Ak=-N, Bk=Kd*N, Ck=1, Dk=Kp+Kd*N  (filtered derivative)
 *
 *   2. Choose the compensator order:
 *      Full-Order  → Ac = Ak  (copy controller pole)
 *      Reduced-Order → Ac chosen to approximate Ak with fewer states
 *      Low-Order   → Ac = fixed pole (e.g. -1/tau), order independent of controller
 *
 *   3. Solve for Bc, Cc, Dc using the "stable co-projection" equations
 *      (Turner, Postlethwaite, Walker 2000) or simply set:
 *        Bc = 1,  Cc = Ec (design gain),  Dc = 0   (simplified SISO version)
 *
 * Python snippet (scipy) to compute state-space for a PI controller:
 * @code
 *   import scipy.signal as sig
 *   Kp, Ki = 2.0, 0.5
 *   # PI in state-space: integral is the state
 *   Ak, Bk, Ck, Dk = 0.0, Ki, 1.0, Kp
 *   # Full-order compensator: mirror controller pole
 *   Ac_fo = Ak   # = 0 for PI → integrator
 *   Bc_fo = 1.0
 *   Cc_fo = 0.5  # design gain Ec
 *   Dc_fo = 0.0
 * @endcode
 *
 * ─────────────────────────────────────────────────────────────────────────────
 */

/**
 * @brief Full-Order Anti-Windup (FOAW) - compensator order equals controller order.
 *
 * For a SISO PI controller (order 1) the compensator is:
 *   dx_c/dt = Ac * x_c + Bc * e_aw (Ac mirrors the controller's integrator pole)
 *   y_c = Cc * x_c + Dc * e_aw
 *
 * The controller's own pole is Ak = 0 (a pure integrator for a PI).
 * Setting Ac = Ak reconstructs the controller state exactly under saturation,
 * which is the theoretical optimum for linear plants.
 *
 * Design parameters (offline, see workflow above):
 *   Ac : controller pole (Ak) - for PI: 0,  for PID filtered: -N
 *   Bc : input gain - typically 1
 *   Cc : output (correction) gain - design freedom, tune for recovery speed
 *   Dc : direct feed-through - typically 0
 *
 * Discretisation: Forward Euler  x_c[k+1] = x_c[k] + dt*(Ac*x_c[k] + Bc*e_aw)
 *
 * @param Ac Compensator pole [rad/s] - set equal to the controller pole
 * @param Bc Input gain - scales e_aw entering the compensator
 * @param Cc Output gain - scales the state leaving the compensator
 * @param Dc Direct term - static feed-through (usually 0)
 */
class FullOrderAntiWindup : public DynamicAntiWindup {

private:
    float m_Ac;   // Compensator pole  (mirrors controller pole for full-order)
    float m_Bc;   // Input gain
    float m_Cc;   // Output gain
    float m_Dc;   // Direct feed-through
    float m_xc;   // Compensator state

public:
    FullOrderAntiWindup(float Ac, float Bc, float Cc, float Dc = 0.f)
        : m_Ac(Ac), m_Bc(Bc), m_Cc(Cc), m_Dc(Dc), m_xc(0.f)
    {}

    /**
     * @brief Factory for a PI controller (controller pole Ak = 0).
     *
     * @param Cc Output gain (tune for desired recovery speed, typ. 0.1…2)
     * @param Dc Direct term (typically 0)
     */
    static FullOrderAntiWindup forPI(float Cc, float Dc = 0.f) {
        return FullOrderAntiWindup(0.f, 1.f, Cc, Dc);
    }

    /**
     * @brief Factory for a PID with filtered derivative (controller pole Ak = -N).
     *
     * @param N Derivative filter coefficient (same as the PID's N)
     * @param Cc Output gain
     * @param Dc Direct term
     */
    static FullOrderAntiWindup forPID(float N, float Cc, float Dc = 0.f) {
        return FullOrderAntiWindup(-N, 1.f, Cc, Dc);
    }

    void setAc(float v) { m_Ac = v; }
    void setBc(float v) { m_Bc = v; }
    void setCc(float v) { m_Cc = v; }
    void setDc(float v) { m_Dc = v; }
    float getAc() const { return m_Ac; }
    float getBc() const { return m_Bc; }
    float getCc() const { return m_Cc; }
    float getDc() const { return m_Dc; }
    float getState() const { return m_xc; }

protected:
    float compensatorStep(float e_aw, float dt) override {
        // Forward Euler: x_c[k+1] = x_c[k] + dt*(Ac*x_c[k] + Bc*e_aw)
        m_xc += dt * (m_Ac * m_xc + m_Bc * e_aw);
        return m_Cc * m_xc + m_Dc * e_aw;         // y_c = Cc*x_c + Dc*e_aw
    }

    void resetCompensator() override { m_xc = 0.f; }
};

#endif