#!/bin/bash

set -e

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

BUILD_DIR=build
TEST_DIR=tests
RESULTS_DIR=tests/results
PLOTS_DIR=tests/plots
VENV_DIR=${PLOTS_DIR}/venv
PYTHON_SCRIPT=${PLOTS_DIR}/plot_results_filters.py

echo "Création du dossier build"
mkdir -p ${BUILD_DIR}
mkdir -p ${RESULTS_DIR}

echo "Compilation des contrôleurs"

${CXX} ${CXXFLAGS} -c controllers/PIDController/PIDController.cpp -I. -o ${BUILD_DIR}/PIDController.o

CONTROLLER_OBJS="
${BUILD_DIR}/PIDController.o
"

echo "Compilation des tests"

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_PID_Filter_Low_Pass.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_pid_low_pass

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_PID_Filter_High_Pass.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_pid_high_pass

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_High_Low_Pass.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_high_low_pass

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_PID_Filter_Median.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_pid_median

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_PID_Filter_AlphaBeta.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_pid_alphabeta


echo "Exécution des tests"

./${BUILD_DIR}/test_pid_low_pass
./${BUILD_DIR}/test_pid_high_pass
./${BUILD_DIR}/test_high_low_pass
./${BUILD_DIR}/test_pid_median
./${BUILD_DIR}/test_pid_alphabeta

echo "Tests terminés"
echo "Fichiers CSV générés :"
ls *.csv 2>/dev/null || echo "Aucun CSV trouvé"

#----------------------------------------------------------------------------------

echo "Création du virtualenv Python"
python3 -m venv ${VENV_DIR}

echo "Activation du virtualenv"
source ${VENV_DIR}/bin/activate

echo "Mise à jour de pip"
pip install --upgrade pip >/dev/null

echo "Installation des dépendances Python"
pip install matplotlib >/dev/null

echo "Lancement du script de tracé"
python3 ${PYTHON_SCRIPT}

echo "Désactivation et supression du virtualenv"
deactivate
rm -rf ${VENV_DIR}

echo "Fin de l'execution des tests."