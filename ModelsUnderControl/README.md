# Models Under Control  
Modular C++ control framework for SISO, MPC, and MIMO environments.

---

## Authors

- BARTHOD Julien  
- DELACROIX Luc
- ROYER Lucas 

Master 2 ISL at University of Marie et Louis Pasteur  
Academic Year 2025 – 2026  

---

# Project overview

This project provides a generic and reusable control framework designed to integrate multiple control strategies within the BIP (Behavior, Interaction, Priority) framework.

The objective is to design controllers and interfaces that are :
- Modular  
- Reusable  
- Generic across different control environments  

Three control environments are implemented in this project :

### SISO : Single Input Single Output

Implements classical feedback controllers for a simple system with a single input and a single output. The implemented controllers include :

- **P** : *Proportional Controller*  
- **PI** : *Proportional-Integral Controller*  
- **PID** : *Proportional-Integral-Derivative Controller*  
- Orientation Controller (angle regulation use-case)

### MPC : Model Predictive Control

Implements a Model Predictive Control strategy for a simple system with disturbance. The MPC controller is designed to optimize control actions based on :
- A system model
- A prediction horizon
- Cost function optimization
- Disturbance handling

### MIMO : Multi Input Multi Output

Implements a discrete-time Linear Quadratic Regulator (LQR) controller for a simple system with multiple inputs and outputs. The LQR controller is designed to minimize a quadratic cost function based on :
- A state-space model of the system
- A quadratic cost function
- State feedback control

---

## Repository structure

```
├── SISO/
│   ├── IControllerSISO.hpp
│   ├── controllers/
│   │   ├── PController/
│   │   ├── PIController/
│   │   ├── PIDController/
│   │   ├── OrientationController/
│   │   └── ControllerBIPInterface.*
│   ├── tests/
│   │   ├── test_PController.cpp
│   │   ├── test_PIController.cpp
│   │   ├── test_PIDController.cpp
│   │   ├── common/
│   │   ├── results/
│   │   ├── plots/
│   │   └── bip/
│   ├── utils/
│   └── run_tests.sh
│
├── MPC/
│   ├── IControllerMPC.hpp
│   ├── controllers/
│   │   ├── MPCController.*
│   │   └── ControllerBIPInterface.*
│   ├── testMPC/
│   ├── utils/
│   └── run_test.sh
│
├── MIMO/
│   ├── IControllerMIMO.hpp
│   ├── controllers/
│   │   └── LQRController.*
│   ├── utils/
│   └── test_drone_2d/
│       ├── make.sh
│       ├── plot_drone.py
│       └── *.cpp
│
├── README.md
├── Doxyfile
└── docs/doxygen/
```

---

# System tested on

- OS : Windows 11 with WSL 2 (Ubuntu 24.04.3 LTS)
- g++ : 13.3.0
- Python : 3.12.3
- pip : 24.0
- venv : standard Python 3.12 venv module
- matplotlib : 3.6.3
- Doxygen : 1.9.8
- BIP : bipc-2026.02.103757-DEV

---

# Installation

The following tools must be installed :
- g++ (C++ compiler)
- Python3 (for plotting)
- pip (venv, matplotlib)
- Doxygen (for documentation)
- BIP compiler (for BIP integration)

Commands to install dependencies on Ubuntu :

```
sudo apt update
sudo apt install g++ python3 python3-venv python3-pip doxygen
pip3 install matplotlib
```

BIP compiler must be downloaded and installed from the official repository : https://gricad-gitlab.univ-grenoble-alpes.fr/verimag/bip/compiler

---

# SISO Environment

## Description

Implements classical feedback controllers for a simple system with a single input and a single output. The implemented controllers include :

- Predictive Controller
- Predictive-Integral Controller
- Predictive-Integral-Derivative Controller
- Orientation Controller

All SISO controllers implement the same interface defined in ```IControllerSISO.hpp```

This ensures controller interchangeability.

## Run SISO tests

To run the SISO tests and generate plots, execute the following commands from the project root :

```
cd SISO
chmod +x run_tests.sh
./run_tests.sh
```

This script :

1. Compiles controllers and test executables
2. Runs simulations
3. Generates CSV files in : ```SISO/tests/results/```
4. Creates a Python virtual environment
5. Installs matplotlib
6. Launches plotting script : ```SISO/tests/plots/plot_results.py```
7. Erases the virtual environment after closing the figures

Two figures are displayed:
- System response vs reference
- Control signal comparison


To run BIP integration tests, you must edit the BIP path in the ```bip_make.sh``` script located in ```SISO/tests/bip/``` :
```
BIP_PATH="your_local_bip_path"
```

After editing the BIP path, execute the following commands from the project root :
```
cd SISO/tests/bip/
chmod +x bip_make.sh
./bip_make.sh
```

This will compile the BIP test executable and run the simulation, generating a CSV file with the results.

---

# MPC Environment

## Description

Implements a Model Predictive Control strategy for a simple system with disturbance.

The MPC controller :
- Uses a predictive model
- Handles disturbances
- Supports constraints
- Computes optimal control over a prediction horizon

All MPC controllers implement the same interface defined in ```IControllerMPC.hpp```

## Run MPC tests

To run the MPC simulation, execute the following commands from the project root :

```
cd MPC
chmod +x run_test.sh
./run_test.sh
```

This will :

1. Compile the test executable
2. Run a simulation with disturbance
3. Generate a CSV results file

The main test file is located in : ```MPC/testMPC/main.cpp```

---

# MIMO Environment

## Description

Implements a discrete-time LQR controller for a 2D drone model.

Two scenarios:
- Without wind disturbance
- With wind disturbance

All MIMO controllers implement the same interface defined in ```IControllerMIMO.hpp```

## Run MIMO tests

To run the MIMO simulation, execute the following commands from the project root :

```
cd MIMO/test_drone_2d
chmod +x make.sh
./make.sh
```

This will :

1. Compile test executables for both scenarios, with and without disturbance
2. Run simulations
3. Generate CSV results files
4. Launch the plotting script : ```plot_drone.py```

Three figures are displayed :
- Drone position 
- Drone velocity 
- Control inputs 

These figures compare the system response with and without wind disturbance both for X and Y coordinates.

---

# Documentation

Documentation is fully generated using Doxygen. The Doxyfile is located in the project root and is configured to generate documentation for all three environments.

To visualize the generated documentation, open the following file in a web browser : ```docs/doxygen/html/index.html```

To regenerate the documentation after making changes to the code, execute the following command from the project root :

```
doxygen Doxyfile
```

The Doxyfile is configured to include all source files and generate comprehensive documentation for classes, interfaces, and functions across all environments.
