#!/bin/bash

unset INFILE
unset TESTS_ROOT
LOGDIR="$PWD"
C_COMPILE=0
C_COMPILE_GUESS=0
USE_RBIPC=0

function help {
    echo 'Batch compiler
Usage:
  -t <root dir>   Specify a root directory for the bip files to 
                  compile. The script will search recursively for 
                  bip files (takes precedence over -f)
  -f <list file>  Specify a file containing a list of bip file
                  (one path per line)
  -b <bip2 home>  Override the value of BIP2_HOME
  -l <dir>        Specify the output directory for all logs
  -c              Also try to compile generated code (if any).
  -r              Use rbipc to resolve and compile dependencies.
  -g              Guess when it is needed to also compile the generated code.
'
}

while getopts  "rl:ht:f:b:cg" flag
do
  case "$flag" in
      t) TESTS_ROOT="$OPTARG";;
      f) INFILE="$OPTARG";;
      b) BIP2_HOME=$OPTARG;;
      c) C_COMPILE=1;;
      l) LOGDIR=$OPTARG;;
      g) C_COMPILE_GUESS=1;;
      r) USE_RBIPC=1;;
      h) help; exit 0;;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done

# we need at least a file with the source files or a root directory
if [ "$INFILE" == "" -a "$TESTS_ROOT" == "" ]; then
    echo "missing input file (-f <file>) or tests root (-t <tests root>)"
    help
    exit 255
fi

# trick to get the absolute path
if [ -d "$TESTS_ROOT" ]; then
    TESTS_ROOT=$(cd $TESTS_ROOT && pwd)
elif [ "$TESTS_ROOT" != "" ]; then
    echo "Tests root $TESTS_ROOT does not exist"
    help;
    exit 255
fi

if [ -d "$BIP2_HOME" ]; then
    BIP2_HOME=$(cd $BIP2_HOME && pwd)
elif [ "$BIP2_HOME" == "" ]; then
    echo "Missing BIP2 home. Either set BIP2_HOME or use -b <bip2 home>"
    help
    exit 255
else
    echo "BIP distribution directory $BIP2_HOME does not exist"
fi
export BIP2_HOME

if [ -d "$LOGDIR" ]; then
    LOGDIR=$(cd $LOGDIR && pwd)
else
    echo "Logdir $LOGDIR does not exist"
    help
    exit 255
fi

if [ "$USE_RBIPC" == "1" ]; then
    # rbipc needs 'bipc' command in the path
    export PATH=$BIP2_HOME/bin:$PATH
    which bipc
    if [ "$?" != "0" ]; then
	echo "Can't find bipc in $BIP2_HOME/bin"
	echo "PATH:$PATH"
	exit 255
    fi
fi

# if we have a test root, build a file with all source file
# we can find
if [ "$TESTS_ROOT" != "" ]; then
    INFILE=$(mktemp)
    find $TESTS_ROOT -name "*.bip" > $INFILE
fi

# get an absolute path, whatever the BIP2_HOME contains
BIPC=$(cd $BIP2_HOME && pwd)/bin/bipc
if [ ! -x $BIPC ]; then
    echo "Could not find 'bipc' in the distribution located in $BIP2_HOME"
    help
    exit 255
fi

RESULT_FILE="$LOGDIR/results"

# SUCCESS_FILE="success.log"
# FAILED_FILE="failed.log"
# SKIPPED_FILE="skipped.log"


rm -f $RESULT_FILE
touch $RESULT_FILE
echo "# $HOSTNAME" >> $RESULT_FILE
echo "#" $(uname -a) >> $RESULT_FILE
echo "#" $(date) >> $RESULT_FILE

echo "#" $($BIPC -v) >> $RESULT_FILE
if [ "$C_COMPILE" == "1" ]; then
    echo "#" $(g++ --version) >> $RESULT_FILE
fi

echo '
# BIP2CPP return codes:
# 0 : compiles as expected
# 2 : does not compile as expected
# 1 : compiles but should not
# 3 : does not compile but should

# CPP return codes:
# 0 : g++ does not fail
# 1 : g++ fails
# 3 : g++ not tested, previous step failed
' >> $RESULT_FILE


echo "# TESTS RESULTS BELOW" >> $RESULT_FILE

while read file; do

    TEST_NAME=$file
    LOGFILE="$LOGDIR/$(dirname $file|sed -e 's@/@_@g' -e 's@^\.@R@')_$(basename $file .bip).log"
    
    TESTS_RESULTS_VAR=""

    rm -f $LOGFILE

    echo $file | grep -q '.ok.bip$'
    if [ "$?" == "0" ]; then
	SHOULD_COMPILE=1
    else
	echo $file | grep -q '.bad.bip$'
	if [ "$?" == "0" ]; then
	    SHOULD_COMPILE=0
	else
# 	    echo "[SKIPPING] $file (not ending with .[ok|bad].bip " >> $SKIPPED_FILE
	    continue
	fi
    fi

    TMP=$(mktemp -d build-XXX)

    cd $TMP

    # 0 : compiles as expected
    # 2 : does not compile as expected
    # 1 : compiles but should not
    # 3 : does not compile but should
    if [ "$USE_RBIPC" == "1" ]; then
	rbipc.py -b $BIPC -f $file -I . -I $(dirname $file) -- --genC-execute >> $LOGFILE
	BIPC_RES="$?"
    else
	echo "RUNNING [BIP2CPP] : $BIPC -f $file --genC-execute" >> $LOGFILE 
	$BIPC -f $file --genC-execute >> $LOGFILE 2>&1
	BIPC_RES="$?"
    fi


    if [ "$BIPC_RES" == "0" ]; then
	if [ "$SHOULD_COMPILE" == "1" ]; then
	    TESTS_RESULTS_VAR="$TESTS_RESULTS_VAR;BIP2CPP:0"
	    #echo "[BIP2CPP] {compiles as expected} $file ../$LOGFILE" >> ../$SUCCESS_FILE
	elif [ "$SHOULD_COMPILE" == "0" ]; then
	    TESTS_RESULTS_VAR="$TESTS_RESULTS_VAR;BIP2CPP:1"
	    #echo "[BIP2CPP] {compiles but should not} $file ../$LOGFILE" >> ../$FAILED_FILE
	fi
    else
	if [ "$SHOULD_COMPILE" == "1" ]; then
	    TESTS_RESULTS_VAR="$TESTS_RESULTS_VAR;BIP2CPP:3"
	    #echo "[BIP2CPP] {does not compile but should} $file ../$LOGFILE" >> ../$FAILED_FILE
	elif [ "$SHOULD_COMPILE" == "0" ]; then
	    TESTS_RESULTS_VAR="$TESTS_RESULTS_VAR;BIP2CPP:2"
	    #echo "[BIP2CPP] {does not compile as expected} $file ../$LOGFILE" >> ../$SUCCESS_FILE
	fi
    fi

    # 0 : g++ does not fail
    # 1 : g++ fails
    # 3 : g++ not tested, previous step failed

    echo $file | grep -q -e 'TestSuite/backend'
    if [ "$?" == "0" -o "$C_COMPILE" == "1" ]; then
	local_compile=1
    else
	local_compile=0
    fi

    echo "" >> $LOGFILE
    if [ "$local_compile" == "1" -a "$SHOULD_COMPILE" == "1" ]; then
	if [ "$BIPC_RES" == "0" ]; then
	    echo "[START C++ COMPILATION]" >> $LOGFILE
	    cp $BIP2_HOME/util/Makefile .
	    echo "RUNNING [CPP] : make $(basename $file)" >> $LOGFILE
	    make $(basename $file) >> $LOGFILE 2>&1
	    if [ "$?" == "0" ]; then
		TESTS_RESULTS_VAR="$TESTS_RESULTS_VAR;CPP:0"
	        #echo "[CPP] $file ../$LOGFILE" >> ../$SUCCESS_FILE
	    else
		TESTS_RESULTS_VAR="$TESTS_RESULTS_VAR;CPP:1"
	        #echo "[CPP] $file ../$LOGFILE"
	    fi
	    echo "[END C++ COMPILATION]" >> $LOGFILE
	else
	    echo "[NOT STARTING C++ COMPILATION, PREVIOUS STEP FAILED]" >> $LOGFILE
	    TESTS_RESULTS_VAR="$TESTS_RESULTS_VAR;CPP:3"
	fi
    fi

    cd ..

    echo "$TEST_NAME $LOGFILE $TESTS_RESULTS_VAR" >> $RESULT_FILE

    rm -rf $TMP
done < $INFILE

if [ "$TESTS_ROOT" != "" ]; then
    rm -f $INFILE
fi
