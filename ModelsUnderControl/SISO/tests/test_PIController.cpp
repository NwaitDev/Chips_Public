#include <algorithm>
#include "../controllers/PIController/PIController.hpp"
#include "../../Filters/StatelessFilter/Clamp/ClampFilter.hpp"
#include "common/ProcessModel.hpp"
#include "common/CsvLogger.hpp"

int main() {
    const float dt = 0.1f;
    const float simTime = 100.0f;

    std::shared_ptr<ClampFilter> clampFilter = std::make_shared<ClampFilter>(0.0f, 255.0f);

    PIController controller(0.6f, 0.15f);
    controller.setOutputLimits(0.0f, 255.0f);
    controller.setOutputFilter(clampFilter);

    FirstOrderProcess process(0.8f, 1.0f, dt);

    process.setNoiseAmplitude(0.5f); // bruit capteur
    process.setDisturbance(0.0f); // perturbation initiale

    CsvLogger logger("tests/results/pi_controller.csv");

    float target = 0.0f;

    for (float t = 0.0f; t <= simTime; t += dt) {
        if (t > 1.0f)
            target = 100.0f;

        if (t > 40.0f)
            process.setDisturbance(5.0f);

        if (t > 70.0f)
            process.setDisturbance(8.0f);

        float measurement = process.measuredOutput();

        controller.setTargetValue(target);
        controller.setCurrentValue(measurement);

        float u = controller.compute(dt);
        // u = std::clamp(u, 0.0f, 255.0f);

        float y = process.update(u);

        logger.log(t, target, y, 0, controller.getIntegral(), 0, u);
    }

    return 0;
}
