#include "blinky_processes.hpp"

void loop_process(
    ControllerPtr pid,
    int& command,
    int& r, int& g, int& b, 
    double sound
){
    double target = 100.0;

    pid->setTargetValue(target);
    pid->setCurrentValue(sound);
    double c = pid->compute(0.1);
    
    command = (int)c;


    // gestion rgb

    const double reference = 100.0;
    const double range = 100.0;

    double delta = sound - reference;
    double alpha = std::min(std::abs(delta) / range, 1.0);

    if (sound == 100.0) {
        r = 0;
        g = 255;
        b = 0;
    }
    else if (sound > reference) {
        // Transition vert -> rouge
        r = static_cast<int>(255 * alpha);
        g = static_cast<int>(255 * (1.0 - alpha));
        b = 0;
    }
    else { 
        // Transition vert -> bleu
        r = 0;
        g = static_cast<int>(255 * (1.0 - alpha));
        b = static_cast<int>(255 * alpha);
    }
}

float random_clap(int cycle) {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<float> dist(-10.0f, 10.0f);

    float result = dist(gen);

    if (cycle % 20 == 9) {
        result = 100;
    } 
    else if (cycle % 20 == 19) {
        result = -100;
    }

    return result;
}