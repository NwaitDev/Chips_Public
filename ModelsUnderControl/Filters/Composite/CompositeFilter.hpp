#ifndef COMPOSITE_FILTER_HPP
#define COMPOSITE_FILTER_HPP

#include "../IFilter.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

/**
 * @brief Composite filter - applies a sequence of filters left-to-right.
 *
 * @code
 *   auto chain = std::make_shared<CompositeFilter>();
 *   chain->add(std::make_shared<MedianFilter>(5));
 *   chain->add(std::make_shared<AlphaBetaFilter>(0.85f, 0.005f));
 *   chain->add(std::make_shared<ClampFilter>(-1.f, 1.f));
 * @endcode
 */
class CompositeFilter : public IFilter{
    private:
        std::vector<std::shared_ptr<IFilter>> m_filters;

    public:
        void add(std::shared_ptr<IFilter> f){
            if(!f) throw std::invalid_argument("CompositeFilter: cannot add null filter");
            m_filters.push_back(std::move(f));
        }

        float apply(float value, float dt) override {
            for(auto& f : m_filters){
                value = f->apply(value, dt);
            }
            return value;
        }

        void reset() override {
            for(auto& f : m_filters){
                f->reset();
            }
        }
        
        std::size_t size() const { return m_filters.size(); }
};

#endif