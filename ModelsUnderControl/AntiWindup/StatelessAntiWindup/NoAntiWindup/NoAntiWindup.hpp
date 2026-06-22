#ifndef NO_ANTI_WINDUP_HPP
#define NO_ANTI_WINDUP_HPP

#include "../StatelessAntiWindup.hpp"

/**
 * @brief No-op - integral passes through unchanged.  Safe default.
 */
class NoAntiWindup : public StatelessAntiWindup {
public:
    float correct(float, float, float integral, float, float) override {
        return integral;
    }
};

#endif