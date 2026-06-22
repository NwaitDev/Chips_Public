/**
 * https://www.geeksforgeeks.org/python/noise-removal-using-lowpass-digital-butterworth-filter-in-scipy-python/
 * Utilisation données mais il y a fallu modifier les valeurs car sinon trop proches pour analyser avec FFT et PSD
 */

#include "../controllers/PIDController/PIDController.hpp"
#include "../../Filters/StatefulFilter/LowPass/LowPassFilter.hpp"
#include "../../Filters/StatefulFilter/LowPass/LowPassFilterOrder2.hpp"
#include "../../Filters/StatefulFilter/LowPass/LowPassFilterOrder4.hpp"
#include "common/FilterLogger.hpp"

#include <cmath>
#include <vector>
#include <memory>

constexpr float low_signal = 10.0f;
constexpr float noise_signal = 200.0f;

int main(){

    const float fs = 1000.0f; // Fréquence d'échantillonnage 
    const float dt = 1.0f / fs; // Pas de temps entre chaque mesure 
    const float duration = 1.0f; // DUrée de 1s
    const int num_samples = static_cast<int>(fs * duration);

    const float fc = 50.0f;
    const float tau = 1.0 / (2.0 * M_PI * fc);

    LowPassFilter filter(tau);
    LowPassFilterOrder2 filter2(tau);
    LowPassFilterOrder4 filter4(tau);

    FilterLogger logger("tests/results/low_pass.csv");
    FilterLogger logger2("tests/results/low_pass_2.csv");
    FilterLogger logger4("tests/results/low_pass_4.csv");

    std::vector<float> time_vector(num_samples);
    std::vector<float> noisy_signal(num_samples);
    std::vector<float> filtered_signal(num_samples);

    for(int i = 0; i < num_samples; i++){
        float t = i * dt;
        time_vector[i] = t;

        float signal_pure = std::sin(2.0f * M_PI * low_signal * t);
        float noise = std::sin(2.0f * M_PI * noise_signal * t);
        noisy_signal[i] = signal_pure + noise;

        filtered_signal[i] = filter.apply(noisy_signal[i], dt);
        float filtered_2 = filter2.apply(noisy_signal[i], dt);
        float filtered_4 = filter4.apply(noisy_signal[i], dt);

        logger.log(t, noisy_signal[i], filtered_signal[i]);
        logger2.log(t, noisy_signal[i], filtered_2);
        logger4.log(t, noisy_signal[i], filtered_4);
    }

}