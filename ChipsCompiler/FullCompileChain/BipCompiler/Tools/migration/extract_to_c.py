#!/usr/bin/python
import re
import sys

DO_RE = re.compile(r'on\s+(?P<port>[A-Za-z0-9_]+)\s+from\s+(?P<from>[A-Za-z0-9_]+)\s+to\s+(?P<to>[A-Za-z0-9_]+)\s+(?:provided (?P<prov>.*?)(?=\s+(on|do|end|$)))?\s*(?:do\s*{(?P<code>.*?)(?<!#)})?', re.M|re.S)

INITIAL_DO_RE = re.compile(r'initial\s+to\s+(?P<to>[A-Za-z0-9_]+)\s+do\s*{(?P<code>.*?)(?<!#)}', re.M|re.S)

fin = open(sys.argv[1])
fout = open(sys.argv[2], "w")
prefix = sys.argv[3]

unique_id = 0

def gid():
    global unique_id
    unique_id += 1
    return str(unique_id)

def rewrite_initial_do(m):
    
    t = m.group('to')

    fname = prefix + '_initial__to' + t + '___' + gid()
    
    s = " initial to " + t + "\n"

    s += " do {\n"
    s += fname +  '(...);\n'
    s += " }"

    print >> fout, "void " + fname + '(...) {'
    print >> fout, m.group('code').replace('{#','').replace('#}','')
    print >> fout, "\n}\n"
    return s

def rewrite_do(m):
    port = m.group('port')
    f = m.group('from')
    t = m.group('to')
    g = m.group('prov')

    s =  " on " + port + "\n"
    s += "  from " + f + "\n"
    s += "  to " + t + "\n"
    if g:
        s += ' provided (' + g + ')\n'
    if m.group('code'):
        fname = prefix +  '_' + port + '__from'+f+'__to' + t + '___' + gid()
        s += " do {\n"
        s += fname + '(...);\n'
        s += " }"

        print >> fout, "void " + fname + '(...) {'
        print >> fout, m.group('code').replace('{#','').replace('#}','')
        print >> fout, "\n}\n"

    return s


all_file_content = fin.read()

new_file_content = DO_RE.sub(rewrite_do, all_file_content)
new_file_content = INITIAL_DO_RE.sub(rewrite_initial_do, new_file_content)

print new_file_content
fin.close()
fout.close()
