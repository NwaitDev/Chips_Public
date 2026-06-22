#!/bin/bash

ROOT=$(dirname $0)/..

unset LOCAL_CP
BIP2_BACKENDS=$ROOT/lib/backends
BIP2_FILTERS=$ROOT/lib/filters

function get_backend_class {
    A=$(echo -n $1 | awk 'BEGIN { FS = "." } ; {print $NF}' | awk 'BEGIN{RS="[[:space:]]";FS=OFS=""}{$1=toupper($1);ORS=RT}1')
    echo $1.${A}Backend
}

function get_filter_class {
    A=$(echo -n $1 | awk 'BEGIN { FS = "." } ; {print $NF}' | awk 'BEGIN{RS="[[:space:]]";FS=OFS=""}{$1=toupper($1);ORS=RT}1')
    echo $1.${A}Filter
}

# this one should return only one jar.
# if there is more than one jar, it will cripple the LOCAL_CP var.
#LOCAL_CP=$(ls $ROOT/build/*.jar)

for cppart in $ROOT/lib/*.jar; do
    LOCAL_CP="$LOCAL_CP:$cppart"
done

if [ "$BIP2_BACKENDS" != "" ]; then
    IFS=":" 
    for jardir in $BIP2_BACKENDS; do
	LOCAL_CP="$LOCAL_CP:$jardir"
	unset IFS
	for jarfile in $jardir/*.jar; do
            LOCAL_CP="$LOCAL_CP:$jarfile"
	    BACKENDS="$BACKENDS;$(get_backend_class $(basename $jarfile .jar | cut -d'_' -f1))"
	    
	done
    done
    unset IFS
fi

## loads filters
IFS=":" 
for jardir in $BIP2_FILTERS; do
    LOCAL_CP="$LOCAL_CP:$jardir"
    unset IFS
    for jarfile in $jardir/*.jar; do
        LOCAL_CP="$LOCAL_CP:$jarfile"
	FILTERS="$FILTERS;$(get_filter_class $(basename $jarfile .jar | cut -d'_' -f1))"
    done
done
unset IFS

# configure for native libraries
export LD_LIBRARY_PATH=${ROOT}/lib:${LD_LIBRARY_PATH}

java -Dbip.compiler.backends="$BACKENDS" -Dbip.compiler.filters="$FILTERS" -ea -cp $LOCAL_CP ujf.verimag.bip.userinterface.cli.Runner $*
