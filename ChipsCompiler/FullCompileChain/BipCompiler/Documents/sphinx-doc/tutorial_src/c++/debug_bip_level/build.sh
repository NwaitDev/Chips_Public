#!/bin/bash
set -e
set -x verbose

mkdir -p output build
bipc.sh -I . -p HelloPackage -d "HelloCompound()"\
    --gencpp-output output \
    --gencpp-enable-bip-debug \
    --gencpp-cc-I $PWD/ext-cpp
cd build
cmake -D CMAKE_BUILD_PROFILE=Debug ../output
make

echo "Finished. Run: ./build/system"
