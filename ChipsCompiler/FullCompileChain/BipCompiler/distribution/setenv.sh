#!/bin/bash

ROOT=$PWD

ENGINE=$1

OS=`uname -s`

: ${ENGINE:="reference-engine"}

export PATH=$PWD/build/bipc-latest/bin/:$PATH

export BIP2_ENGINE_LIB_DIR=$(ls -d $PWD/build/ENGINE-${ENGINE}/_CPack_Packages/${OS}/TGZ/BIP-${ENGINE}-*/lib/static/ 2> /dev/null)

export BIP2_ENGINE_SPECIFIC_DIR=$(ls -d $PWD/build/ENGINE-${ENGINE}/_CPack_Packages/${OS}/TGZ/BIP-${ENGINE}-*/include/specific/ 2> /dev/null)
export BIP2_ENGINE_GENERIC_DIR=$(ls -d $PWD/build/ENGINE-${ENGINE}/_CPack_Packages/${OS}/TGZ/BIP-${ENGINE}-*/include/generic/ 2> /dev/null)

echo "Environment configured for engine: " ${ENGINE}

[ -d "${BIP2_ENGINE_GENERIC_DIR}" -a ! -z "${BIP2_ENGINE_GENERIC_DIR}" ] || echo 'WARNING, the engine files may not exist. Check given name!'

# if [ "$OS" == "Darwin" ]; then
#     if [ ! -e ~/lib ]; then
#         mkdir ~/lib
#     fi

#     /bin/cp -f $PWD/build/bipc-latest/lib/*.dylib ~/lib/
#     /bin/cp -f $PWD/build/bipc-latest/lib/*.jnilib ~/lib/
# fi
