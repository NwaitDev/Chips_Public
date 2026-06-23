#!/bin/bash
set -e
set -x verbose

mkdir -p output build

bipc.sh -I . -p priorities_in_compound -d "Model()" \
    --gencpp-output output

cd build
cmake ../output
make

echo "Finished. Run: ./build/system"
