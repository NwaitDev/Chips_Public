#!/bin/bash

# where stuff should go
PUBLISH_ROOT=/import/www/TOOLS/DCS/bip/distribution

# root directories for distributions
ACTIVE_DISTRIBUTION="BIP.linux.x86"

# plugins to distribute as standalone jars (bytecode only)
PUBLISHED_PLUGINS="ujf.verimag.bip.parser"
# same as above, but ship with source code also
PUBLISHED_PLUGINS_WITH_SRC="ujf.verimag.bip.metamodel"

DIST_ROOT=$PUBLISH_ROOT/full
PLUGINS_ROOT=$PUBLISH_ROOT/plugins

if [ ! -x ./create-distribution.sh ]; then
    echo "You must be within the distribution/ directory in the bip2 source to run this."
    exit 255
fi

(./create-distribution.sh || (echo "Error building distribution" && exit 255)) || exit 255

for dist in $ACTIVE_DISTRIBUTION; do
    cp dist/$ACTIVE_DISTRIBUTION.tar.gz $DIST_ROOT
done

for plugin in $PUBLISHED_PLUGINS; do
    cp $(ls dist/${plugin}*.jar | grep -v src.jar)  $PLUGINS_ROOT
done

for plugin in $PUBLISHED_PLUGINS_WITH_SRC; do
    cp $(ls dist/${plugin}*.src.jar)  $PLUGINS_ROOT
done
