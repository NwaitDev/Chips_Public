#!/bin/bash

# exit at first error.
set -e

# unbound variables are evil(tm) 
set -u

WRAP_ARGS=""
V=""
RELEASE=0

function help {
 echo 'BIP distribution wrapper - idiot proof version
Usage:
  -r              When building a revision to release :)
  -v              Give the version name instead of it being generated
  -h              This help
'
}

while getopts  "hrv:" flag
do
  case "$flag" in
      r) WRAP_ARGS="${WRAP_ARGS} -r"; RELEASE=1;;
      h) help; exit 0;;
      v) WRAP_ARGS="${WRAP_ARGS} -v ${OPTARG}"; V=${OPTARG};;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done

# first, wrap !
./wrap.sh ${WRAP_ARGS}


# if not specifed on command line...
if [ "$V" == "" ]; then
    if [ "$RELEASE" == "1" ]; then
	V=$(date +%Y.%m)
    else
	V=$(date +%Y.%m.%H%M%S)-DEV
    fi
fi

FROOT=build/bip-full

rm -rf ${FROOT} && mkdir -p ${FROOT}
cd ${FROOT}
tar zxvf ../bipc_*.tar.gz
for engine_tfile in ../BIP-*engine*`uname -m`*.tar.gz; do
    tar zxvf $engine_tfile
done

echo '''#!/bin/bash
FDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

ROOT=${FDIR}

ENGINE=${1:-reference-engine}

export PATH=$PATH:$(ls -d ${FDIR}/bipc-*/bin/)

export BIP2_ENGINE_LIB_DIR=$(ls -d ${FDIR}/BIP-${ENGINE}-*/lib/static/)

export BIP2_ENGINE_SPECIFIC_DIR=$(ls -d ${FDIR}/BIP-${ENGINE}-*/include/specific/)
export BIP2_ENGINE_GENERIC_DIR=$(ls -d ${FDIR}/BIP-${ENGINE}-*/include/generic/)
echo "Environment configured for engine: " ${ENGINE}

''' > setup.sh

chmod +x setup.sh

cd ..
tar zcvf bip-full-${V}_`uname -m`.tar.gz bip-full
