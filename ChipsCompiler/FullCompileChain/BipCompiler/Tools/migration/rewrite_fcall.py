#!/usr/bin/python
import re
import sys

##
## Reads a C src and find function decl, extract args and reinject args in
## BIP file where function call are left empty with (...) instead of args
## prototypes should have type info for args.
##

FPROTO_RE = re.compile(r'$(?P<fname>[A-Za-z0-9_]+)\s*\((?P<args>.*?)\)', re.M|re.S)

finBIP = open(sys.argv[2])
finBIP_all = finBIP.read()
finBIP.close()

fin = open(sys.argv[1])

for l in fin.xreadlines():
    m = FPROTO_RE.search(l)
    if m:
        ## print "MATCHED! : ", l
        fname = m.group('fname')
        args = m.group('args')
        ##print "re: ", fname + '\s*\(\.\.\.\)\s*;'
        finBIP_all = re.sub(fname + '\s*\(\.\.\.\)\s*;', fname+'('+args+');', finBIP_all)
        
fin.close()
print finBIP_all

