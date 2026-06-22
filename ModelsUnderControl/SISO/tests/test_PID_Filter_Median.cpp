#include "../controllers/PIDController/PIDController.hpp"
#include "../../Filters/Median/MedianFilter.hpp"
#include "common/CsvLogger.hpp"
#include "common/FilterLogger.hpp"

#include <memory>
#include <cmath>

int main(){

    FilterLogger logger("tests/results/median.csv");
    FilterLogger logger_without_filter("tests/results/without_median.csv");
    
    auto medianFilter = std::make_shared<MedianFilter>(15);

    const float dt = 0.05f;

    for(int i = 0; i < 200; i++){
        bool spike = (i % 40 == 0 && i != 0);
        float t = i * dt;
        float raw = std::sin(2.0f * M_PI * 0.2f * t) + (spike ? 2.0f : 0.0f);

        auto value = medianFilter->apply(raw, dt);

        logger.log(t, raw, value);
    }

}