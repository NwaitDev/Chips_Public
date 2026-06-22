#!/bin/bash

DAYS=10
ROOT=/local/poulhies/nightly-bip

# match something like "2010-06-09-trunk"
PATTERN="20*"

find $ROOT -maxdepth 1  -name "$PATTERN" -type d -mtime +$DAYS -print | while read dir; do
    echo "removing: " $dir
    rm -rf $dir
done
