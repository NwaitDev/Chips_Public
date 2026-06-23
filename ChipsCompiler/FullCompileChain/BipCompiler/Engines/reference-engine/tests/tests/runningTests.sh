#! /bin/bash
# file: examples/equality_test.sh

# ALL variables must be set before use. Else, script will stop.
set -u

ENGINES_ROOT=$PWD/$(dirname $0)/../../../reference-engine

oneTimeSetUp() {
    . $(dirname $0)/./tests.inc
    oneTimeSetUp_MASTER
    RUNNING_TESTS="$TESTS_ROOT_DIR/running_tests"
    KIND=running_tests
}
#
# THE TESTS STARTS BELOW
#

###
### RUNNING TESTS : check compilation and run them.
###

# external.bip
tests_exernal() {
  TEST=external
  
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'Compound()' "--gencpp-cc-I $RUNNING_TESTS/external --gencpp-cc-extra-opt -pthread --gencpp-ld-extra-opt -pthread" && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  declare -i success
  declare -i sum

  let "success=0"
  let "sum=0"

  for index in {1..100}
  do
    let "sum=$sum+$index"
    let "success+=$(grep "1.s1=$sum;" -c $OUTPUT_DIR/trace)"
    let "success+=$(grep "2.s1=$sum;" -c $OUTPUT_DIR/trace)"
    let "success+=$(grep "1.s2=$sum;" -c $OUTPUT_DIR/trace)"
    let "success+=$(grep "2.s2=$sum;" -c $OUTPUT_DIR/trace)"
  done

  let "success+=$(grep "1.s3=42;" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "2.s3=42;" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "1.s4=42;" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "2.s4=42;" -c $OUTPUT_DIR/trace)"

  let "success+=$(grep "sync 1 and 2" -c $OUTPUT_DIR/trace)"
  
  let "success+=$(grep "state #405:.*deadlock" -c $OUTPUT_DIR/trace)"

  [ $success -eq "406" ]

  assertTrue "$0 test failed" "$?"
}

# external_error.bip
tests_exernal_error() {
  TEST=external_error
  
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'Compound()' "--gencpp-cc-I $RUNNING_TESTS/external --gencpp-cc-extra-opt -pthread --gencpp-ld-extra-opt -pthread" && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace
  assertEquals 6 $?

  declare -i success
  declare -i sum

  let "success=0"
  let "sum=0"

  let "success+=$(grep "1.s3=42;" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "2.s3=42;" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "1.s4=42;" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "2.s4=42;" -c $OUTPUT_DIR/trace)"

  let "success+=$(grep "sync 1 and 2" -c $OUTPUT_DIR/trace)"
  
  let "success+=$(grep "state #405:.*deadlock" -c $OUTPUT_DIR/trace)"

  [ $success -eq "0" ]

  assertTrue "$0 test failed" "$?"
}


# double_compound.bip
tests_double_compound() {
  TEST=double_compound

  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'System()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  INTER_NB=$(grep '1 interaction' -c $OUTPUT_DIR/trace)

  [ "$INTER_NB" -eq "1001" ] && \
  grep -q "state #1001: deadlock!" $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# and_expressions.bip
test_and_expressions() {
  TEST=and_expressions
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'AndExpressions()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  INTER_NB=$(grep '1 interaction' -c $OUTPUT_DIR/trace)

  [ "$INTER_NB" -eq "15" ] && \
  grep -q ": state #15: deadlock!" $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# or_expressions.bip
test_or_expressions() {
  TEST=or_expressions
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'OrExpressions()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  INTER_NB=$(grep '1 interaction' -c $OUTPUT_DIR/trace)
  INTER_NB=$(grep 'choose.*single.*sync' -c $OUTPUT_DIR/trace)

  [ "$INTER_NB" -eq "4" ] && \
  grep -q ": state #4: deadlock!" $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# petri_net.bip
test_petri_net() {
  TEST=petri_net
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #2: 2 interactions' $OUTPUT_DIR/trace ; STATE2_NB1=$?
  grep -q 'state #2: 1 interaction'  $OUTPUT_DIR/trace ; STATE2_NB2=$?
  
  grep -q 'start1:.*petriNet.start1' $OUTPUT_DIR/trace && \
  grep -q 'start2:.*petriNet.start2' $OUTPUT_DIR/trace && \
  grep -q 'res1:.*petriNet.res1' $OUTPUT_DIR/trace && \
  grep -q 'res2:.*petriNet.res2' $OUTPUT_DIR/trace && \
  grep -q 'sync:.*petriNet.sync' $OUTPUT_DIR/trace && \
  grep -q 'state #0: 2 interactions' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 2 interactions' $OUTPUT_DIR/trace && \
  [ $STATE2_NB1 -eq 0 -o $STATE2_NB2 -eq 0 ] && \
  grep -q 'state #3: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #4: 1 interaction' $OUTPUT_DIR/trace && \
  (tail -n 50 $OUTPUT_DIR/trace | grep -q 'state #5: deadlock')

  assertTrue "$0 test failed" "$?"
}


# petri_net_non_safe.bip
test_petri_net_non_safe() {
  TEST=petri_net_non_safe
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 2 $? # returns error code 2: non 1-safe Petri net
}


# petri_net_non_deterministic.bip
test_petri_net_non_deterministic() {
  TEST=petri_net_non_deterministic
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 1 $? # returns error code 1: non deterministic Petri net
}


# petri_net_non_deterministic2.bip
test_petri_net_non_deterministic2() {
  TEST=petri_net_non_deterministic2
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 1 $? # returns error code 1: non deterministic Petri net
}


# petri_net_non_deterministic3.bip
test_petri_net_non_deterministic3() {
  TEST=petri_net_non_deterministic3
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 1 $? # returns error code 1: non deterministic Petri net
}


# petri_net_deterministic.bip
test_petri_net_deterministic() {
  TEST=petri_net_deterministic
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system  > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'choose.*singleP' $OUTPUT_DIR/trace && \
  grep -q 'choose.*singleQ' $OUTPUT_DIR/trace && \
  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 1 interaction' $OUTPUT_DIR/trace && \
  (tail -n 10 $OUTPUT_DIR/trace | grep -q 'state #2: deadlock')

  assertTrue "$0 test failed" "$?"
}


# simple10counter.bip
test_simple10counter() {
  TEST=simple10counter
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CT()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  LAST_EXEC_LINE=$($OUTPUT_DIR/build/system |tail -n 1)

  [ ${PIPESTATUS[0]} -eq "0" ] || fail "Executable returned an error"

  assertEquals "[BIP ENGINE]: state #0: deadlock!" "$LAST_EXEC_LINE"
}


# atom_internal_transitions.bip
test_atom_internal_transitions() {
  TEST=atom_internal_transitions
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CT()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  NBINCR=$(grep -c -m6 'choose.*single:.*c.incr()' $OUTPUT_DIR/trace)
  
  [ $NBINCR -eq "5" ] && \
  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #2: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #3: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #4: 1 interaction' $OUTPUT_DIR/trace && \
  (tail -n 10 $OUTPUT_DIR/trace | grep -q 'state #5: deadlock')

  assertTrue "$0 test failed" "$?"
}


# internal_export_compound.bip
test_internal_export_compound() {
  TEST=internal_export_compound
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'BIG_CT()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 1 internal port' $OUTPUT_DIR/trace && \
  grep -q 'state #2: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #3: deadlock' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# multi_export_atom.bip
test_multi_export_atom() {
 TEST=multi_export_atom
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'mySingleton:.*myAtom.xport(d=1;)' $OUTPUT_DIR/trace && \
  grep -q 'mySingleton:.*myAtom.xport(d=2;)' $OUTPUT_DIR/trace && \
  grep -q 'mySingleton:.*myAtom.xport(d=3;)' $OUTPUT_DIR/trace && \
  grep -q 'state #0: 3 interactions' $OUTPUT_DIR/trace && \
  (tail -n 10 $OUTPUT_DIR/trace | grep -q 'state #1: deadlock')
  assertTrue "$0 test failed" "$?"
}


# multi_export_compound.bip
test_multi_export_compound() {
 TEST=multi_export_compound
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'Top()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"
  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'mySingleton:.*C.xport(d=1;)' $OUTPUT_DIR/trace && \
  grep -q 'mySingleton:.*C.xport(d=2;)' $OUTPUT_DIR/trace && \
  grep -q 'mySingleton:.*C.xport(d=3;)' $OUTPUT_DIR/trace && \
  grep -q 'state #0: 3 interactions' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 2 interactions' $OUTPUT_DIR/trace && \
  grep -q 'state #2: 1 interaction' $OUTPUT_DIR/trace && \
  tail $OUTPUT_DIR/trace | grep -q 'state #3: deadlock'

  assertTrue "$0 test failed" "$?"
}


# broadcast.bip
test_broadcast() {
 TEST=broadcast
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST"  || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  (grep -q 'myBroadcast:.*myAtom1.p() .*myAtom3.p()' $OUTPUT_DIR/trace || \
   grep -q 'myBroadcast:.*myAtom3.p() .*myAtom1.p()' $OUTPUT_DIR/trace) && \
  (grep -q 'myBroadcast:.*myAtom1.p() .*myAtom2.p()' $OUTPUT_DIR/trace || \
   grep -q 'myBroadcast:.*myAtom2.p() .*myAtom1.p()' $OUTPUT_DIR/trace) && \
  grep -q 'state #0: 2 interactions' $OUTPUT_DIR/trace && \
  (tail -n 10  $OUTPUT_DIR/trace | grep -q 'state #1: deadlock') && \
  (!  grep -q 'myAtom2.p() .*myAtom3.p()' $OUTPUT_DIR/trace) && \
  (! grep -q 'myAtom3.p() .*myAtom2.p()' $OUTPUT_DIR/trace)

  assertTrue "$0 test failed" "$?"
}


# broadcast_reverted.bip
test_broadcast_reverted() {
 TEST=broadcast_reverted
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST"  || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  (grep -q 'myBroadcast:.*myAtom1.p() .*myAtom3.p()' $OUTPUT_DIR/trace || \
   grep -q 'myBroadcast:.*myAtom3.p() .*myAtom1.p()' $OUTPUT_DIR/trace) && \
  (grep -q 'myBroadcast:.*myAtom3.p() .*myAtom2.p()' $OUTPUT_DIR/trace || \
   grep -q 'myBroadcast:.*myAtom2.p() .*myAtom3.p()' $OUTPUT_DIR/trace) && \
  grep -q 'state #0: 2 interactions' $OUTPUT_DIR/trace && \
  (tail -n 10  $OUTPUT_DIR/trace | grep -q 'state #1: deadlock') && \
  (!  grep -q 'myAtom1.p() .*myAtom2.p()' $OUTPUT_DIR/trace) && \
  (! grep -q 'myAtom2.p() .*myAtom1.p()' $OUTPUT_DIR/trace)

  assertTrue "$0 test failed" "$?"
}


# broadcast_maximal.bip
test_broadcast_maximal() {
  TEST=broadcast_maximal
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  NBR1=$(grep -m13 -e 'myBroadcast:.*myAtom1.p' -c $OUTPUT_DIR/trace)
  NBR2=$(grep -m13 -e 'myBroadcast:.*myAtom2.p' -c $OUTPUT_DIR/trace)
  NBR3=$(grep -m13 -e 'myBroadcast:.*myAtom3.p' -c $OUTPUT_DIR/trace)
  NBR4=$(grep -m13 -e 'myBroadcast:.*myAtom4.p' -c $OUTPUT_DIR/trace)
  NBR5=$(grep -m13 -e 'myBroadcast:.*myAtom5.p' -c $OUTPUT_DIR/trace)
  NBR6=$(grep -m13 -e 'myBroadcast:.*myAtom6.p' -c $OUTPUT_DIR/trace)


  grep -q 'state #0: 20 interactions' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #2: deadlock' $OUTPUT_DIR/trace && \
  [ $NBR1 -eq '11' -o $NBR1 -eq '12' ] && \
  [ $NBR2 -eq '11' -o $NBR2 -eq '12' ] && \
  [ $NBR3 -eq '11' -o $NBR3 -eq '12' ] && \
  [ $NBR4 -eq '11' -o $NBR4 -eq '12' ] && \
  [ $NBR5 -eq '11' -o $NBR5 -eq '12' ] && \
  [ $NBR6 -eq '11' -o $NBR6 -eq '12' ]

  assertTrue "$0 test failed" "$?"
}

# broadcast_up.bip
test_broadcast_up() {
  TEST=broadcast_up
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
 
  grep -q 'single:.*brd.xport(d=54;)' $OUTPUT_DIR/trace && \
  grep -q 'single:.*brd.xport(d=115;)' $OUTPUT_DIR/trace && \
  grep -q 'state #0: 2 interactions' $OUTPUT_DIR/trace && \
  (tail -n 10 $OUTPUT_DIR/trace | grep -q 'state #1: deadlock')

  assertTrue "$0 test failed" "$?"
}


# broadcast_up_down.bip
test_broadcast_up_down() {
  TEST=broadcast_up_down
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'div:.*xport(d=70;)'     $OUTPUT_DIR/trace && \
  grep -q 'div:.*xport(d=54;)'     $OUTPUT_DIR/trace && \
  ((grep -q 'choose.*xport(d=70;'  $OUTPUT_DIR/trace && grep -q 'choose.*disp:.*myAtom1.q(d=38;' $OUTPUT_DIR/trace) || \
   (grep -q 'choose.*xport(d=54;'  $OUTPUT_DIR/trace && grep -q 'choose.*disp:.*myAtom1.q(d=28;' $OUTPUT_DIR/trace)) && \
  grep -q 'state #0: 2 interactions' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 1 interaction'  $OUTPUT_DIR/trace && \
  (tail -n 10 $OUTPUT_DIR/trace | grep -q 'state #2: deadlock')

  assertTrue "$0 test failed" "$?"
}


# rendezvous_down.bip
test_rendezvous_down() {
 TEST=rendezvous_down
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  (grep -q 'send:.*sender.p(d=-32;) .*receiver.p(d=0;)' $OUTPUT_DIR/trace  || \
   grep -q 'send:.*receiver.p(d=0;) .*sender.p(d=-32;)' $OUTPUT_DIR/trace    ) && \
  (grep -q 'send:.*sender.p(d=99;) .*receiver.p(d=-32;)' $OUTPUT_DIR/trace || \
   grep -q 'send:.*receiver.p(d=-32;) .*sender.p(d=99;)' $OUTPUT_DIR/trace ) &&\
  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #2: deadlock' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# priority_rules.bip
test_priority_rules() {
  TEST=priority_rules
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  (grep -q 'brd1:.*myAtom1.p() .*myAtom3.p()' $OUTPUT_DIR/trace || \
   grep -q 'brd1:.*myAtom3.p() .*myAtom1.p()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom2.p()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom1.q()' $OUTPUT_DIR/trace ) && \
  ( ! grep -q 'myAtom2.q()' $OUTPUT_DIR/trace ) && \
  ( ! grep -q 'myAtom3.q()' $OUTPUT_DIR/trace ) && \
   grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
   grep -q 'state #1: deadlock' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# priority_rules_wildcard.bip
test_priority_rules_wildcard() {
  TEST=priority_rules_wildcard
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  (grep -q 'brd1:.*myAtom1.p() .*myAtom3.p()' $OUTPUT_DIR/trace || \
   grep -q 'brd1:.*myAtom3.p() .*myAtom1.p()' $OUTPUT_DIR/trace ) && \
  ( ! grep -q 'myAtom2.p()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom1.q()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom2.q()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom3.q()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom1.r()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom2.r()' $OUTPUT_DIR/trace) && \
  ( ! grep -q 'myAtom3.r()' $OUTPUT_DIR/trace) && \
  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  (tail -n10 $OUTPUT_DIR/trace | grep -q 'state #1: deadlock')

  assertTrue "$0 test failed" "$?"
}


# priority_rules_cycle.bip
test_priority_rules_cycle() {
  TEST=priority_rules_cycle
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 3 $? # returns error code 3: cycle found in priorities of a compound
}


# priority_rules_cycle2.bip
test_priority_rules_cycle2() {
  TEST=priority_rules_cycle2
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && fail "$TEST compiled but should be rejected"
}

# priority_rules_cycle3.bip
test_priority_rules_cycle3() {
  TEST=priority_rules_cycle3
  compute_output_dir

  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 3 $? # returns error code 3: cycle found in priorities of a compound
}


# priority_rules_cycle_hierarchy.bip
test_priority_rules_cycle_hierarchy() {
  TEST=priority_rules_cycle_hierarchy
  compute_output_dir

  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CTH()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 3 $? # returns error code 3: cycle found in priorities of a compound
}


# priority_rules_no_cycle.bip
test_priority_rules_no_cycle() {
  TEST=priority_rules_no_cycle
  compute_output_dir

  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'rdv:.*A1.p.*A2.p.*A3.p' $OUTPUT_DIR/trace
}


# priority_rules_no_cycle2.bip
test_priority_rules_no_cycle2() {
  TEST=priority_rules_no_cycle2
  compute_output_dir

  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'rdv2:.*rdv1.r.*A3.p' $OUTPUT_DIR/trace
}


# priority_rules_atom.bip
test_priority_rules_atom() {
  TEST=priority_rules_atom
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: deadlock' $OUTPUT_DIR/trace && \
  grep -q 'single1:.*myAtom.p' $OUTPUT_DIR/trace && \
  ( ! grep -q 'single2:.*myAtom.q' $OUTPUT_DIR/trace )

  assertTrue "$0 test failed" "$?"
}


# priority_rules_atom_internal.bip
test_priority_rules_atom_internal() {
  TEST=priority_rules_atom_internal
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'myAtom.p' $OUTPUT_DIR/trace && \
  grep -q 'myAtom.r' $OUTPUT_DIR/trace && \
  (grep -q 'choose .*myAtom.p' $OUTPUT_DIR/trace || grep -q 'choose .*myAtom.r' $OUTPUT_DIR/trace)  && \
  grep -q 'state #0: 2 internal ports' $OUTPUT_DIR/trace && \
  grep -q 'state #1: deadlock' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# priority_rules_atom_export.bip
test_priority_rules_atom_export() {
  TEST=priority_rules_atom_export
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  NB=$(grep -c -m 4 'single:.*myAtom.exp()' $OUTPUT_DIR/trace)
  NBchoose=$(grep -c -m 2 'choose.*single:.*myAtom.exp()' $OUTPUT_DIR/trace)

  [ $NB -eq "3" ] && \
  [ $NBchoose -eq "1" ] && \
  grep -q 'state #0: 2 interactions' $OUTPUT_DIR/trace && \
  grep -q 'state #1: deadlock' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# priority_rules_atom_closure.bip
test_priority_rules_atom_closure() {
  TEST=priority_rules_atom_closure
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: deadlock' $OUTPUT_DIR/trace && \
  grep -q 'single5:.*myAtom.t' $OUTPUT_DIR/trace && \
  ( ! grep -q 'single1:.*myAtom.p' $OUTPUT_DIR/trace )

  assertTrue "$0 test failed" "$?"
}


# priority_rules_atom_wildcard.bip
test_priority_rules_atom_wildcard() {
  TEST=priority_rules_atom_wildcard
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'single1:.*myAtom.p()' $OUTPUT_DIR/trace && \
  ( ! grep -q 'single1:.*myAtom.q()' $OUTPUT_DIR/trace ) && \
  ( ! grep -q 'single1:.*myAtom.r()' $OUTPUT_DIR/trace ) && \
  grep -q 'state #0: 1 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: deadlock' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# priority_rules_atom_cycle3.bip
test_priority_rules_atom_cycle3() {
  TEST=priority_rules_atom_cycle3
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --silent
  assertEquals 4 $? # returns error code 4: cycle in atom priorities
}


# priority_rules_atom_cycle4.bip
test_priority_rules_atom_cycle4() {
  TEST=priority_rules_atom_cycle4
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0: 2 interaction' $OUTPUT_DIR/trace && \
  grep -q 'state #1: deadlock' $OUTPUT_DIR/trace && \
  ( grep -q 'single1:.*myAtom.p' $OUTPUT_DIR/trace || grep -q 'single5:.*myAtom.t' $OUTPUT_DIR/trace )

  assertTrue "$0 test failed" "$?"
}


# broadcast_browser.bip
test_broadcast_browser() {
 TEST=broadcast_browser
   compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  NBsync=$(grep -m 63 -e 'choose.*sync' -c $OUTPUT_DIR/trace)
  NBstop=$(grep -m2 -e 'choose.*stop' -c $OUTPUT_DIR/trace)

  NBsyncbit1=$(grep -m 32 -e 'choose.*sync.*bit1' -c $OUTPUT_DIR/trace)
  NBsyncbit2=$(grep -m 32 -e 'choose.*sync.*bit2' -c $OUTPUT_DIR/trace)
  NBsyncbit3=$(grep -m 32 -e 'choose.*sync.*bit3' -c $OUTPUT_DIR/trace)
  NBsyncbit4=$(grep -m 32 -e 'choose.*sync.*bit4' -c $OUTPUT_DIR/trace)
  NBsyncbit5=$(grep -m 32 -e 'choose.*sync.*bit5' -c $OUTPUT_DIR/trace)
  NBsyncbit6=$(grep -m 32 -e 'choose.*sync.*bit6' -c $OUTPUT_DIR/trace)

  NBbit1=$(grep -m 65 'choose.*bit1' -c $OUTPUT_DIR/trace)
  NBbit2=$(grep -m 68 'choose.*bit2' -c $OUTPUT_DIR/trace)
  NBbit3=$(grep -m 74 'choose.*bit3' -c $OUTPUT_DIR/trace)
  NBbit4=$(grep -m 86 'choose.*bit4' -c $OUTPUT_DIR/trace)
  NBbit5=$(grep -m 110 'choose.*bit5' -c $OUTPUT_DIR/trace)
  NBbit6=$(grep -m 127 'choose.*bit6' -c $OUTPUT_DIR/trace)
  
  # broadcast between 6 ports with all ports triggers => nbr of interactions = 63
  [ "$NBsync" -eq "62" ] && \
  # i.e. 62 interactions through sync, one through stop to deadlock the system
  [ "$NBstop" -eq "1" ] && \
  # each atom is part of half of the interactions of sync+stop
  [ "$NBsyncbit1" -eq "31" ] && \
  [ "$NBsyncbit2" -eq "31" ] && \
  [ "$NBsyncbit3" -eq "31" ] && \
  [ "$NBsyncbit4" -eq "31" ] && \
  [ "$NBsyncbit5" -eq "31" ] && \
  [ "$NBsyncbit6" -eq "31" ] && \
  # 31 inter in sync, 1 in stop, 63 flips, 1  carry
  [ "$NBbit1" -eq "64" ] && \
  # 31 inter in sync, 1 in stop, 31 flips, 4  carry
  [ "$NBbit2" -eq "67" ] && \
  # 31 inter in sync, 1 in stop, 31 flips, 10 carry
  [ "$NBbit3" -eq "73" ] && \
  # 31 inter in sync, 1 in stop, 31 flips, 22 carry
  [ "$NBbit4" -eq "85" ] && \
  # 31 inter in sync, 1 in stop, 31 flips, 46 carry
  [ "$NBbit5" -eq "109" ] && \
  # 31 inter in sync, 1 in stop, 63 flips, 31 carry
  [ "$NBbit6" -eq "126" ] && \
  (tail -n 10 $OUTPUT_DIR/trace | grep -q 'state #183: deadlock' )

  assertTrue "$0 test failed" "$?"
}


# guarded_transitions.bip
test_guarded_transitions() {
  TEST=guarded_transitions
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  NBR1=$(grep -m 12 -c 'choose.*myAtom1.p' $OUTPUT_DIR/trace)
  NBR2=$(grep -m 22 -c 'choose.*myAtom2.p' $OUTPUT_DIR/trace)

  [ "$NBR1" -eq "11" ] && \
  [ "$NBR2" -eq "21" ]

  assertTrue "$0 test failed" "$?"
}


# maximal_progress.bip
test_maximal_progress() {
  TEST=maximal_progress
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'Top()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0: 3 interactions' $OUTPUT_DIR/trace && \
  grep -q 'high:.*low.xport(x=-12;)' $OUTPUT_DIR/trace && \
  grep -q 'high:.*low.xport(x=-5;)'  $OUTPUT_DIR/trace && \
  grep -q 'single:.*myCompound.p(x=-5;)' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# maximal_progress_hierarchy.bip
test_maximal_progress_hierarchy() {
  TEST=maximal_progress_hierarchy
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'System()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #0:.*1 interaction' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# multi_export_compound2.bip
test_multi_export_compound2() {
  TEST=multi_export_compound2
    compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'Top()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"

  grep -q 'state #1: 3 interactions' $OUTPUT_DIR/trace ; STATE1_3INTER=$?
  grep -q 'state #1: 4 interactions' $OUTPUT_DIR/trace ; STATE1_4INTER=$?
  grep -q 'state #2: 1 interaction'  $OUTPUT_DIR/trace ; STATE2_1INTER=$?
  grep -q 'state #2: 2 interactions' $OUTPUT_DIR/trace ; STATE2_2INTER=$?

  grep -q 'state #0: 5 interactions' $OUTPUT_DIR/trace && \
  [ $STATE1_3INTER -eq 0 -o $STATE1_4INTER -eq 0 ] && \
  [ $STATE2_1INTER -eq 0 -o $STATE2_2INTER -eq 0 ] && \
  [ $STATE1_4INTER -eq 1 -o $STATE2_1INTER -eq 1 ]

  assertTrue "$0 test failed" "$?"
}


# doublecounter.bip
test_doublecounter() {
  TEST=doublecounter
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CT()' "--gencpp-enable-marshalling" && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --explore > $OUTPUT_DIR/trace || fail "Executable returned an error"

  declare -i success
  let "success=0"

  let "success+=$(grep "10201 reachable states" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "1 deadlock" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "0 error" -c $OUTPUT_DIR/trace)"

  [ $success -eq "3" ]

  assertTrue "$0 test failed" "$?"
}


# doublecounter2.bip
test_doublecounter2() {
  TEST=doublecounter2
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CT()' "--gencpp-enable-marshalling" && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --explore > $OUTPUT_DIR/trace || fail "Executable returned an error"

  declare -i success
  let "success=0"

  let "success+=$(grep "5251 reachable states" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "1 deadlock" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "0 error" -c $OUTPUT_DIR/trace)"

  [ $success -eq "3" ]

  assertTrue "$0 test failed" "$?"
}


# cyclic.bip
test_cyclic() {
  TEST=cyclic
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CT()' "--gencpp-enable-marshalling" && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --explore > $OUTPUT_DIR/trace || fail "Executable returned an error"

  declare -i success
  let "success=0"

  let "success+=$(grep "40401 reachable states" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "0 deadlock" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "0 error" -c $OUTPUT_DIR/trace)"

  [ $success -eq "3" ]

  assertTrue "$0 test failed" "$?"
}


# dining_philo.bip
test_dining_philo() {
  TEST=dining_philo
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'DiningPhilo()' "--gencpp-enable-marshalling" && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  ulimit -s 40000
  $OUTPUT_DIR/build/system --explore > $OUTPUT_DIR/trace || fail "Executable returned an error"

  declare -i success
  let "success=0"

  let "success+=$(grep "27303 reachable states" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "2 deadlock" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "0 error" -c $OUTPUT_DIR/trace)"

  [ $success -eq "3" ]

  assertTrue "$0 test failed" "$?"
}


# dining_philo_flat.bip
test_dining_philo_flat() {
  TEST=dining_philo_flat
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'DiningPhilo()' "--gencpp-enable-marshalling" && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --explore > $OUTPUT_DIR/trace || fail "Executable returned an error"

  declare -i success
  let "success=0"

  let "success+=$(grep "117485 reachable states" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "2 deadlock" -c $OUTPUT_DIR/trace)"
  let "success+=$(grep "0 error" -c $OUTPUT_DIR/trace)"

  [ $success -eq "3" ]

  assertTrue "$0 test failed" "$?"
}


# const_data.bip
test_const_data() {
  TEST=const_data
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'Top()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q ": state #25: 2 internal ports:" $OUTPUT_DIR/trace && \
  grep -q ": state #27: deadlock!" $OUTPUT_DIR/trace
  assertTrue "$0 test failed" "$?"
}

# hierarchical
test_hierarchical() {
  TEST=hierarchical
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q ": state #21: deadlock!" $OUTPUT_DIR/trace
  assertTrue "$0 test failed" "$?"
}

# hierarchical filter
test_hierarchical_filter() {
  TEST=hierarchical
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' '-f ujf.verimag.bip.middleend.flattening.FlatteningFilter' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q ": state #21: deadlock!" $OUTPUT_DIR/trace
  assertTrue "$0 test failed" "$?"
}

# nested
test_nested() {
  TEST=nested
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q ": state #21: deadlock!" $OUTPUT_DIR/trace
  assertTrue "$0 test failed" "$?"
}

# nested2
test_nested2() {
  TEST=nested2
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q "state #0: 3 interactions" $OUTPUT_DIR/trace && \
  grep -q "state #1: 2 interactions" $OUTPUT_DIR/trace && \
  grep -q "state #2: 1 interaction" $OUTPUT_DIR/trace && \
  grep -q "state #3: deadlock"       $OUTPUT_DIR/trace && \
  grep -q "choose.*P.*Q"             $OUTPUT_DIR/trace && \
  grep -q "choose.*R.*S"             $OUTPUT_DIR/trace && \
  grep -q "choose.*T.*U"             $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}

# nested3
test_nested3() {
  TEST=nested3
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --disable-maximal-progress > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q "state #0: 7 interactions" $OUTPUT_DIR/trace && \
  grep -q "state #1: deadlock"       $OUTPUT_DIR/trace && \
  grep -q ".*P.*Q.*R.*S.*T.*U" $OUTPUT_DIR/trace && \
  grep -q ".*P.*Q.*R.*T.*U"    $OUTPUT_DIR/trace && \
  grep -q ".*P.*Q.*S.*T.*U"    $OUTPUT_DIR/trace && \
  grep -q ".*Q.*R.*S.*T.*U"    $OUTPUT_DIR/trace && \
  grep -q ".*Q.*R.*T.*U"       $OUTPUT_DIR/trace && \
  grep -q ".*Q.*S.*T.*U"       $OUTPUT_DIR/trace && \
  grep -q ".*T.*U"             $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}

# hierarchical with priority
test_hierarchical_priority() {
  TEST=hierarch_priority
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q ": state #21: deadlock!" $OUTPUT_DIR/trace
  assertTrue "$0 test failed" "$?"
}

# hierarchical with priority and filter
test_hierarchical_priority_filter() {
  TEST=hierarch_priority
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' '-f ujf.verimag.bip.middleend.flattening.FlatteningFilter' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace || fail "Executable returned an error"
  grep -q ": state #21: deadlock!" $OUTPUT_DIR/trace
  assertTrue "$0 test failed" "$?"
}

# demosaicing9.bip
test_demosaicing9() {
  TEST=demosaicing9

  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'Demosaicer()' "--gencpp-no-serial --gencpp-cc-I $RUNNING_TESTS/demosaicing" && compile_and_link_with_engine

  $OUTPUT_DIR/build/system --silent > $OUTPUT_DIR/trace

  /bin/cp -f $RUNNING_TESTS/demosaicing/reference.gz $OUTPUT_DIR/
  gunzip -f $OUTPUT_DIR/reference.gz

  diff $OUTPUT_DIR/reference $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}

# priority_rules_guard_external
test_priority_rules_guard_external() {
  TEST=priority_rules_guard_external
  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'EvilPriorityRules()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system --limit 1000000 > $OUTPUT_DIR/trace || fail "Executable returned an error"

  more $OUTPUT_DIR/trace | grep "choose" | awk -F"choose" '{print $2}' | awk -F": " 'begin{bit=0}  $2=="switch.flip()" {if (bit==0) bit=1; else bit=0; } $2=="A.p() B.p()" {if (bit==1) print "ERROR"; else print "OK"; } $2=="C.p() D.p()" {if (bit==0) print "ERROR"; else print "OK"; }' | grep -q "ERROR"
  assertFalse "$0 test failed" "$?"
}


# invariants
tests_invariants() {
  TEST=invariants

  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CT()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace
  assertEquals 5 $? # error code for violation of invariants

  grep -q 'state #202' $OUTPUT_DIR/trace && \
  grep -q 'ERROR.*invariant.*totalUse2' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}


# invariants2
tests_invariants2() {
  TEST=invariants2

  compute_output_dir
  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'CT()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  $OUTPUT_DIR/build/system > $OUTPUT_DIR/trace
  assertEquals 5 $? # error code for violation of invariants

  grep -q 'state #200' $OUTPUT_DIR/trace && \
  grep -q 'ERROR.*invariant.*use12' $OUTPUT_DIR/trace

  assertTrue "$0 test failed" "$?"
}

##
## shunit2 internal. Simply source the shunit2 file and "voilà".
##

# load shunit2
. $ENGINES_ROOT/tests/lib/shunit2/shunit2
