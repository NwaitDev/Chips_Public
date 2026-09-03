#!/bin/bash
set -euo pipefail

cd BipCompiler/distribution
./wrap.sh
cd ../../Chips2BipTransformer
make
cd ..

# Génération pour le parseur

cd ../Chips_Parser/
rm -rf build
mkdir build
cd build
cmake ..
make
cd ../../FullCompileChain