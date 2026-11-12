LIBS_DIR="$SCRIPT_DIR/libs"
TOOLS_DIR="$SCRIPT_DIR/tools"
PROBE2TABLE="$TOOLS_DIR/probe2table.py"
PROBE2PLOT="$TOOLS_DIR/probe2plot.py"

CHIPS_PARSER="$SCRIPT_DIR/FullCompileChain/Chips2XmiParser/chipsparser"
ATL_RUNNER="$SCRIPT_DIR/FullCompileChain/ChipsModel2BipModel/emftvm.sh"
CHIPS_METAMODEL="$SCRIPT_DIR/FullCompileChain/metamodels/chips1.1.ecore"
BIP_METAMODEL="$SCRIPT_DIR/FullCompileChain/metamodels/BIP.ecore"
ATL_TRANSFORMATION="$SCRIPT_DIR/FullCompileChain/ChipsModel2BipModel/transformations/chips2bip.atl"
CPP_GENERATOR="$SCRIPT_DIR/FullCompileChain/Chips2Cpp/build/Chips2Cpp"
BIPC="$SCRIPT_DIR/FullCompileChain/BipCompiler/distribution/build/bipc-latest/bin/bipc"
BIP_SETENV="$SCRIPT_DIR/FullCompileChain/BipCompiler/distribution/setenv.sh"

ROOT_COMPONENT="SYSTEM_COMPOUND"
CPP_BASENAME="bip_importable"
DEFAULT_OUTPUT_DIR="CHIPS_GENERATED"

if [[ -t 1 && -z "${NO_COLOR:-}" ]]; then
    YELLOW=$'\033[33m'
    GREEN=$'\033[32m'
    RESET=$'\033[0m'
else
    YELLOW=""
    GREEN=""
    RESET=""
fi
