#!/usr/bin/env bash
set -euo pipefail

HERE="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd -- "$HERE/../.." && pwd)"
CHIPS2CPP="$ROOT/FullCompileChain/Chips2Cpp/build/Chips2Cpp"
OUT="$HERE/out"
CXX="${CXX:-g++}"
failures=0

check() {
    if "${@:2}"; then
        echo "PASS $1"
    else
        echo "FAIL $1"
        failures=$((failures + 1))
    fi
}

cd "$HERE"
rm -rf "$OUT"
mkdir -p "$OUT/probes"
touch "$OUT/probes/stale_l1c1_x.csv" "$OUT/probes/unrelated.txt"
printf 'file,instance,location,expression\nstale_l1c1_x.csv,x,stale.chips:1:1,x\n' > "$OUT/probes/index.csv"

"$CHIPS2CPP" writer.chips -o "$OUT/writer.cpp" -probe-dir "$OUT/probes" > "$OUT/writer.log" 2>&1
"$CXX" -std=c++17 -I"$OUT" -o "$OUT/writer" writer_main.cpp "$OUT/writer.cpp"
check "float literals have no exponent and read back unchanged" "$OUT/writer"

check "probe files and index match expected/" diff -r expected/probes "$OUT/probes" --exclude=unrelated.txt
check "files of the previous run are deleted" test ! -e "$OUT/probes/stale_l1c1_x.csv"
check "unrelated files are kept" test -e "$OUT/probes/unrelated.txt"

"$CHIPS2CPP" reader.chips -o "$OUT/reader.cpp" -probe-dir "$OUT/back" > "$OUT/reader.log" 2>&1
"$CXX" -std=c++17 -I"$OUT" -o "$OUT/reader" reader_main.cpp "$OUT/reader.cpp"
"$OUT/reader"
for probe in 16:15 17:16 18:17 19:18 20:19 21:20; do
    check "line ${probe%%:*} round-trips through fromfile TIMED" \
        diff "$OUT/probes/writer_l${probe%%:*}c5_w1.csv" "$OUT/back/reader_l${probe##*:}c5_w1.csv"
done

python3 "$ROOT/tools/probe2table.py" "$OUT/probes" -o "$OUT/table.csv" > /dev/null
check "probe2table output matches expected/table.csv" diff expected/table.csv "$OUT/table.csv"

echo "$failures failure(s)"
exit $((failures > 0))
