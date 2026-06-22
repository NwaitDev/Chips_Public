#include "../controllers/PIDController/PIDController.hpp"
#include "../../Filters/StatefulFilter/AlphaBeta/AlphaBetaFilter.hpp"
#include "common/CsvLogger.hpp"

/**
 * Vraiment pas sûr du tests qu'il soit bien
 */

struct Plant{
    float tau = 3.0f, y = 0.0f;
    float step(float u, float dt){
        y += (dt / tau) * (u - y);
        return y;
    }
};

struct Noise {
    int seed = 42;
    float next(float amp = 0.1f) {
        seed = seed * 1664525 + 1013904223;
        return ((seed & 0x7fff) / (float)0x7fff - 0.5f) * 2.f * amp;
    }
};

int main(){

    Plant p; Noise n;

    const float dt = 0.05f, sp = 0.8f;

    const float kp = 2.0f;
    const float ki = 0.5f;
    const float kd = 0.0f;

    auto ab = std::make_shared<AlphaBetaFilter>(AlphaBetaFilter::criticallyDamped(0.8f));

    PIDController controller(kp, ki, kd);
    PIDController controller_without_filter(kp, ki, kd);

    controller.setInputFilter(ab);

    CsvLogger logger("tests/results/alphabeta.csv");
    CsvLogger logger_without_filter("tests/results/without_alphabeta.csv");

    for(int i = 0; i < 200; i++){
        float noisy = p.y + n.next(0.12f);
        controller.setTargetValue(sp);
        controller.setCurrentValue(noisy);
        float u = controller.compute(dt);
        p.step(u, dt);
        logger.log(i*dt, sp, noisy, controller.getProportional(), controller.getIntegral(), controller.getDerivative(), u);
    }

    for(int i = 0; i < 200; i++){
        float noisy = p.y + n.next(0.12f);
        controller_without_filter.setTargetValue(sp);
        controller_without_filter.setCurrentValue(noisy);
        float u = controller_without_filter.compute(dt);
        p.step(u, dt);
        logger_without_filter.log(i*dt, sp, noisy, controller_without_filter.getProportional(), controller_without_filter.getIntegral(), controller_without_filter.getDerivative(), u);
    }

}