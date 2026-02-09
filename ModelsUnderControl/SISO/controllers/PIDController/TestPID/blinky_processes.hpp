#ifndef _PROCESSES_HPP__
#define _PROCESSES_HPP__

#include <iostream>
#include <algorithm>
#include "../PIDController.hpp"
#include "../../ControllerBIPInterface.hpp"

void init_process(
    int& rx1,
    int& tx1, int& tx2, int& tx3, int& tx4, int& tx5, int& tx6,
    int& r, int& g, int& b, int& rB, int& gB, int& bB, int& sound
);

void loop_process(
    ControllerPtr pid, 
    int rx1,
    int& tx2, int& tx5, int& tx6,
    int& r, int& g, int& b, 
    int rB, int gB, int bB,
    int sound
);

#endif