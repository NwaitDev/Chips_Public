#!/usr/bin/env python

import optparse 
import sys
import re
import os.path
import os

include_dirs = []

all_packages = {}
scheduled_compilation = []


class Package:
    def __init__(self, filepath, name, deps=None):
        self.name = name
        self.filepath = filepath
        self.deps = deps

    def __str__(self):
        return "Package[%s]@%s" %(self.name, self.filepath)

class PackageNotFoundException:
    pass


def compile_everything(package):
    global scheduled_compilation
    
    for dep in package.deps:
        if dep.name not in scheduled_compilation:
            compile_everything(dep)
    scheduled_compilation.append(package.filepath)
    
def find_package_file(package_name):
    for directory in include_dirs:
        f = os.path.join(directory, package_name+".bip")
        if os.path.exists(f):
            return f
    print "Could not find", package_name+".bip", "in", include_dirs
    raise PackageNotFoundException()

def resolve_file_deps(filepath, root=False):
    global all_packages
    
    fin = open(filepath)

    deps = set()
    name = None
    
    for l in fin.xreadlines():
        m = re.match("\s*package\s+(?P<package>\S*)", l)
        if m:
            name = m.group('package')

        m = re.match("\s*use\s+(?P<package>\S*)", l)
        if m:
            sub = find_package_file(m.group('package'))
            if sub in all_packages:
                deps.add(all_packages[sub])
            else:
                deps.add(resolve_file_deps(sub))

    fin.close()
    
    if root:
        return deps
    
    if name == None:
        print "Error, missing package name"
        sys.exit(-1)
    else:
        p = Package(filepath, name, deps)
        all_packages[name] = p
        return p


def main(argv):
    global include_dirs
    global scheduled_compilation
    
    include_dirs = []
    parser = optparse.OptionParser()
    
    parser.add_option("-I", dest="include_dirs",
                      action="append", type="str")

    parser.add_option("-f","--file", dest="filename",
                      metavar="FILE")

    parser.add_option("-b", dest="bipc",
                      metavar="bipc-exec")
    
    options, args = parser.parse_args(argv)

    print "orig arg:", argv

    if "--" in argv: argv.remove("--")

    for farg in ("-f", "--file", "-b"):
        if farg in argv:
            i = argv.index(farg)
            argv.pop(i)
            argv.pop(i)
            
    print "new arg:", argv
    
    include_dirs = options.include_dirs
    d = resolve_file_deps(options.filename, True)

    bipc = "bipc"
    if options.bipc:
        bipc=options.bipc

    for dep in d:
        compile_everything(dep)
    scheduled_compilation.append(options.filename)

    for f in scheduled_compilation:
        cmd = "%s -f %s %s" %(bipc, f, " ".join(argv[1:]))
        print "[EXEC]", cmd
        r = os.system(cmd)
        print "[EXECUTED %s]" %r, cmd
        if r != 0:
            return r
    return 0
    
if __name__ == '__main__':
    r = main(sys.argv)
    sys.exit((r & 0xFF00)>>8)
