# Chips to C++ generator (Chips2Cpp)

Chips2Cpp writes `bip_importable.hpp/.cpp`: the C++ bodies of the components' functions, which bipc links into the generated system.

| Argument | Meaning | Default |
| --- | --- | --- |
| `input` | Chips file (the merged file when `--include` is used) | — |
| `-o` / `-oh` | Generated source / header | `bip_importable.cpp` / same name `.hpp` |
| `-max-ticks` | THEN cycles after which each core component stops | 1000 |
| `-probe-dir` | Folder where `probe` statements write one CSV per statement and instance | `<input>.probes` |
| `-source-map` | `<first line>\t<path>` per merged file, for error and probe locations | — |

- `src/main.cpp` parses the file, walks it with `CodeGenListener`, and prepends the runtime header (`cppHeaderAutoInclude.hpp`) to the generated header.
- `src/CodeGenListener.cpp` has one `translate*` function per construct (loops, ifs, assignments, contextual assignments, expressions). A statement with no translation is copied verbatim and reported as `unhandled:`.
- `probe <expr>` becomes `chips_probe(instance, ticks, "<function>_l<line>c<col>", "file:line:col", "<expr text>", value)`, which appends `tick,value` to `<probe dir>/<function>_l<line>c<col>_<instance>.csv`. Probes are only allowed in the `init` and `then` sections of a function.