#!/bin/bash


function help {
    echo 'Add a BIP source file to the tests database. 
Usage:
   -f <bip file>     The file to add to the Test Suite
   -b <branch>       Use <branch> branch of the Test Suite
'
}

while getopts  "=hf:b:" flag
do
  case "$flag" in
      e) BIP_FILE="$EXTRA_MODULES $OPTARG";;
      b) BRANCH=$OPTARG;;
      h) help; exit 0;;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done

if [ ! -f "$BIP_FILE" ]; then
    echo "You must provide a file path to an existing file as argument [$1]"
    exit 255
else
    echo $BIP_FILE | grep -q -e '\.bip$'
    if [ "$?" != "0" ]; then
	echo "File must end with .bip [$BIP_FILE]"
	exit 255
    else
	TEST_FILE="$BIP_FILE"
    fi
fi


if [ "$BRANCH" == "" -o "$BRANCH" == "trunk" ]; then
    ACTUAL_BRANCH=trunk
else
    ACTUAL_BRANCH="branches/$BRANCH"
fi


ORIG_DIR=$PWD

# trick to get the absolute path
ABS_DIR=$(cd $(dirname $TEST_FILE) && pwd)
FNAME=$(basename $TEST_FILE)

declare -a categories
categories=(\
"grammar" "Test the grammar/parser" \
"model" "Tests that some BIP model are well compiled/rejected" \
)

declare -a subcategories
subcategories=(\
"main" "Main language" \
"realtime" "Everything specific to realtime" \
"priority" "Everything related to priorities" \
"connector" "Everything related to connectors" \
)

SIFS=$IFS
IFS=""

category=$(whiptail --separate-output --menu "In which category does this test belong ?" 20 70 10  ${categories[@]} 3>&2 2>&1 1>&3-)
if [ "$?" == "1" ]; then
    echo "Aborted"
    cd $ORIG_DIR
    exit 255
fi

subcategory=$(whiptail --separate-output --menu "Does it belong to any of the following subcategory? (select main if not)" 20 70 10 ${subcategories[@]} 3>&2 2>&1 1>&3-)
if [ "$?" == "1" ]; then
    echo "Aborted"
    cd $ORIG_DIR
    exit 255
fi

should_compile=$(whiptail --separate-output --menu "Should this test be successfull ?" 20 70 10 Yes ", it should compile" No ", it should be rejected" 3>&2 2>&1 1>&3-)
if [ "$?" == "1" ]; then
    echo "Aborted"
    cd $ORIG_DIR
    exit 255
fi

should_cpp=$(whiptail --separate-output --menu "Is this a test for the C++ code generation ?" 20 70 10 Yes ", g++ must be invoked" No ", g++ must not be invoked" 3>&2 2>&1 1>&3-)
if [ "$?" == "1" ]; then
    echo "Aborted"
    cd $ORIG_DIR
    exit 255
fi

descro=""
while [ "$descro" == "" ]; do
    descro=$(whiptail --separate-output --inputbox "Give a brief description (leaving this empty is *NOT* valid)" 20 70 3>&2 2>&1 1>&3-)
    if [ "$?" == "1" ]; then
	echo "Aborted"
	cd $ORIG_DIR
	exit 255
    fi
done

IFS=$SIFS

REPOS_ROOT=svn+ssh://$LOGNAME@ssh-veri.imag.fr/svn/bip2

SCRATCH_DIR=$(mktemp -d)

cd $SCRATCH_DIR
svn co $REPOS_ROOT/TestSuite/$ACTUAL_BRANCH TestSuite
cd TestSuite

if [ "$should_compile" == "Yes" ]; then
    EXT="ok"
else
    EXT="bad"
fi

if [ "$should_cpp" == "Yes" ]; then
    compiler_part="backend"
else
    compiler_part="frontend"
fi

cd $compiler_part/$category/$subcategory

TARGET_FNAME=$(basename $FNAME .bip).$EXT.bip

if [ -f "$TARGET_FNAME" ]; then
    echo "Test file already exists, please change filename"
    rm -rf "$SCRATCH_DIR"
    cd $ORIG_DIR
    exit 255
fi

cp $ABS_DIR/$FNAME $TARGET_FNAME
svn add $TARGET_FNAME

rm -f tmp_log
echo "Assisted test addition." >> tmp_log
echo "$descro" >> tmp_log
svn commit -F tmp_log
cd $ORIG_DIR
rm -rf $SCRATCH_DIR
echo "All done"
