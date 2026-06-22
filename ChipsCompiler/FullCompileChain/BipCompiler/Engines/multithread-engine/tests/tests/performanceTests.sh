#! /bin/bash
# file: examples/equality_test.sh

ENGINES_ROOT=$PWD/$(dirname $0)/../../../reference-engine

oneTimeSetUp() {
    . $(dirname $0)/./tests.inc
    oneTimeSetUp_MASTER
    RUNNING_TESTS="$TESTS_ROOT_DIR/running_tests"
}
#
# THE TESTS STARTS BELOW
#

###
### RUNNING TESTS : check compilation and run them.
###

# broadcast_browser.bip
test_broadcast_browser() {
 TEST=broadcast_browser

  compile_to_cpp "$TEST" "$RUNNING_TESTS" 'MyCompoundType()' && compile_and_link_with_engine "$TEST" || fail "Compiler returned an error"

  valgrind --tool=callgrind $OUTPUT_DIR/build/system --silent
}


##
## shunit2 internal. Simply source the shunit2 file and "voilà".
##

# load shunit2
. $ENGINES_ROOT/tests/lib/shunit2/shunit2
