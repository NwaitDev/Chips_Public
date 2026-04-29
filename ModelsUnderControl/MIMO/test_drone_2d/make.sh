#!/bin/bash
set -e

CXX=g++
CXXFLAGS="-std=c++17 -O2"

CTRL_CPP="../controllers/LQRController.cpp"

OUT1="lqr_nowind"
OUT2="lqr_wind"

SRC1="lqr_drone_2d_nowind.cpp"
SRC2="lqr_drone_2d_wind.cpp"

echo "Compiling $OUT1"
$CXX $CXXFLAGS $SRC1 $CTRL_CPP -o $OUT1

echo "Compiling $OUT2"
$CXX $CXXFLAGS $SRC2 $CTRL_CPP -o $OUT2

echo "Running $OUT1"
./$OUT1

echo "Running $OUT2"
./$OUT2

echo "Plotting results"
python3 plot_drone.py