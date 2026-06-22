#!/bin/bash

NIGHTLY_BUILD_ROOT=/local/poulhies/nightly-bip
CHECKOUT=checkout.sh
BRANCH=trunk


while getopts  "b:" flag
do
  case "$flag" in
      b) BRANCH=$OPTARG;;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done


DATE=$(date  +'%F')

TODAY_ROOT=$NIGHTLY_BUILD_ROOT/$DATE-$BRANCH

TODAY_BUILD_LOG=$TODAY_ROOT/build-log
TODAY_CHECKOUT_LOG=$TODAY_ROOT/checkout-log
TODAY_ENV=$TODAY_ROOT/env

mkdir -p $TODAY_ROOT || exit 255

env &> $TODAY_ENV
cd $TODAY_ROOT

(time $CHECKOUT -b $BRANCH) &> $TODAY_CHECKOUT_LOG || exit 255

cd bip2/distribution
(SCM=svn time ./create-distribution.sh) &> $TODAY_BUILD_LOG

cd $NIGHTLY_BUILD_ROOT && rm -f latest-$BRANCH && ln -s $DATE-$BRANCH latest-$BRANCH