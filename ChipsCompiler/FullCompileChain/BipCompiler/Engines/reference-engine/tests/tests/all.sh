#!/bin/bash

set -u

# Hammer the CPU :)
export MAKE_PARALLEL_PS=4

TESTS_SCRIPTS_ROOT=$(dirname $0)
ROOT=${TESTS_SCRIPTS_ROOT}/../
LOGS=${ROOT}/logs/

SOMEONE_FAILLED=0

rm -rf ${LOGS}
rm -rf  build/*

mkdir -p ${LOGS}

OPTIM_LEVELS="0 1 2 3"

CLI_ARGS_TO_TEST[0]=""
CLI_ARGS_TO_TEST[${#CLI_ARGS_TO_TEST[*]}]="--gencpp-enable-bip-debug"

for ((n=0; n < ${#CLI_ARGS_TO_TEST[*]}; n++))
do
cli_arg=${CLI_ARGS_TO_TEST[$n]}

for optim_lvl in $OPTIM_LEVELS; do
    echo "OPTIM LEVEL: ${optim_lvl}"
    DEFAULT_BIPC_ARGS="--gencpp-optim=${optim_lvl} ${cli_arg}" ${TESTS_SCRIPTS_ROOT}/runningTests.sh  &>  ${LOGS}/run_optlvl_${optim_lvl}__"${cli_arg}".txt &
    echo "Running tests started..."
    PID1=$!
    DEFAULT_BIPC_ARGS="--gencpp-optim=${optim_lvl} ${cli_arg}" ${TESTS_SCRIPTS_ROOT}/compileOnlyTests.sh &> ${LOGS}/compile_optlvl_${optim_lvl}__"${cli_arg}".txt &
    echo "Compiling tests started..."
    PID2=$!

    wait $PID1
    RET=$?
    if [ "$RET" != "0" ] ; then SOMEONE_FAILLED=1; echo "Fail ($RET) in ${LOGS}/run_optlvl_${optim_lvl}__${cli_arg}.txt" ;  fi
    echo "Running tests ended!"

    wait $PID2
    RET=$?
    if [ "$RET" != "0" ] ; then SOMEONE_FAILLED=1; echo "Fail ($RET) in ${LOGS}/compile_optlvl_${optim_lvl}__${cli_arg}.txt"; fi

    echo "Compiling tests ended!"

    echo "END OF OPTIM LEVEL: ${optim_lvl}/${cli_arg}"
    echo ""
done

SINGLE_OPTIMS="rdvconnector poolci poolciv ports-index ports-reset transitions-update no-side-effect early-update"

for single_optim in $SINGLE_OPTIMS; do
    echo "Testing with only ${single_optim}"
    DEFAULT_BIPC_ARGS="--gencpp-enable-optim=${single_optim} ${cli_arg}" ${TESTS_SCRIPTS_ROOT}/runningTests.sh &> ${LOGS}/run_opt_${single_optim}__"${cli_arg}".txt &
    PID1=$!
    echo "Running tests started..."

    DEFAULT_BIPC_ARGS="--gencpp-enable-optim=${single_optim} ${cli_arg}" ${TESTS_SCRIPTS_ROOT}/compileOnlyTests.sh &> ${LOGS}/compile_opt_${single_optim}__"${cli_arg}".txt &
    PID2=$!
    echo "Compiling tests started..."

    wait $PID1
    RET=$?
    if [ "$RET" != "0" ] ; then SOMEONE_FAILLED=1; echo "Fail ($RET) in ${LOGS}/run_opt_${single_optim}__${cli_arg}.txt";  fi
    echo "Running tests ended!"

    wait $PID2
    RET=$?
    if [ "$RET" != "0" ] ; then SOMEONE_FAILLED=1; echo "Fail ($RET) in ${LOGS}/compile_opt_${single_optim}__${cli_arg}.txt"; fi
    echo "Compiling tests ended!"

    echo "End of testing with only ${single_optim}/${cli_arg}"
    echo ""
done

done
echo "error:"  $SOMEONE_FAILLED
exit $SOMEONE_FAILLED