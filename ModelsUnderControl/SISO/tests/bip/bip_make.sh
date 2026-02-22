#!/bin/bash

NAME="blinky"
BIP_PATH="/home/lucas/bip/compiler/distribution"

rm -rf ./output/*
mkdir -p ./output/build/

cd $BIP_PATH
source "./setenv.sh"
cd -

$BIP_PATH/build/bipc-latest/bin/bipc.sh \
    -p blinkyBIP \
    -d "System()" \
    -I . \
    --gencpp-cc-I . \
    --genbip-follow-used-packages \
    --gencpp-follow-used-packages \
    --gencpp-output output

cd ./output/build && cmake .. -Wno-dev
make

cd ../../
./output/build/system