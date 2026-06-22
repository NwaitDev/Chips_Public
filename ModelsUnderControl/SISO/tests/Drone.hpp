#include <cmath>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

#include "../controllers/PIDController/PIDController.hpp"
#include "../../AntiWindup/IAntiWindup.hpp"
#include "common/CsvLogger.hpp"

struct SettlingResult {
    float settlingTime;   // temps auquel stabilisé
    bool  settled;        // false si jamais stabilisé
};

SettlingResult computeSettlingTime(
    const std::vector<float>& time,
    const std::vector<float>& altitude,
    float target,
    float bandPercent = 0.05f)
{
    const float lo = target * (1.0f - bandPercent);
    const float hi = target * (1.0f + bandPercent);

    // On cherche le dernier indice ou le signal est HORS bande,
    // puis le temps de stabilisation = pas suivant
    int lastOutside = -1;
    for (int i = 0; i < static_cast<int>(altitude.size()); i++) {
        if (altitude[i] < lo || altitude[i] > hi) {
            lastOutside = i;
        }
    }

    if (lastOutside == -1) {
        // Signal dans la bande depuis le debut
        return { time[0], true };
    }

    int settledIdx = lastOutside + 1;
    if (settledIdx >= static_cast<int>(time.size())) {
        // Signal encore hors bande a la fin de la simulation
        return { -1.0f, false };
    }

    return { time[settledIdx], true };
}



constexpr float GRAVITY = 9.81f;
constexpr float KP = 0.29f;
constexpr float MASS = 0.2f;
constexpr float DRAG_COEFF = 0.8f; // simple linear drag coefficient
constexpr float TIME_KEEP = 10.0f;

class Drone{

public:
    float m;
    float altitude;
    float alt_max;
    float velocity;

    Drone(float mass) : m(mass), altitude(0), alt_max(0), velocity(0){}

    float update(float u, float dt){
        float K = 4.0f * KP * pow(((2.0 * M_PIf) / 60.0f), 2);
        float Fp = K * pow(u, 2);
        //linear drag proportinal to velocity (simple damping)
        float drag = DRAG_COEFF * velocity;
        float a = (Fp / m) - GRAVITY - (drag / m);

        velocity += a * dt;
        altitude += velocity * dt;

        if(altitude < 0){
            altitude = 0;
            velocity = 0;
        }
        alt_max = (alt_max < altitude) ? altitude : alt_max;
        return altitude;
    }
};

class DroneExample{

public:
    float kp;
    float ki;
    float kd;

    float u_min;
    float u_max;

    float min_integral_limit;
    float max_integral_limit;

    float dt;
    float simTime;

    float target;

    PIDController controller;
    Drone drone;

    DroneExample(std::shared_ptr<IAntiWindup> aw,
                 float kp = 1.5f, float ki = 0.6f, float kd = 0.0f,
                 float u_min = 0.0f, float u_max = 15.0f,
                 float min_integral_limit = -30.0f, float max_integral_limit = 30.0f,
                 float dt = 0.1f, float simTime = 60.0f, float target = 5.0f)
                                : kp(kp),
                                    ki(ki),
                                    kd(kd),
                                    u_min(u_min),
                                    u_max(u_max),
                                    min_integral_limit(min_integral_limit),
                                    max_integral_limit(max_integral_limit),
                                    dt(dt),
                                    simTime(simTime),
                                    target(target),
                                    controller(kp, ki, kd),
                                    drone(MASS) {
        controller.setOutputLimits(u_min, u_max);
        if(aw){
            controller.setAntiWindup(aw);
        }
    }

    void runScenario(const std::string& CsvPath){

        std::vector<float> times;
        std::vector<float> altitudes;
        std::vector<float> commandes;

        float integral_max = 0.0f;
        float avg_command = 0.0f;

        CsvLogger logger(CsvPath);

        for(float t = 0.0f; t <= simTime; t += dt){
            // if(t < TIME_KEEP){
            //     drone.altitude = 0.0f;
            // }

            controller.setCurrentValue(drone.altitude);
            controller.setTargetValue(target);
            float u = controller.compute(dt);
            float y = drone.update(u, dt);
            // if(t < TIME_KEEP){
            //     y = 0.0f;
            // }

            times.push_back(t);
            altitudes.push_back(y);
            commandes.push_back(u);

            if(controller.getIntegral() > integral_max) integral_max = controller.getIntegral();

            avg_command += u;
            logger.log(t, target, y, controller.getProportional(), controller.getIntegral(), controller.getDerivative(), u);
        }

        float command_max = 0.0f;
        float command_min_local = 0.0f;

        for(int i = 0; i < commandes.size(); i++){
            if(commandes[i] > command_max){
                command_max = commandes[i];
                command_min_local = commandes[i];
            }

            if(command_max == u_max && commandes[i] < command_min_local){
                command_min_local = commandes[i];
            }
        }

        std::sort(commandes.begin(), commandes.end());

        auto result = computeSettlingTime(times, altitudes, target);

        std::cout << CsvPath << std::endl;

        std::cout << "Altitude max: " << drone.alt_max << std::endl;
        std::cout << "Dépassement maximal: " << ((drone.alt_max - target) / target * 100) << "%" << std::endl;
        if(result.settled){
            std::cout << "Temps de stabilisation (+-5%) : " << result.settlingTime << "s" << std::endl;
        }else{
            std::cout << "Le système ne s'est pas stabilisé dans le temps imparti" << std::endl;
        }
        std::cout << "Integral maximal: " << integral_max << std::endl;
        std::cout << "Commande moyenne: " << (avg_command / times.size()) << std::endl;
        std::cout << "Commande minimal: " << commandes.front() << std::endl;
        std::cout << "Commande minimal local: " << command_min_local << std::endl;
        std::cout << "Commande maximal: " << commandes.back() << std::endl;
    }

};