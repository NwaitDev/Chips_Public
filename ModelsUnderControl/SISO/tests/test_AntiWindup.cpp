#include "Drone.hpp"

#include "../../AntiWindup/StatelessAntiWindup/Clamp/ClampAntiWindup.hpp"
#include "../../AntiWindup/StatefulAntiWindup/BackCalculation/BackCalculationAntiWindup.hpp"


int main(){

    constexpr float integral_limit = 30.0f;

    auto aw_clamp = std::make_shared<ClampingAntiWindup>(-integral_limit, integral_limit);
    aw_clamp->setIntegralLimits(-integral_limit, integral_limit);

    DroneExample with_clamp(aw_clamp);
    DroneExample without_clamp(nullptr);

    with_clamp.runScenario("tests/results/drone_with_aw.csv");
    without_clamp.runScenario("tests/results/drone.csv");

    constexpr float kb = 0.2f;


    auto aw_back_calculation = std::make_shared<BackCalculationAntiWindup>(kb);

    DroneExample with_back_calculation(aw_back_calculation);
    DroneExample without_back_calculation(nullptr);

    with_back_calculation.runScenario("tests/results/back_calculation.csv");
    without_back_calculation.runScenario("tests/results/without_back_calculation.csv");
}