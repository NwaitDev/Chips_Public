#!/bin/bash

export CHIPS_PATH=$(realpath ../..)
export CHIPSC_PATH="$CHIPS_PATH"/ChipsCompiler/FullCompileChain/Chips2BipTransformer
cd BipCompiler/distribution ; source setenv.sh; cd -
