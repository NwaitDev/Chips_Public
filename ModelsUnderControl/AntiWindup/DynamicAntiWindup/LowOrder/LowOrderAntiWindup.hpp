#ifndef LOW_ORDER_ANTI_WINDUP_HPP
#define LOW_ORDER_ANTI_WINDUP_HPP

#include "../DynamicAntiWindup.hpp"
#include <stdexcept>
#include <cmath>

/**
 * @brief Low-Order Anti-Windup (LOAW) - fixed-order compensator (0 or 1),
 *        independent of the controller order.
 *
 * The compensator order is a compile-time / construction-time parameter:
 *
 *   Order 0 (static):
 *     y_c = Dc * e_aw
 *     Equivalent to back-calculation with gain Dc.  Zero states, zero overhead.
 *     Use when minimal complexity is required and the plant is well-damped.
 *
 *   Order 1 (first-order IIR):
 *     dx_c/dt = Ac * x_c + Bc * e_aw
 *     y_c = Cc * x_c + Dc * e_aw
 *     Adds one state.  Pole Ac chosen by the designer, not tied to the controller.
 *     Use when a static gain is not smooth enough.
 *
 * @param order 0 = static (no state), 1 = first-order dynamic
 * @param Ac Compensator pole [rad/s] (used only for order=1, must be < 0)
 * @param Bc Input gain
 * @param Cc Output (state) gain
 * @param Dc Direct (static) gain
 */
class LowOrderAntiWindup : public DynamicAntiWindup {
public:
    enum class Order { STATIC = 0, FIRST_ORDER = 1 };

    LowOrderAntiWindup(Order order,
                       float Ac, float Bc, float Cc, float Dc)
        : m_order(order), m_Ac(Ac), m_Bc(Bc), m_Cc(Cc), m_Dc(Dc), m_xc(0.f) {
        if (order == Order::FIRST_ORDER && Ac >= 0.f)
            throw std::invalid_argument(
                "LowOrderAntiWindup: Ac must be < 0 for order=FIRST_ORDER");
    }

    /**
     * @brief Order-0 (static gain) factory.
     *
     * Equivalent to back-calculation with a static gain.
     * Correction: y_c = gain * e_aw
     *
     * @param gain  Static anti-windup gain (positive, typical range 0.1…5)
     */
    static LowOrderAntiWindup staticGain(float gain) {
        return LowOrderAntiWindup(Order::STATIC, 0.f, 0.f, 0.f, gain);
    }

    /**
     * @brief Order-1 factory using tracking-time-constant idiom.
     *
     * Pole at -1/Tt, DC gain = 1.
     * @param Tt  Time constant [s] > 0
     */
    static LowOrderAntiWindup firstOrder(float Tt) {
        if (Tt <= 0.f)
            throw std::invalid_argument("LowOrderAntiWindup::firstOrder: Tt > 0");
        const float Ac = -1.f / Tt;
        const float Cc = std::fabs(Ac);
        return LowOrderAntiWindup(Order::FIRST_ORDER, Ac, 1.f, Cc, 0.f);
    }

    /**
     * @brief Order-1 factory with explicit pole and gains.
     *
     * @param Ac Compensator pole [rad/s] < 0
     * @param Bc Input gain
     * @param Cc State gain
     * @param Dc Static gain
     */
    static LowOrderAntiWindup firstOrderFull(float Ac, float Bc,
                                             float Cc, float Dc) {
        return LowOrderAntiWindup(Order::FIRST_ORDER, Ac, Bc, Cc, Dc);
    }

    Order getOrder() const { return m_order; }
    float getAc() const { return m_Ac; }
    float getBc() const { return m_Bc; }
    float getCc() const { return m_Cc; }
    float getDc() const { return m_Dc; }
    float getState() const { return m_xc; }

    void setDc(float v) { m_Dc = v; }
    void setCc(float v) { m_Cc = v; }
    void setBc(float v) { m_Bc = v; }
    void setAc(float v) {
        if (m_order == Order::FIRST_ORDER && v >= 0.f)
            throw std::invalid_argument("LowOrderAntiWindup: Ac < 0");
        m_Ac = v;
    }

protected:
    float compensatorStep(float e_aw, float dt) override {
        if (m_order == Order::STATIC) {
            return m_Dc * e_aw;                     // pure static gain, no state
        }
        // First-order: Forward Euler
        m_xc += dt * (m_Ac * m_xc + m_Bc * e_aw);
        return m_Cc * m_xc + m_Dc * e_aw;
    }

    void resetCompensator() override { m_xc = 0.f; }

private:
    Order m_order;
    float m_Ac, m_Bc, m_Cc, m_Dc;
    float m_xc;
};

#endif