#!/bin/bash

export CHIPS_PATH=$(realpath ../..)
export CHIPSC_PATH="$CHIPS_PATH"/ChipsCompiler/FullCompileChain
cd BipCompiler/distribution ; source setenv.sh; cd -

export BIP_PATH="$CHIPSC_PATH"/ChipsCompiler/FullCompileChain/BipCompiler/
echo "\nEnvironment variables defined:"
printenv | grep CHIPS_PATH
printenv | grep BIP_PATH
printenv | grep CHIPSC_PATH
export PATH=$CHIPSC_PATH:$PATH