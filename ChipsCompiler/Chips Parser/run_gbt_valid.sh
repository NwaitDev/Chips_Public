#!/usr/bin/env bash
set -u

cd "$(dirname "$0")" || exit 1

shopt -s nullglob
files=(unitTestFilesForCompiler/ShouldCompileSyntax/gbt_valid_*.chips)

echo "Counting gbt_valid files: ${#files[@]}"

if [ ${#files[@]} -eq 0 ]; then
  echo "No gbt_valid_*.chips found under unitTestFilesForCompiler/ShouldCompileSyntax"
  exit 2
fi

fail=0
for f in "${files[@]}"; do
  if ./chipsc "$f" --skip-xmi >/dev/null 2> /tmp/chipsc_err.txt; then
    :
  else
    rc=$?
    echo "FAIL: $(basename "$f") (exit $rc)"
    sed -n '1,200p' /tmp/chipsc_err.txt
    echo "----"
    fail=$((fail + 1))
  fi
done

echo "Total failing: $fail"

if [ $fail -ne 0 ]; then
  exit 1
fi
