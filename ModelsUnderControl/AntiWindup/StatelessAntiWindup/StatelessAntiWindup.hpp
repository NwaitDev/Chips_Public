#ifndef STATELESS_ANTI_WINDUP_HPP
#define STATELESS_ANTI_WINDUP_HPP

#include "../IAntiWindup.hpp"

/**
 * @brief Base for anti-windup strategies that carry no mutable state.
 *
 * reset() does nothing — there is nothing to clear.
 * Derived classes only need to implement correct().
 */
class StatelessAntiWindup : public IAntiWindup {
public:
    void reset() final {}     // no-op, cannot be overridden further
};

#endif