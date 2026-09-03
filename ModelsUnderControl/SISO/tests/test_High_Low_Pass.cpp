#include "../../Filters/StatefulFilter/HighPass/HighPassFilter.hpp"
#include "../../Filters/StatefulFilter/LowPass/LowPassFilter.hpp"
#include "common/FilterLogger.hpp"

#include <cmath>



int main(){

    const float fs = 1000.0f;
    const float dt = 1.0f / fs;
    const float duration = 1.0f;
    const int num_samples = static_cast<int>(fs * duration);

    const float fc_lp = 110.0f;
    const float tau_lp = 1 / (2.0f * M_PI * fc_lp);

    const float fc_hp = 90.0f;
    const float tau_hp = 1 / (2.0f * M_PI * fc_hp);

    HighPassFilter hp(tau_hp);
    LowPassFilter lp(tau_lp);

    FilterLogger logger("tests/results/high_low_pass.csv");

    for(int i = 0; i < num_samples; i++){
        float t = i * dt;

        float signal1 = std::sin(2.0f * M_PI * 5.0f * t);
        float signal2 = std::sin(2.0f * M_PI * 100.0f * t);
        float signal3 = std::sin(2.0f * M_PI * 400.0f * t);
        float s = signal1 + signal2 + signal3;

        float filtered = hp.apply(s, dt);
        filtered = lp.apply(filtered, dt);

        logger.log(t, s, filtered);
    }

}
