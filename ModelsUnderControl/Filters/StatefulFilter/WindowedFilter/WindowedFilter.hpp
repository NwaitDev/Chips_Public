#ifndef WINDOWED_FILTER_HPP
#define WINDOWED_FILTER_HPP

#include "../StatefulFilter.hpp"
#include <cstddef>
#include <vector>
#include <stdexcept>

/**
 * @brief Base class for stateful filters that operate on a sliding window.
 *
 * The base manages the circular buffer and seeds it with the first sample.
 * Derived classes only need to define how the current window should be
 * reduced to a single output value.
 */
class WindowedFilter : public StatefulFilter {
public:
    explicit WindowedFilter(std::size_t windowSize)
        : m_windowSize(windowSize), m_buffer(windowSize, 0.f) {
        if (windowSize == 0) {
            throw std::invalid_argument("WindowedFilter: windowSize must be > 0");
        }
    }

    std::size_t getWindowSize() const { return m_windowSize; }
    std::size_t getSampleCount() const { return m_count; }

protected:
    float applyImpl(float value, float dt) override {
        pushSample(value);
        return reduceWindow(dt);
    }

    void seedState(float firstValue) override {
        resetState();
        pushSample(firstValue);
    }

    void resetState() override {
        std::fill(m_buffer.begin(), m_buffer.end(), 0.f);
        m_head = 0;
        m_count = 0;
    }

    void pushSample(float value) {
        m_buffer[m_head] = value;
        m_head = (m_head + 1) % m_windowSize;
        if (m_count < m_windowSize) {
            ++m_count;
        }
    }

    std::vector<float> snapshotWindow() const {
        if (m_count < m_windowSize) {
            return std::vector<float>(m_buffer.begin(), m_buffer.begin() + m_count);
        }

        return m_buffer;
    }

    virtual float reduceWindow(float dt) = 0;

    std::size_t m_windowSize;
    std::vector<float> m_buffer;
    std::size_t m_head = 0;
    std::size_t m_count = 0;
};

#endif