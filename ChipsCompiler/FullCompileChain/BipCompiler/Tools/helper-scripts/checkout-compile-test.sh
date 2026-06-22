#!/bin/bash
ORIG=$PWD

unset CHECKOUT_EXTRA_ARGS
C_COMPILE_ARG=""
EX_BRANCH="trunk"

CHECKOUT_SH=checkout.sh
BATCH_COMPILER_SH=batch-compiler.sh
FILTER_TESTS=filter-test-to-text.sh

WWW_REG_TEST_ROOT=/local/poulhies/nightly-bip/tests
KEEP_BIP_TESTS_SOURCES=1
USE_RBIC=" "

function help {
    echo 'Checking out BIP2 and stress it ;). 
Usage:
   -c                Force the C++ compilation pass
   -g                Guess when the C++ compilation pass should be used
   -b <branch>       By default, checks out from <branch>
   -o <directory>    Directory where the HTML should be written (default $WWW_REG_TEST_ROOT)
   -n                Do not keep the BIP source in along with the logs.
   -r                Use rbipc to resolve and compile dependencies.
   -h                This help

Without argument, the script checks out the trunk and test it'

}

while getopts  "cgb:o:nrh:" flag
do
  case "$flag" in
      h) help; exit 0;;
      n) KEEP_BIP_TESTS_SOURCES=0;;
      c) C_COMPILE_ARG=" -c ";;
      g) C_COMPILE_GUESS=" -g ";;
      r) USE_RBIC=" -r ";;
      o) WWW_REG_TEST_ROOT="$OPTARG";;
      b) EX_BRANCH="$OPTARG";CHECKOUT_EXTRA_ARGS="-b $OPTARG";;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done

SCRATCH_DIR=$(mktemp -d bip2-XXX)

cd $SCRATCH_DIR && $CHECKOUT_SH -e "Examples@$EX_BRANCH" -e "TestSuite@$EX_BRANCH" $CHECKOUT_EXTRA_ARGS && cd bip2/distribution && SCM=svn ./create-distribution.sh

if [ "$?" != "0" ];then
    echo "Error during checkout/build"
    exit 255
fi

# transition between trunk (old style) and emf-java-6 (new style)
if [ -d $PWD/BIP.lnx ]; then
    # this is an "old trunk style" distribution

    export BIP2_HOME=$PWD/BIP.lnx
elif [ -d $PWD/build/BIP.linux.x86 ]; then
    export BIP2_HOME=$PWD/build/BIP.linux.x86
else
    echo "Could not guess where the distribution is...."
    exit 255
fi

cd $ORIG

DDATE=$(date  +'%F')
DIR=tests-$EX_BRANCH-$DDATE

mkdir $DIR && cd $DIR || exit 255

$BATCH_COMPILER_SH $USE_RBIC $C_COMPILE_ARG $C_COMPILE_GUESS -t $ORIG/$SCRATCH_DIR/bip2/TestSuite

cd ..
tar zcf $DIR.tar.gz $DIR 

$FILTER_TESTS $DIR
stats-wrapper.sh $DIR/results $WWW_REG_TEST_ROOT/$(basename $DIR).html "$EX_BRANCH" "$DDATE" || exit 255

rm -f $WWW_REG_TEST_ROOT/latest-"$EX_BRANCH".html || exit 255
ln -s $(basename $DIR).html $WWW_REG_TEST_ROOT/latest-"$EX_BRANCH".html || exit 255

if [ "$KEEP_BIP_TESTS_SOURCES" == "1" ]; then
    mkdir $DIR/bip2 && cp -a $SCRATCH_DIR/bip2/TestSuite $DIR/bip2
else
    rm -rf $DIR
fi

rm -rf bip2 $SCRATCH_DIR

if [ "$R" != "0" ]; then
    exit 255
fi
