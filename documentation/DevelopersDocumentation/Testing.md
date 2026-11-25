## Testing and debugging

Since the compiler is broken down into several different programs, each stage can be run and inspected alone: stop early with a flag, or start from an intermediate file.

| Goal | Command |
| --- | --- |
| Check parsing and typing only | `chipsc f.chips --chips-xmi` |
| Inspect the ATL output | `chipsc f.chips --bip-xmi`, then open `out.bip.xmi` |
| Inspect the BIP text | `chipsc f.chips --bip` |
| Inspect generated C++ | `chipsc f.chips --cpp-only`, then read `bip_importable.cpp` |
| Rebuild without recompiling Chips | `chipsc <folder>/<pkg>.bip` |
| Build but not run | `chipsc f.chips --no-run` |
| Time each step | add `--metrics` |
| Re-plot an old run | `chipsc run.probes/index.csv --plot` |

All artefacts and logs land in the output folder (`-o`, default `CHIPS_GENERATED`): one `<Step>Debug.log` per step, `merged/` and its `.map` when `--include` is used, `output/build/system`, `SystemTrace.log`.


### Tests

`ChipsCompiler/tests/probe/run.sh` checks the probe statement without the BIP engine: it generates C++ with Chips2Cpp, runs it from small C++ harnesses, compares the probe files with `expected/`, reads them back with `fromfile(..., "TIMED")` and checks they are unchanged, and checks the `probe2table.py` output. It needs a built Chips2Cpp, `g++` and `python3`; outputs land in `tests/probe/out/`.

### TODO

The probe tests are the only automated tests so far, and they cover a single statement with their own script. A common test suite would make a VERY GOOD contribution: one `tests/<feature>/` folder per feature, each with `.chips` files and their expected outputs (`.bip`, generated C++, probe folders), plus a single script that runs every folder, diffs the outputs and reports the failures. The probe tests could then be moved into that layout.