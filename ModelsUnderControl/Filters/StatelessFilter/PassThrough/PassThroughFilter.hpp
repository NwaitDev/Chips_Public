#ifndef PASS_THROUGH_FILTER_HPP
#define PASS_THROUGH_FILTER_HPP

#include "../StatelessFilter.hpp"

/**
 * @brief Identity filter - passes the value through unchanged
 * 
 * Use as the default when no filtering is desired
 */
class PassThroughFilter : public StatelessFilter {
    public:
        float apply(float value, float /*dt*/) override { return value; }
};

#endif