#!/bin/bash

set -e
set -u

function help {
    echo 'Bench for BIP Compiler. '
    echo ' -d <DIR>       Directory with all benchmarks'
    echo ' -b <DIR>       Directory where everything will be build'
    echo ' -o <DIR>       Directory where all results will be stored'
}

unset OUTPUTDIR
unset SOURCEDIR
unset BUILDDIR

while getopts  "hd:b:o:" flag
do
  case "$flag" in
      d) SOURCEDIR="$OPTARG";;
      o) OUTPUTDIR="$OPTARG";;
      b) BUILDDIR="$OPTARG";;
      h) help; exit 0;;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done

echo "Source: " $SOURCEDIR
echo "Output: " $OUTPUTDIR
echo "Build: " $BUILDDIR

declare -a stack_test=( 0 )

function fill_test_stack {
    for t in $(find "$SOURCEDIR" -name "bench.conf"); do
	stack_test=("${stack_test[@]}" $(dirname $t))
    done
}

function compile_and_run_test {
    mTESTDIR="$2"

    mBIPC_ARGS="${BIPC_ARGS[$1]}"
    mBIPC="${BIPC[$1]}"

    mCMAKE_PROFILE="${CMAKE_PROFILE[$1]}"

    mSPECIFIC="${ENGINE_SPECIFIC[$1]}"
    mGENERIC="${ENGINE_GENERIC[$1]}"
    mLIB="${ENGINE_LIB[$1]}"

    mTITLE="${TITLE[$1]}"

    mOUTPUTDIR="$OUTPUTDIR/$mTESTDIR"
    mkdir -p $mOUTPUTDIR

    mBUILDDIR=$(mktemp -d --tmpdir="$BUILDDIR/" b.XXXXXXX)
    if [ "${mCMAKE_PROFILE}" != "-" ]; then
	
	/usr/bin/time -f "\"${mTITLE}_bipc\" %e %M" -o "$mOUTPUTDIR/${mTITLE}_BIPC.res" $mBIPC $mBIPC_ARGS --gencpp-output-dir $mBUILDDIR
	mkdir $mBUILDDIR/build
	cd $mBUILDDIR/build
	/usr/bin/time -f "\"${mTITLE}_cmake\" %e %M" -o "$mOUTPUTDIR/${mTITLE}_CMAKE.res" cmake -DCMAKE_BUILD_TYPE=$mCMAKE_PROFILE -DBIP2_ENGINE_GENERIC_DIR=$mGENERIC -DBIP2_ENGINE_SPECIFIC_DIR=$mSPECIFIC -DBIP2_ENGINE_LIB_DIR=$mLIB ..
	/usr/bin/time -f "\"${mTITLE}_make\" %e %M" -o "$mOUTPUTDIR/${mTITLE}_MAKE.res" make -j ${MAKE_PARALLEL_PS:-1}
	/usr/bin/time -f "\"${mTITLE}_exec\" %e %M" -o "$mOUTPUTDIR/${mTITLE}_EXECUTION.res" ./system -s &> /dev/null
    else
	/usr/bin/time -f "\"${mTITLE}_bipc\" %e %M" -o "$mOUTPUTDIR/${mTITLE}_BIPC.res" $mBIPC $mBIPC_ARGS
    fi
}

function run_test {
    unset BIPC_ARGS
    unset BIPC
    unset ENGINE_SPECIFIC
    unset ENGINE_GENERIC
    unset ENGINE_LIB
    unset CMAKE_PROFILE
    unset -f build_result

    TESTDIR="$1"
    TESTDIR_ABS="$PWD/$1"

    . $TESTDIR/bench.conf

    for i in `seq 0 $((${#BIPC[@]}-1))`; do
	echo "**" ${TITLE[$i]}
	pushd $TESTDIR
	compile_and_run_test $i "$TESTDIR"
	popd
    done
    pushd $OUTPUTDIR/$TESTDIR
    build_result $TESTDIR_ABS
    popd
}

fill_test_stack

for t in ${stack_test[@]:1}; do
    echo $t
    run_test $t
done