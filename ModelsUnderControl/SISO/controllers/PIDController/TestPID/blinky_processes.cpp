#include "blinky_processes.hpp"

void init_process(
    int& rx1,
    int& tx1, int& tx2, int& tx3, int& tx4, int& tx5, int& tx6,
    int& r, int& g, int& b, int& rB, int& gB, int& bB, int& sound
){
    rx1=0;
    tx1=0; tx2=0; tx3=0; tx4=0; tx5=0; tx6=0;
    r = 0; g = 0; b = 0;
    rB = 0; gB = 0; bB = 0;
    sound = 0;
}

void loop_process(
    ControllerPtr pid,
    int rx1,
    int& tx2, int& tx5, int& tx6,
    int& r, int& g, int& b, 
    int rB, int gB, int bB, 
    int sound
){
    bool noisy = (sound > 50);
    bool neighbor_active = (rB > 0 || gB > 0);

    double target = 100.0;
    if (noisy || neighbor_active) {
        target = 250.0;
    }

    double measure = (double)rx1;

    pid->setTargetValue(target);
    pid->setCurrentValue(measure);
    double command = pid->compute(0.1);
    
    int intensity = (int)command;
    if (intensity > 255) intensity = 255;
    if (intensity < 0) intensity = 0;
    
    tx2 = intensity; 

    bool prev_has_sound = (tx5 == 1);
    int silence_count = tx6;
    int r_out = 0, g_out = 0, b_out = 0;

    if (noisy) {
        silence_count = 0;
        if (prev_has_sound) r_out = 1; else g_out = 1; 
        prev_has_sound = true;
    } else {
        prev_has_sound = false;
        if (neighbor_active) {
            silence_count = 0; 
            if (rB > 0) r_out = 1;
            if (gB > 0) g_out = 1;
        } else {
            silence_count++;
            if (silence_count >= 2) {
                b_out = 1;
            } else {
                if (r > 0) r_out = 1;
                if (g > 0) g_out = 1;
            }
        }
    }

    r = r_out * intensity;
    g = g_out * intensity;
    b = b_out * intensity;

    tx5 = prev_has_sound ? 1 : 0;
    tx6 = silence_count;

}