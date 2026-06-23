#! /bin/bash
# file: examples/equality_test.sh
ENGINES_ROOT=$PWD/$(dirname $0)/../../../reference-engine

oneTimeSetUp() {
    . $(dirname $0)/./tests.inc
    oneTimeSetUp_MASTER
    COMPILE_ONLY_TESTS="$TESTS_ROOT_DIR/compile_only_tests"
    KIND=compile_only_tests
}

#
# THE TESTS STARTS BELOW
#

###
### STATIC TESTS (only check that they compile correctly)
###
test_atom_port_values() {
  TEST=atom_port_values
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'CT()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

test_tempcontrol() {
  TEST=tempcontrol
   compute_output_dir
  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'Top()'  "--gencpp-cc-I $COMPILE_ONLY_TESTS" && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

test_internal_port() {
  TEST=internal_port
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompound()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

test_periodic_tick() {
  TEST=periodic_tick
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompound()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $? 

}

test_priorities_atom() {
  TEST=priorities_atom
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompound()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

test_priorities_wildcard() {
  TEST=priorities_wildcard
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompound()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

test_hierarchy()
{
  TEST=hierarchy
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompound()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

test_modulo8()
{
  TEST=modulo8
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'Modulo8()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

test_const_data()
{
  TEST=const_data
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'CT()' && compile_and_link_with_engine "$TEST"
  assertEquals 0 $?
}

# priority_rules_atom_cycle.bip
test_priority_rules_atom_cycle() {
  TEST=priority_rules_atom_cycle
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompoundType()' && fail "$TEST compiled but should be rejected"
}

# priority_rules_atom_cycle2.bip
test_priority_rules_atom_cycle2() {
  TEST=priority_rules_atom_cycle2
   compute_output_dir

  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompoundType()' && fail "$TEST compiled but should be rejected"
}

# broadcast_reverted.bip
test_broadcast_reverted() {
  TEST=broadcast_reverted
  compute_output_dir
  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST"
}

# conflict_component_prio.bip
test_conflict_component_prio() {
  TEST=conflict_component_prio
  compute_output_dir
  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'Comp()' && compile_and_link_with_engine "$TEST"
}

# conflict_type_instance.bip
test_conflict_type_instance() {
  TEST=conflict_type_instance
  compute_output_dir
  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'Comp()' && compile_and_link_with_engine "$TEST"
}

# conflict_packages.bip
test_conflict_packages() {
  TEST=conflict_packages
  compute_output_dir
  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'Composite()' && compile_and_link_with_engine "$TEST"
}

# conflict_packages2.bip
test_conflict_packages2() {
  TEST=conflict_packages2
  compute_output_dir
  compile_to_cpp "$TEST" "$COMPILE_ONLY_TESTS" 'Composite()' && compile_and_link_with_engine "$TEST"
}

##
## shunit2 internal. Simply source the shunit2 file and "voilà".
##

# load shunit2
. $ENGINES_ROOT/tests/lib/shunit2/shunit2
