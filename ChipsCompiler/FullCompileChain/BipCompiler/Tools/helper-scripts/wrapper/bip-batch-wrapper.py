#!/usr/bin/env python

import ConfigParser
import sys
import os

configo = ConfigParser.ConfigParser()

configo.read(sys.argv[1])

for section in configo.sections():

    if section == "settings":
        continue

    elt_branch = configo.get(section, "branch")
    elt_type = configo.get(section, "type")
    elt_run_c_tests = configo.get(section, "run_c_tests") == "1"
    elt_env = configo.get(section, "env")
    elt_tests_result_root = configo.get(section, "tests_result_root")

    if elt_type == "build":
        cmd = ". %s && ~/local/bin/daily-builder.sh -b %s" % (elt_env, elt_branch)
    elif elt_type == "tests":
        cmd = ". %s && " % elt_env
        cmd += "cd %s && " % elt_tests_result_root
        cmd += "~/local/bin/checkout-compile-test.sh -b %s" % elt_branch
        if elt_run_c_tests:
            cmd += " -c "

    print cmd
    os.system(cmd)
