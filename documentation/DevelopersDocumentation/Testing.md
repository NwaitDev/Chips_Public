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
| Re-plot an old run | `chipsc run.probe.csv --plot` |

All artefacts and logs land in the output folder (`-o`, default `CHIPS_GENERATED`): one `<Step>Debug.log` per step, `merged/` and its `.map` when `--include` is used, `output/build/system`, `SystemTrace.log`.


### TODO

There is no automated test suite yet. A `tests/` folder of `.chips` files with expected `.bip` and probe CSVs, plus a script that diffs them, would make a VERY GOOD contribution.