#!/bin/bash

export CHIPS_PATH=$(realpath .)
export BIPC_PATH="$CHIPS_PATH"/FullCompileChain/BipCompiler/distribution/build/bipc-latest/bin

cd FullCompileChain/BipCompiler/distribution ; source setenv.sh; cd -
echo "\nEnvironment variables defined:"
printenv | grep CHIPS_PATH
printenv | grep BIPC_PATH
export PATH=$CHIPSC_PATH:$PATH

chmod u+x chipsc