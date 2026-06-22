#!/bin/bash

## choose backends to include in the distribution
# assume we are using cpp, bip & aseba backend.
BACKENDS="cpp bip" #aseba"

# choose filters to include
FILTERS="flattening"

## choose which engines to include in the distribution
ENGINES="reference-engine" #optimized-engine multithread-engine"

## should not change anything below...

pushd $PWD
##
## Compiler packaging
##

unset RELEASE
unset V
SKIP_COMPILER_BUILD=0

CMAKE_PROFILE_ENGINE=Release

RELEASE=0
TEST=""

function help {
 echo 'BIP distribution wrapper
Usage:
  -r              When building a revision to release :)
  -v              Give the version name instead of it being generated
  -p              Build profile for engine (default: Release)
  -s              Skip directly to engine building, no compiler
  -t              Launch tests of: compiler, engines, engines-all
  -h              This help
'
}

while getopts  "sp:hrv:t:" flag
do
  case "$flag" in
      p) CMAKE_PROFILE_ENGINE=$OPTARGS;;
      r) RELEASE=1;;
      h) help; exit 0;;
      s) SKIP_COMPILER_BUILD=1;;
      v) V=$OPTARG;;
      t) TEST="$OPTARG";;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done

# if not specifed on command line...
if [ "$V" == "" ]; then
    if [ "$RELEASE" == "1" ]; then
	V=$(date +%Y.%m)
    else
	V=$(date +%Y.%m.%H%M%S)-DEV
    fi
fi


DISTRIB_BUILD_ROOT=$PWD/$(dirname $0)/build/
DISTRIB_COMPILER=$DISTRIB_BUILD_ROOT/bipc-"$V"

BACKEND_ROOT=../Compiler/Backend/ujf.verimag.bip.backend.
FILTER_ROOT=../Compiler/Middleend/ujf.verimag.bip.middleend.
USER_UI_SCRIPT=../Compiler/Frontend/ujf.verimag.bip.userinterface.cli/

if [ "${TEST}" == "clean" ]; then
    # clean compiler
    rm -rf ${DISTRIB_BUILD_ROOT}/* 

    # clean engines tests
    for eng in $ENGINES; do
        rm -rf ${DISTRIB_BUILD_ROOT}/../../Engines/$eng/tests/build
    done

    exit 0
fi

if [ "${TEST}" == "compiler" ]; then
    ant -Dprogram.version="$V" -lib lib clean publish-local-all tests-all

    exit $?
fi

if [ "${TEST}" == "engines" ]; then
    for eng in $ENGINES; do
        pushd $PWD
        
        source ./setenv.sh $eng
        cd ../Engines/$eng/tests
        rm -rf build/*

        ./tests/compileOnlyTests.sh
        
        if [ $? -ne 0 ]; then
            exit 1
        fi
        
        ./tests/runningTests.sh
        
        if [ $? -ne 0 ]; then
            exit 1
        fi

        popd
    done

    exit 0
fi

if [ "${TEST}" == "engines-all" ]; then
    for eng in $ENGINES; do        
        pushd $PWD
        
        source ./setenv.sh $eng
        cd ../Engines/$eng/tests
        rm -rf build/*

        ./tests/all.sh
        
        if [ $? -ne 0 ]; then
            exit 1
        fi

        popd
    done

    exit 0
fi

if [ "${SKIP_COMPILER_BUILD}" == "0" ]; then

    ant -Dprogram.version="$V" -lib lib clean publish-local-all && \
	mkdir -p $DISTRIB_COMPILER/{bin,lib} && \
	cp -r $USER_UI_SCRIPT/cli-lib/bipc_.sh $DISTRIB_COMPILER/bin/bipc.sh && chmod u+x $DISTRIB_COMPILER/bin/bipc.sh && cp -r $USER_UI_SCRIPT/cli-lib/* $DISTRIB_COMPILER/lib/ && \
	cp -r $USER_UI_SCRIPT/cli-build/*jar $DISTRIB_COMPILER/lib

    if [ "$?" == "0" ]; then
	mkdir -p $DISTRIB_COMPILER/lib/backends
	mkdir -p $DISTRIB_COMPILER/lib/filters

	for fe in $FILTERS; do
	    cp -a ${FILTER_ROOT}$fe/cli-build/*jar $DISTRIB_COMPILER/lib/filters
	    cp -a ${FILTER_ROOT}$fe/cli-lib/* $DISTRIB_COMPILER/lib
	done

	for be in $BACKENDS; do
	    cp -a ${BACKEND_ROOT}$be/cli-build/*jar $DISTRIB_COMPILER/lib/backends
	    cp -a ${BACKEND_ROOT}$be/cli-lib/* $DISTRIB_COMPILER/lib
	done
	VERSION=$(basename $DISTRIB_COMPILER/lib/ujf.verimag.bip.metamodel_* .jar | cut -d'_' -f2)
#    cd build && tar zcvf bipc_$VERSION.tar.gz bipc-$V
	cd build && tar zcvf bipc_"$V".tar.gz bipc-"$V"
	rm -f bipc-latest; ln -s bipc-"$V" bipc-latest
	find bipc-"$V" > bipc-"$V".FILES
    else
	echo "Error when building"
	exit -1
    fi

    popd
fi ## SKIP_COMPILER_BUILD

pushd $PWD
##
## Engines packaging
##

ENGINES_ROOT=$PWD/../Engines 
pushd $PWD 

for eng in $ENGINES; do
    pushd $PWD
    mkdir -p build/ENGINE-$eng && \
    cd build/ENGINE-$eng && \
    cmake \
       -D VERSION="$V" \
       -D CMAKE_BUILD_TYPE=${CMAKE_PROFILE_ENGINE} \
       $ENGINES_ROOT/$eng && make package && cp *.tar.gz $DISTRIB_BUILD_ROOT
    popd
done

popd

popd
