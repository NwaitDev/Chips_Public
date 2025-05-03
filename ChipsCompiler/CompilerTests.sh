#!/bin/bash

shopt -s nullglob

BLUE='\033[0;34m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${BLUE}Should compile (Syntaxically correct):${NC}"
for f in ./unitTestFilesForCompiler/ShouldCompileSyntax/*.chips
do
    ./chipsc $f > /dev/null
    if [ "$?" -ne 0 ]; then 
        echo -e "${RED}$(basename $f) didn't compile (but it should)${NC}"
    else
        echo -e "${GREEN}$(basename $f) compiled (as it should)${NC}"
    fi
done

echo
echo -e "${BLUE}Should not compile (Syntaxically incorrect):${NC}"
for f in ./unitTestFilesForCompiler/ShouldNotCompileSyntax/*.chips
do
    ./chipsc $f > /dev/null
    if [ "$?" -ne 0 ];
    then 
        echo -e "${GREEN}$(basename $f) didn't compile (as intended)${NC}"
    else
        echo -e "${RED}$(basename $f) compiled (but it shouldn't)${NC}"
    fi
done

echo
echo -e "${BLUE}Should compile (semantically correct):${NC}"
for f in ./unitTestFilesForCompiler/ShouldCompileSemantic/*.chips
do
    ./chipsc $f > /dev/null
    if [ "$?" -ne 0 ]; then 
        echo -e "${RED}$(basename $f) didn't compile (but it should)${NC}"
    else
        echo -e "${GREEN}$(basename $f) compiled (as it should)${NC}"
    fi
done

echo

echo -e "${BLUE}Should not compile (semantically incorrect):${NC}"
for f in ./unitTestFilesForCompiler/ShouldNotCompileSemantic/*.chips
do
    ./chipsc $f > /dev/null
    if [ "$?" -ne 0 ];
    then 
        echo -e "${GREEN}$(basename $f) didn't compile (as intended)${NC}"
    else
        echo -e "${RED}$(basename $f) compiled (but it shouldn't)${NC}"
    fi
done