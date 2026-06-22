#!/bin/bash
set -e
set -x verbose

mkdir -p output build

bipc.sh -I . -p HelloPackage -d "HelloCompound()"\
    --gencpp-output output \
    --gencpp-cc-I $PWD/ext-cpp \
    --gencpp-no-serial

cd build
cmake ../output
make

echo "Finished. Run: ./build/system"
