#ifndef REDUCED_ORDER_ANTI_WINDUP_HPP
#define REDUCED_ORDER_ANTI_WINDUP_HPP

#include "../DynamicAntiWindup.hpp"
#include <stdexcept>
#include <cmath>

/**
 * @brief Reduced-Order Anti-Windup (ROAW) - compensator order < controller order.
 *
 * For a PID (order 2: one integrator + one filtered derivative), a
 * reduced-order compensator of order 1 is often sufficient.  The
 * second (derivative) state is approximated by a static gain, reducing
 * implementation cost at the price of slightly sub-optimal performance.
 *
 * The compensator is identical in structure to FOAW but its pole Ac is
 * chosen independently of (and typically slower than) the controller's
 * fastest pole:
 *
 *   dx_c/dt = Ac * x_c + Bc * e_aw     (single state, order 1)
 *   y_c = Cc * x_c + Dc * e_aw
 *
 * The "reduced" aspect is that:
 *   - A PID has 2 internal states; this compensator has 1.
 *   - Ac is not constrained to equal any controller pole - it is a free
 *     design parameter chosen for the desired bandwidth of the correction.
 *
 * Design rule of thumb:
 *   Ac = -(1 / Tt)    where Tt is the desired recovery time constant
 *                      (same role as in back-calculation, but embedded in
 *                       a dynamic compensator rather than a static gain)
 *   Bc = 1
 *   Cc = |Ac|          (normalised so the DC gain Cc/|Ac| ≈ 1)
 *   Dc = 0
 *
 * @param Ac Compensator pole [rad/s] - must be < 0 for stability
 * @param Bc Input gain
 * @param Cc Output gain
 * @param Dc Direct term (typically 0)
 */
class ReducedOrderAntiWindup : public DynamicAntiWindup {
private:
    float m_Ac, m_Bc, m_Cc, m_Dc;
    float m_xc;

public:
    ReducedOrderAntiWindup(float Ac, float Bc, float Cc, float Dc = 0.f)
        : m_Ac(Ac), m_Bc(Bc), m_Cc(Cc), m_Dc(Dc), m_xc(0.f){
        if (Ac >= 0.f)
            throw std::invalid_argument(
                "ReducedOrderAntiWindup: Ac must be < 0 for a stable compensator");
    }

    /**
     * @brief Convenience factory using the tracking-time-constant idiom.
     *
     * Places the compensator pole at -1/Tt and normalises gains so the
     * DC gain is 1 (same steady-state behaviour as back-calculation).
     *
     * @param Tt  Recovery time constant [s] > 0  (same meaning as in BackCalculation)
     */
    static ReducedOrderAntiWindup fromTt(float Tt) {
        if (Tt <= 0.f)
            throw std::invalid_argument("ReducedOrderAntiWindup::fromTt: Tt > 0");
        const float Ac = -1.f / Tt;
        const float Cc = std::fabs(Ac);   // DC gain: Cc / |Ac| = 1
        return ReducedOrderAntiWindup(Ac, 1.f, Cc, 0.f);
    }

    void  setAc(float v) {
        if (v >= 0.f)
            throw std::invalid_argument("ReducedOrderAntiWindup: Ac < 0");
        m_Ac = v;
    }
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
        m_xc += dt * (m_Ac * m_xc + m_Bc * e_aw);
        return m_Cc * m_xc + m_Dc * e_aw;
    }

    void resetCompensator() override { m_xc = 0.f; }
};

#endif