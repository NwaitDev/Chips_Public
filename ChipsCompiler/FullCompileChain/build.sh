#!/bin/bash
set -euo pipefail

cd BipCompiler/distribution
./wrap.sh
cd ../../Chips2BipTransformer
make
cd ..