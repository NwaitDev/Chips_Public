#ifndef STATELESS_FILTER_HPP
#define STATELESS_FILTER_HPP
#include "../IFilter.hpp"

/**
 * @brief Base for filters that carry no mutable state between calls.
 *
 * reset() is a no-op: there is nothing to clear.
 * Derived classes only need to implement apply().
 */
class StatelessFilter : public IFilter {
public:
    void reset() override {}   // nothing to reset
};

#endif