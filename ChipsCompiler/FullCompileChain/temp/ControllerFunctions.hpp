#pragma once

#include "base.hpp"
#include "../../../ModelsUnderControl/SISO/controllers/PIDController/PIDController.hpp"
#include "../../../ModelsUnderControl/AntiWindup/StatefulAntiWindup/BackCalculation/BackCalculationAntiWindup.hpp"
#include "../../../ModelsUnderControl/AntiWindup/StatelessAntiWindup/Clamp/ClampAntiWindup.hpp"

#include <memory>
#include <ostream>

struct pid_controller {
    std::shared_ptr<PIDController> controller;
};

std::ostream& operator<<(std::ostream& os, const pid_controller& c);

pid_controller init_pid_controller(
    chips_float& kp,
    chips_float& ki,
    chips_float& kd,
    chips_float& minOutput,
    chips_float& maxOutput
);

chips_float pid_compute(pid_controller& c, chips_float& dt);

void set_target_value(pid_controller& c, chips_float& target);
void set_current_value(pid_controller& c, chips_float& current);

chips_float get_integral(pid_controller& c);
chips_float get_proportional(pid_controller& c);
chips_float get_derivative(pid_controller& c);