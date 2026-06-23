#!/bin/bash

cd BipCompiler/distribution
./wrap.sh
cd ../../Chips2BipTransformer
make
cd ..