#!/bin/bash

#LOGNAME=poulhies
REPOS_ROOT=svn+ssh://$LOGNAME@ssh-veri.imag.fr/svn/bip2

DEFAULT_MODULES="Compiler/Frontend Compiler/Backend Engines@trunk distribution Documents LanguageFactories/C@trunk"

FALLBACK_BRANCH=trunk

BRANCH=""
MODULES=""
EXTRA_MODULES=""

function help {
    echo 'Checking out BIP2 ;). 
Usage:
   -e <module spec>  Extra module to check out
   -m <module spec>  Check out this module (override defaults modules)
   -b <branch>       By default, checks out from <branch>

A module spec is given by a directory in the svn with an optional branch name:
  LanguageFactories@trunk
  Compiler/Frontend

Default modules are:
'
    echo $DEFAULT_MODULES
    echo '
Without argument, the script checks out the trunk'

    echo 'Example:
$ checkout.sh -e Tools@emf-java-6
'
}

function get_branch {
    MODULE=$1
    DEFAULT_BRANCH=$2

    SPEC_BRANCH=$(echo $MODULE | cut -s -d'@' -f2)
    if [ "$SPEC_BRANCH" == "" ]; then
	echo $2
    elif [ "$SPEC_BRANCH" == "trunk" ]; then
	echo trunk
    else
	echo branches/$SPEC_BRANCH
    fi;
}

while getopts  "he:m:b:" flag
do
  case "$flag" in
      e) EXTRA_MODULES="$EXTRA_MODULES $OPTARG";;
      b) BRANCH=$OPTARG;;
      m) MODULES="$MODULES $OPTARG";;
      h) help; exit 0;;
      *) echo "Unknown argument:" $flag; exit 255;
  esac
done

if [ "$BRANCH" == "" -o "$BRANCH" == "trunk" ]; then
    ACTUAL_BRANCH=trunk
else
    ACTUAL_BRANCH="branches/$BRANCH"
fi

if [ "$MODULES" == "" ]; then
    MODULES=$DEFAULT_MODULES
fi

MODULES="$MODULES $EXTRA_MODULES"

# create the root for keeping the possibility to commit on different sub project

svn co --depth empty svn+ssh://$LOGNAME@ssh-veri.imag.fr/svn/bip2 && cd bip2
svn co --depth empty svn+ssh://$LOGNAME@ssh-veri.imag.fr/svn/bip2/Compiler
svn co --depth empty svn+ssh://$LOGNAME@ssh-veri.imag.fr/svn/bip2/LanguageFactories

SUMMARY="Checkout Summary:\n"

for module in $MODULES; do
    MOD_BRANCH=$(get_branch $module $ACTUAL_BRANCH)
    MOD_NAME=$(echo $module|cut -d'@' -f1)
    svn co $REPOS_ROOT/$MOD_NAME/$MOD_BRANCH $MOD_NAME
    if [ "$?" != "0" ]; then
	svn co $REPOS_ROOT/$MOD_NAME/$FALLBACK_BRANCH $MOD_NAME	
	SUMMARY="$SUMMARY - $MOD_NAME -> trunk\n"
    else
	SUMMARY="$SUMMARY - $MOD_NAME -> $MOD_BRANCH\n"
    fi
done

echo -e $SUMMARY
