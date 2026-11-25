# Probes and post-processing tools

When a Chips model features the ```probe``` statement within one or more of its functional block definitions, a run of that model fills the folder `<name>.probes/` with:

- one CSV per probe statement and instance, named `<function>_l<line>c<col>_<instance>.csv`, with one `tick,value` line per probed value. This is the format read by `fromfile(..., "TIMED")`, so a probe file can be fed back into another model. Arrays take one column per element; nested arrays are written as quoted `"[...]"` fields.
- `index.csv`, with the columns `file,instance,location,expression`, listing every probe file of the run. Files listed in a previous `index.csv` are deleted at the start of a new run.

Both tools mentionned here read that folder (or its `index.csv`) and can be run alone or through `chipsc <name>.probes/index.csv`.

| Tool | Output | Options |
| --- | --- | --- |
| `probe2table.py` | One row per tick, one column per probe of each instance (`<name>.table.csv`) | `-o`, `-d` delimiter, `--decimal-comma` |
| `probe2plot.py` | One figure per instance, one step-curve subplot per probe (`probes.pdf` or PNG/SVG per instance) | `-o` folder or `.pdf`, `-f`, `-p`/`-i` regex filters, `-c`, `--size` |

- Probes with the same expression at two locations are labelled `expr (file:line:col)`.
- `true`/`false` are plotted as 1/0; non-numeric values (arrays) are skipped with a warning.
- The system's stdout goes to `SystemTrace.log`, and its stderr to `SystemRunDebug.log`.