#!/usr/bin/env bash
set -u

cd "$(dirname "$0")" || exit 1

shopt -s nullglob
files=(unitTestFilesForCompiler/ShouldNotCompileSyntax/gbt_invalid_*.chips)

echo "Counting gbt_invalid files: ${#files[@]}"

if [ ${#files[@]} -eq 0 ]; then
  echo "No gbt_invalid_*.chips found under unitTestFilesForCompiler/ShouldNotCompileSyntax"
  exit 2
fi

bad=0
for f in "${files[@]}"; do
  if ./chipsc "$f" --skip-xmi >/dev/null 2> /tmp/chipsc_err.txt; then
    # It compiled successfully, but it shouldn't.
    echo "UNEXPECTED PASS: $(basename "$f")"
    bad=$((bad + 1))
  else
    :
  fi
done

echo "Total unexpected passes: $bad"

if [ $bad -ne 0 ]; then
  exit 1
fi
