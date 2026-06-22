#include "../../Filters/StatefulFilter/HighPass/HighPassFilter.hpp"
#include "common/FilterLogger.hpp"

#include <cmath>
#include <vector>

constexpr float noise_signal = 10.0f;
constexpr float high_signal = 100.0f;

int main(){

    const float fs = 1000.0f;
    const float dt = 1.0f / fs;
    const float duration = 1.0f;
    const int num_samples = static_cast<int>(fs * duration);

    const float fc = 80.0f;
    const float tau = 1.0 / (2.0 * M_PI * fc);

    HighPassFilter filter(tau);
    FilterLogger logger("tests/results/high_pass.csv");

    for(int i = 0; i < num_samples; i++){
        float t = i * dt;

        float signal_pure = std::sin(2.0 * M_PI * high_signal * t);
        float noise = std::sin(2.0f * M_PI * noise_signal * t);
        float noisy_signal = signal_pure + noise;

        float filtered = filter.apply(noisy_signal, dt);
        logger.log(t, noisy_signal, filtered);
    }

}