#!/bin/bash

start=$(date +%s.%N)

rm -r build/
mkdir build/

bipc -I . -p Drone -d "SYSTEM_COMPOUND()" \
    --gencpp-output-dir build \
    --gencpp-follow-used-packages --gencpp-cc-I . \
    --gencpp-cc-extra-src ControllerFunctions.cpp \
    --gencpp-cc-extra-src ../../../ModelsUnderControl/SISO/controllers/PIDController/PIDController.cpp \
    --gencpp-cc-extra-src ../../../ModelsUnderControl/AntiWindup/StatefulAntiWindup/BackCalculation/BackCalculationAntiWindup.hpp \
    --gencpp-cc-extra-src ../../../ModelsUnderControl/AntiWindup/StatelessAntiWindup/Clamp/ClampAntiWindup.hpp

cd build/ 
mkdir build/
cd build/
cmake ..
make

end=$(date +%s.%N)

echo "Temps total : $(echo "$end - $start" | bc) s"
