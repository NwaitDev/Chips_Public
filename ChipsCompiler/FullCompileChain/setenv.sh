#!/bin/bash

export CHIPS_PATH=$(realpath ../..)
export CHIPSC_PATH="$CHIPS_PATH"/ChipsCompiler/FullCompileChain/Chips2BipTransformer
export BIPC_PATH="$CHIPS_PATH"/ChipsCompiler/FullCompileChain/BipCompiler/distribution/build/bipc-latest/bin
cd BipCompiler/distribution ; source setenv.sh; cd -
