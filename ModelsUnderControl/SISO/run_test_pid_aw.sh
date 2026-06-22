#!/bin/bash

set -e

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

BUILD_DIR=build
TEST_DIR=tests
RESULTS_DIR=tests/results
PLOTS_DIR=tests/plots
VENV_DIR=${PLOTS_DIR}/venv
# PYTHON_SCRIPT=${PLOTS_DIR}/plot_results_aw.py
PYTHON_SCRIPT=${PLOTS_DIR}/plot_drone_antiwindup.py

echo "Création du dossier build"
mkdir -p ${BUILD_DIR}
mkdir -p ${RESULTS_DIR}

echo "Compilation des contrôleurs"
${CXX} ${CXXFLAGS} -c controllers/PIDController/PIDController.cpp  -I. -o ${BUILD_DIR}/PIDController.o

CONTROLLER_OBJS="
${BUILD_DIR}/PIDController.o
"
echo "Compilation des tests"

# ${CXX} ${CXXFLAGS} \
#     ${TEST_DIR}/test_PID_AntiWindup.cpp \
#     ${CONTROLLER_OBJS} \
#     -I. \
#     -o ${BUILD_DIR}/test_pid_drone


# ${CXX} ${CXXFLAGS} \
#     ${TEST_DIR}/test_PI_BackCalculation.cpp \
#     ${CONTROLLER_OBJS} \
#     -I. \
#     -o ${BUILD_DIR}/test_pi_backcalc

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_AntiWindup.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_AntiWindup

echo "Exécution des tests"

# ./${BUILD_DIR}/test_pi_backcalc
# ./${BUILD_DIR}/test_pid_drone

./${BUILD_DIR}/test_AntiWindup

echo "Tests terminés"
echo "Fichiers CSV générés :"
ls tests/results/*.csv 2>/dev/null || echo "Aucun CSV trouvé"

#----------------------------------------------------------------------------------

echo "Création du virtualenv Python"
rm -rf ${VENV_DIR}
python3 -m venv ${VENV_DIR}

echo "Activation du virtualenv"
source ${VENV_DIR}/bin/activate

echo "Installation des dépendances Python"
python3 -m pip install matplotlib >/dev/null

echo "Lancement du script de tracé"
python3 ${PYTHON_SCRIPT}

echo "Désactivation et suppression du virtualenv"
deactivate
rm -rf ${VENV_DIR}

echo "Fin de l'execution des tests."