#!/bin/bash


DIR=$1

if [ "$DIR" == "." -o "$DIR" == "" ] ;then
    LFILE="filtered-results.log"
else
    LFILE=$(dirname $DIR)/$(basename $DIR).log
fi

echo "Log: $LFILE"

# clean comments/empty lines
TOTAL_TESTS=$(grep -v -e '^#' -v -e '^[:space:]*$' $DIR/results|wc -l)

if [ "$TOTAL_TESTS" == "0" ];then
    echo 'No tests ?!' >> $LFILE
    exit 255
fi


GLOB_SUCC=0
BIP2CPP_SUCC=0
BIP2CPP_FAIL=0
CPP_SUCC=0
CPP_FAIL=0

IFS='
'
for testline in $(grep -v -e '^#' -v -e '^[:space:]*$' $DIR/results); do

    local_succ=1
    tests_res=$(echo $testline | cut -d' ' -f3 | sed -e s/'^;'//)
    OIFS=$IFS
    IFS=';' 
    for test_item in $tests_res; do

 	tname=$(echo $test_item | cut -d':' -f1)
 	tres=$(echo $test_item | cut -d':' -f2)

 	if [ $(($tres%2)) == 0 ]; then

 	    case $tname in
 		BIP2CPP) BIP2CPP_SUCC=$((BIP2CPP_SUCC+1)) ;;
 		    CPP) CPP_SUCC=$((CPP_SUCC+1)) ;;
 	    esac
 	else
	    local_succ=0
 	    case $tname in
 		BIP2CPP) BIP2CPP_FAIL=$((BIP2CPP_FAIL+1)) ;;
 		    CPP) CPP_FAIL=$((CPP_FAIL+1)) ;;
 		    *)
 	    esac
 	fi
    done
    GLOB_SUCC=$(($GLOB_SUCC+$local_succ))
    IFS=$OIFS
done

cat $DIR/results >> $LFILE
echo -e "\n\n******\n\n" >> $LFILE
 
echo "Success rate : $(($GLOB_SUCC * 100 / $TOTAL_TESTS))% [$GLOB_SUCC/$TOTAL_TESTS]" >> $LFILE

if [ "$BIP2CPP_SUCC" != "0" -o "$BIP2CPP_FAIL" != "0" ]; then
    echo "BIP2CPP: successful=$BIP2CPP_SUCC, failed=$BIP2CPP_FAIL, total=$(($BIP2CPP_FAIL+$BIP2CPP_SUCC))" >> $LFILE
fi

if [ "$CPP_SUCC" != "0" -o "$CPP_FAIL" != "0" ]; then
    echo "CPP: successful=$CPP_SUCC, failed=$CPP_FAIL, total=$(($CPP_FAIL+$CPP_SUCC)) " >> $LFILE
fi


