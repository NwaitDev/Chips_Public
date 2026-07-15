#ifndef MOVING_AVERAGE_FILTER_HPP
#define MOVING_AVERAGE_FILTER_HPP

#include "WindowedFilter.hpp"
#include <stdexcept>

/**
 * @brief Sliding-window moving average filter.
 *
 * Useful to smooth noisy measurements while keeping the implementation
 * simpler than a low-pass IIR filter.
 */
class MovingAverageFilter : public WindowedFilter {
public:
    explicit MovingAverageFilter(std::size_t windowSize = 5)
        : WindowedFilter(windowSize) {
        if (windowSize == 0) {
            throw std::invalid_argument("MovingAverageFilter: windowSize must be > 0");
        }
    }

protected:
    float reduceWindow(float /*dt*/) override {
        const auto samples = snapshotWindow();
        float sum = 0.f;
        for (float sample : samples) {
            sum += sample;
        }
        return samples.empty() ? 0.f : sum / static_cast<float>(samples.size());
    }
};

#endif