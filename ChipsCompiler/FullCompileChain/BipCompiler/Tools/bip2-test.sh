#!/bin/bash
set -u
set -e

ENGINE_PROFILES="Release Debug"


BRANCH=${1:-staging}

MODULES="-m Compiler/Backend@$BRANCH -m Compiler/Middleend@$BRANCH -m Compiler/Frontend@$BRANCH -m Compiler/Common@$BRANCH -m distribution@$BRANCH -m Engines@$BRANCH"

di=$(mktemp -d --tmpdir=$PWD test-bip-XXXXX)
cd ${di}

checkout.sh $MODULES

cd bip2/distribution
ant -lib lib clean
## needed for building the compiler itself!
./wrap.sh

for CURRENT_CMAKE_PROFILE in $ENGINE_PROFILES; do
    ./wrap.sh -s $CURRENT_CMAKE_PROFILE

    ( . ./setenv.sh reference-engine && cd ../Engines/reference-engine/tests && ./tests/all.sh &> ${di}/reference-engine_$CURRENT_CMAKE_PROFILE.log) &
    ( . ./setenv.sh optimized-engine && cd ../Engines/optimized-engine/tests && ./tests/all.sh &> ${di}/optimized-engine_$CURRENT_CMAKE_PROFILE.log) &
    wait
    echo "REFERENCE ENGINE ($CURRENT_CMAKE_PROFILE)"
    echo "****************"
    cat ${di}/reference-engine_$CURRENT_CMAKE_PROFILE.log
    echo ""
    echo ""
    echo "OPTIMIZED ENGINE ($CURRENT_CMAKE_PROFILE)"
    echo "****************"
    cat ${di}/optimized-engine_$CURRENT_CMAKE_PROFILE.log
done

