#!/bin/bash

CHECKOUT=$HOME/local/bin/checkout.sh

BRANCH=" -b trunk "

# don't forget the ending '/' !!
JAVADOC_DEST=/import/www/TOOLS/DCS/bip/javadoc/

mkdir -p /local/$LOGNAME

TMPDIR=$(mktemp -d /local/$LOGNAME/sampleXXX)
if [ $? -ne 0 ]; then
    exit 255
fi

cd $TMPDIR && $CHECKOUT $BRANCH && cd bip2/distribution && ant javadoc && rsync --delete -avz --stats docs/api/ $JAVADOC_DEST

rm -rf $TMPDIR
