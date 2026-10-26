#!/bin/bash

set -euo pipefail
trap 'echo "Error on line $LINENO"; exit 1' ERR

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"

java -cp "$SCRIPT_DIR:$SCRIPT_DIR/lib/*" emftvm "$@"