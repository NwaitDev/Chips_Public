#ifndef MEDIAN_FILTER_HPP
#define MEDIAN_FILTER_HPP

#include "../StatefulFilter/WindowedFilter/WindowedFilter.hpp"
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <algorithm>

/**
 * @brief Sliding-window median filter - removes impulsive noise / spikes.
 *
 * Keeps a circular buffer of the last `windowSize` samples and returns the
 * median of the window at each step.  Unlike the IIR filters above, the
 * median filter introduces no lag on step changes, but does add a delay of
 * ⌊windowSize/2⌋ samples on ramp inputs.
 *
 * Typical use case: place before an AlphaBetaFilter to strip outliers first,
 * then let the tracker smooth what remains.
 *
 * @code
 *   auto chain = std::make_shared<CompositeFilter>();
 *   chain->add(std::make_shared<MedianFilter>(5));              // spike removal
 *   chain->add(AlphaBetaFilter::criticallyDamped(0.85f));       // smoothing
 * @endcode
 *
 * @param windowSize  Number of samples in the window.  Must be >+ 3.
 */
class MedianFilter : public WindowedFilter {
    public:
        explicit MedianFilter(std::size_t windowSize = 5)
            : WindowedFilter(windowSize){
            if(windowSize < 3){
                throw std::invalid_argument("MedianFilter: windowSize must be >= 3");
            }
        }

    protected:
        float reduceWindow(float /*dt*/) override{
            std::vector<float> sorted = snapshotWindow();
            std::sort(sorted.begin(), sorted.end());

            if(sorted.empty()){
                return 0.f;
            }

            const std::size_t middle = sorted.size() / 2;
            if(sorted.size() % 2 == 0){
                return 0.5f * (sorted[middle - 1] + sorted[middle]);
            }

            return sorted[middle];
        }
};

#endif