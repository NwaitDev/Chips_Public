#include <iostream>
#include "../controllers/ControllerBIPInterface.hpp"
#include "../utils/printing.hpp"

float simulerPhysique(float y, float u, float perturbation) {
    return (0.9f * y) + (0.1f * u * 10.0f) - perturbation;
}

int main() {
    ControllerBIPInterface controller;

    int horizon = 20; 
    controller.init(horizon); 
    
    controller.setSystemModel(0.9f, 1.0f); 
    
    controller.setTarget(5.0f);
    controller.setSafetyLimits(4.0f, 100.0f);

    CppOutStream file = openStream("test_result");

    printInStream(file, "Temps;Cible;Tension;Commande;Securite\n");

    float tension = 5.0f;
    float perturbation = 0.0f;

    for (int t = 0; t < 100; ++t) {
        if (t >= 30 && t < 60) {
            perturbation = 0.5f;
        } else {
            perturbation = 0.0f;
        }

        float commande = controller.update(tension);

        tension = simulerPhysique(tension, commande, perturbation);
        printInStream(file, t); 
        printInStream(file, ";"); 

        printInStream(file, 5.0);
        printInStream(file, ";");

        printInStream(file, tension);
        printInStream(file, ";");

        printInStream(file, commande);
        printInStream(file, ";");

        printInStream(file, 3.5);
        printInStream(file, "\n");
    }

    closeStream(file);
    return 0;
}