# Probes and post-processing tools

When a Chips model features the ```probe``` statement within one or more of its functional block definitions, a run of that model writes one long CSV, `<name>.probe.csv`, with the columns `instance,ticks,location,expression,value`. Both tools mentionned here read that file and can be run alone or through `chipsc <file>.probe.csv`.

| Tool | Output | Options |
| --- | --- | --- |
| `probe2table.py` | One row per tick, one column per probe of each instance (`<name>.table.csv`) | `-o`, `-d` delimiter, `--decimal-comma` |
| `probe2plot.py` | One figure per instance, one step-curve subplot per probe (`probes.pdf` or PNG/SVG per instance) | `-o` folder or `.pdf`, `-f`, `-p`/`-i` regex filters, `-c`, `--size` |

- Probes with the same expression at two locations are labelled `expr (file:line:col)`.
- `true`/`false` are plotted as 1/0; non-numeric values (arrays) are skipped with a warning.
- The system's stdout goes to `SystemTrace.log`, and its stderr to `SystemRunDebug.log`.