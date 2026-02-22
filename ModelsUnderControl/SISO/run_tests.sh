#!/bin/bash

set -e

CXX=g++
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

BUILD_DIR=build
TEST_DIR=tests
RESULTS_DIR=tests/results
PLOTS_DIR=tests/plots
VENV_DIR=${PLOTS_DIR}/venv
PYTHON_SCRIPT=${PLOTS_DIR}/plot_results.py

echo "Création du dossier build"
mkdir -p ${BUILD_DIR}
mkdir -p ${RESULTS_DIR}

echo "Compilation des contrôleurs"

${CXX} ${CXXFLAGS} -c controllers/PController/PController.cpp      -I. -o ${BUILD_DIR}/PController.o
${CXX} ${CXXFLAGS} -c controllers/PIController/PIController.cpp    -I. -o ${BUILD_DIR}/PIController.o
${CXX} ${CXXFLAGS} -c controllers/PIDController/PIDController.cpp  -I. -o ${BUILD_DIR}/PIDController.o
${CXX} ${CXXFLAGS} -c controllers/ControllerBIPInterface.cpp       -I. -o ${BUILD_DIR}/ControllerBIPInterface.o

CONTROLLER_OBJS="
${BUILD_DIR}/PController.o
${BUILD_DIR}/PIController.o
${BUILD_DIR}/PIDController.o
${BUILD_DIR}/ControllerBIPInterface.o
"

echo "Compilation des tests"

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_PController.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_p

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_PIController.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_pi

${CXX} ${CXXFLAGS} \
    ${TEST_DIR}/test_PIDController.cpp \
    ${CONTROLLER_OBJS} \
    -I. \
    -o ${BUILD_DIR}/test_pid

echo "Exécution des tests"

./${BUILD_DIR}/test_p
./${BUILD_DIR}/test_pi
./${BUILD_DIR}/test_pid

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

echo "Désactivation et suppression du virtualenv"
deactivate
rm -rf ${VENV_DIR}

echo "Fin de l'execution des tests."