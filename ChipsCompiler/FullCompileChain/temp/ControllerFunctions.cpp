#include "ControllerFunctions.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const pid_controller& c) {
    return os << "PIDController";
}

pid_controller init_pid_controller(
    chips_float& kp,
    chips_float& ki,
    chips_float& kd,
    chips_float& minOutput,
    chips_float& maxOutput
) {
    pid_controller wrapper;

    auto aw_clamp = std::make_shared<ClampingAntiWindup>(-30.0f, 30.0f);
    aw_clamp->setIntegralLimits(-30.0f, 30.0f);
    auto aw_back = std::make_shared<BackCalculationAntiWindup>(0.2f);



    wrapper.controller = std::make_shared<PIDController>(
        std::get<0>(kp),
        std::get<0>(ki),
        std::get<0>(kd),
        nullptr,
        nullptr,
        aw_back
    );

    wrapper.controller->setOutputLimits(std::get<0>(minOutput), std::get<0>(maxOutput));

    if(wrapper.controller->getAntiWindup()){
        std::cout << "JA\n";
    }

    std::cout << "KP: " << std::get<0>(kp) << "\n"
              << "KI: " << std::get<0>(ki) << "\n"
              << "KD: " << std::get<0>(kd) << "\n"
              << "min: " << std::get<0>(minOutput) << "\n"
              << "max: " << std::get<0>(maxOutput) << "\n";

    return wrapper;
}

chips_float pid_compute(pid_controller& c, chips_float& dt) {
    if (!c.controller) {
        return std::make_tuple(0.0, 0);
    }

    std::cout << "Target: " << c.controller->getTargetValue() << "\n"
              << "Current: " << c.controller->getCurrentValue() << "\n"
              << "kp: " << c.controller->getKp() << "\n" 
              << "ki: " << c.controller->getKi() << "\n"
              << "kd: " << c.controller->getKd() << "\n";

    return std::make_tuple(c.controller->compute(std::get<0>(dt)), 0);
}

void set_target_value(pid_controller& c, chips_float& target) {
    if (c.controller) {
        c.controller->setTargetValue(std::get<0>(target));
    }
}

void set_current_value(pid_controller& c, chips_float& current) {
    if (c.controller) {
        c.controller->setCurrentValue(std::get<0>(current));
    }
}

chips_float get_integral(pid_controller& c){
    return std::make_tuple(c.controller->getIntegral(), 0);
}
chips_float get_proportional(pid_controller& c){
    return std::make_tuple(c.controller->getProportional(), 0);
}
chips_float get_derivative(pid_controller& c){
    return std::make_tuple(c.controller->getDerivative(), 0);
}