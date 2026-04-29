#ifndef _PROCESSES_HPP__
#define _PROCESSES_HPP__

#include <iostream>
#include <algorithm>
#include <random>
#include "../../controllers/PIDController/PIDController.hpp"
#include "../../controllers/ControllerBIPInterface.hpp"

void loop_process(
    ControllerPtr pid,
    int& command,
    int& r, int& g, int& b, 
    double sound
);

float random_clap(int cycle);

#endif