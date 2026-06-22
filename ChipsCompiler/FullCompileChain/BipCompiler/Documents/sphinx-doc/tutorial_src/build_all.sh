#!/bin/bash

set -e

EXAMPLES=$(find -name 'build.sh' -printf '%h\n')

for ex  in $EXAMPLES; do
    pushd $ex
    ./build.sh
    popd
done