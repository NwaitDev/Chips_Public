#!/usr/bin/python

import re
import sys

PLACE_RE=re.compile('\s*place\s+(?P<place>\S+)\s*')
ATOMIC_TYPE_RE=re.compile('\s*atomic\s+type\s+(?P<typename>[0-9A-Za-z_]+)\s*(\((?P<args>.*)\))?\s*')

f=open(sys.argv[1])

state_list=[]

for l in f.xreadlines():
    line_has_been_modified = False
    
    m = PLACE_RE.match(l)
    emit_str = ""

    if m:
        line_has_been_modified = True
        state_list.append(m.group('place'))
        continue
    else:
        if state_list:
            emit_str += "    place "
            emit_str += ", ".join(state_list)
            emit_str += "\n"
            state_list=[]

    m = ATOMIC_TYPE_RE.match(l)
    if m:
        line_has_been_modified = True
        emit_str += "    atom type " + m.group('typename') + '('
        
        if len(m.groups())>1 and m.group('args'):
            emit_str += m.group('args')
        emit_str+=')\n'

    if not line_has_been_modified:
        emit_str += l
        
    print emit_str,
