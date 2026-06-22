#! /bin/bash
__INIT_OK=0

oneTimeSetUp_MASTER(){
    BIPC=bipc.sh
    TESTS_ROOT_DIR=$PWD/$(dirname $0)/../src
##    OUTPUT_DIR=$PWD/$(dirname $0)/../build/cppoutput
    INIT_PWD=$PWD # most probably useless as path should be absolute everywhere.
    __INIT_OK=1
}

compute_output_dir(){
    OUTPUT_DIR=$PWD/$(dirname $0)/../build/cppoutput-${KIND}_$TEST
}

checkInit() {
    if [ "${__INIT_OK}" == "0" ]; then
	echo "Not initialized correctly"
	return 255
    fi
}

#
# This one is executed before EACH test.
# It cleans the output
#
##setUp() {
##    cd $INIT_PWD && clean_output $OUTPUT_DIR
##}

# oneTimeTearDown() {
#     checkInit || return 255

#     if [ "$?" != "0" ]; then
# 	return 255
#     fi
#     cd $INIT_PWD 
#     rm -rf $PWD/$(dirname $0)/../build/
# }


clean_output() {
    checkInit || return 255

    if [ "$?" != "0" ]; then
	return 255
    fi

##    rm -rf $OUTPUT_DIR
}

#
# Helper function that executes the BIP compiler
# with the CPP backend and outputs everything
# in the $OUTPUT_DIR directory
#
compile_to_cpp() {
    checkInit || return 255
    if [ "$?" != "0" ]; then
	return 255
    fi

    pushd $PWD

    compute_output_dir
##    OUTPUT_DIR=$PWD/$(dirname $0)/../build/cppoutput-$KIND_$TEST

    if [ "$3" != "" ]; then
      ROOT_DEF="-d $3"
    else
      ROOT_DEF=""
    fi

    args=("$@")
    EXTRA_ARGS=${args[@]:3}

    mkdir -p $OUTPUT_DIR || (popd; return 255)
    if [ "$?" != "0" ]; then
	return 255
    fi

    echo "RUNNING:" $BIPC -I "$2" \
	  -p "$1" \
	  $ROOT_DEF \
          --gencpp-output-dir $OUTPUT_DIR \
          --gencpp-follow-used-packages \
          --gencpp-cc-extra-opt -pthread \
          --gencpp-ld-extra-opt -pthread \
	   ${DEFAULT_BIPC_ARGS:-""} \
          $EXTRA_ARGS

    $BIPC -I "$2" \
	  -p "$1" \
	  $ROOT_DEF \
          --gencpp-output-dir $OUTPUT_DIR \
          --gencpp-follow-used-packages \
          --gencpp-cc-extra-opt -pthread \
          --gencpp-ld-extra-opt -pthread \
	   ${DEFAULT_BIPC_ARGS:-""} \
          $EXTRA_ARGS || (popd; return 255)

    if [ "$?" != "0" ]; then
	return 255
    fi

    popd
}

#
# Helper function that executes cmake & make
# to actually compile and link the generated code with
# the provided engines (you must set BIP2_HOME)
#
compile_and_link_with_engine() {
    checkInit || return 255

    if [ "$?" != "0" ]; then
	return 255
    fi

    pushd $PWD

    compute_output_dir
##    OUTPUT_DIR=$PWD/$(dirname $0)/../build/cppoutput-${KIND}_$TEST

    cd $OUTPUT_DIR/ && mkdir -p build && cd build || (popd; return 255)

    if [ "$?" != "0" ]; then
	return 255
    fi

    cmake .. && \
    make -j ${MAKE_PARALLEL_PS:-1} || (popd; return 255)

    if [ "$?" != "0" ]; then
	return 255
    fi
    popd
}
