#ifndef CLAMP_FILTER_HPP
#define CLAMP_FILTER_HPP

#include "../StatelessFilter.hpp"
#include <stdexcept>
#include <algorithm>

/**
 * @brief Hard saturation filter
 * 
 * Direct replacement for the existing m_hasLimits / clamp() logic inside
 * PIController, now expressed as a composable filter.
 *  
 * @param min Lower bound
 * @param max Upper bound
 */
class ClampFilter : public StatelessFilter {
    private:
        float m_min;
        float m_max;
        
    public:
        ClampFilter(float min, float max) : m_min(min), m_max(max){
            if(m_min >= m_max){
                throw std::invalid_argument("ClampFilter: min must be < max");
            }
        }

        float apply(float value, float /*dt*/) override {
            return std::clamp(value, m_min, m_max);
        }

        void setLimits(float min, float max){
            if(min >= max){
                throw std::invalid_argument("ClampFilter: min must be < max");
            }

            m_min = min;
            m_max = max;
        }

        float getMin() const { return m_min; }
        float getMax() const { return m_max; }
};


 #endif
