#!/bin/bash

echo "Compilation du contrôleur MPC en cours"

g++ ./testMPC/main.cpp ./controllers/MPCController.cpp ./controllers/ControllerBIPInterface.cpp ./utils/printing.cpp -o test_mpc
./test_mpc

if [ $? -eq 0 ]; then
    echo "Compilation réussie !"
else
    echo "Erreur lors de la compilation"
fi

echo "Donnée de test générée dans le fichier test_results.csv"
