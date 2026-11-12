plan_stages() {
    case "$FORMAT" in
        chips)     FIRST_STAGE=1 ;;
        chips.xmi) FIRST_STAGE=2 ;;
        bip.xmi)   FIRST_STAGE=3 ;;
        bip)       FIRST_STAGE=4 ;;
    esac

    case "$STOP_FLAG" in
        --chips-xmi) LAST_STAGE=1 ;;
        --bip-xmi)   LAST_STAGE=2 ;;
        --bip)       LAST_STAGE=3 ;;
        --cpp-only)  LAST_STAGE=0 ;;
        *)           LAST_STAGE=4 ;;
    esac

    DO_CPP=0
    if [[ "$FORMAT" == "chips" && ( "$STOP_FLAG" == "--cpp-only" || "$LAST_STAGE" -eq 4 ) ]]; then
        DO_CPP=1
    fi

    CHIPS_XMI_FILE="$OUTPUT_DIR/out.chips.xmi"
    BIP_XMI_FILE="$OUTPUT_DIR/out.bip.xmi"
    BIP_FILE=""
    PROBE_FILE=""
}

stage_selected() {
    [[ "$1" -ge "$FIRST_STAGE" && "$1" -le "$LAST_STAGE" ]]
}

stage_chips_xmi() {
    run_step \
        "CHIPS -> CHIPS XMI" \
        "$OUTPUT_DIR/ChipsXmiGeneratorDebug.log" \
        "$CHIPS_PARSER" \
        "$CHIPS_SOURCE" \
        "$CHIPS_XMI_FILE"
}

stage_bip_xmi() {
    [[ "$FORMAT" == "chips.xmi" ]] && CHIPS_XMI_FILE="$FILE"
    run_step \
        "CHIPS XMI -> BIP XMI" \
        "$OUTPUT_DIR/BipXmiGeneratorDebug.log" \
        "$ATL_RUNNER" \
        "$CHIPS_METAMODEL" \
        "$BIP_METAMODEL" \
        "$CHIPS_XMI_FILE" \
        "$ATL_TRANSFORMATION" \
        "$BIP_XMI_FILE"
}

stage_cpp() {
    local cpp_args=("$CHIPS_SOURCE" -o "$OUTPUT_DIR/$CPP_BASENAME.cpp")
    [[ -n "$SOURCE_MAP" ]] && cpp_args+=(-source-map "$SOURCE_MAP")
    PROBE_FILE="$OUTPUT_DIR/$(basename -- "$FILE" .chips).probe.csv"
    cpp_args+=(-probe-file "$PROBE_FILE")
    [[ -n "$MAX_TICKS" ]] && cpp_args+=(-max-ticks "$MAX_TICKS")
    run_step \
        "CHIPS -> C++" \
        "$OUTPUT_DIR/CppGeneratorDebug.log" \
        "$CPP_GENERATOR" \
        "${cpp_args[@]}"
}

stage_bip() {
    [[ "$FORMAT" == "bip.xmi" ]] && BIP_XMI_FILE="$FILE"
    local marker="$OUTPUT_DIR/.chipsc_bip_marker"
    touch "$marker"
    run_step \
        "BIP XMI -> BIP" \
        "$OUTPUT_DIR/BipGeneratorDebug.log" \
        "$BIPC" \
        --xmi "$BIP_XMI_FILE" \
        -d "$ROOT_COMPONENT" \
        --genbip-output-dir "$OUTPUT_DIR"
    BIP_FILE="$(find "$OUTPUT_DIR" -maxdepth 1 -name '*.bip' -newer "$marker" -print -quit)"
    rm -f "$marker"
    if [[ -z "$BIP_FILE" ]]; then
        echo "Error: bipc did not produce any .bip file in '$OUTPUT_DIR'." >&2
        exit 1
    fi
    run_step \
        "BIP identifiers cleanup" \
        "$OUTPUT_DIR/BipCleanupDebug.log" \
        sed -i 's/@0//g' "$BIP_FILE"
}

bip_env_set() {
    [[ -n "${BIP2_ENGINE_LIB_DIR:-}" && -n "${BIP2_ENGINE_GENERIC_DIR:-}" && -n "${BIP2_ENGINE_SPECIFIC_DIR:-}" ]]
}

load_bip_env() {
    bip_env_set && return 0
    if [[ -f "$BIP_SETENV" ]]; then
        local previous_dir="$PWD"
        cd -- "$(dirname -- "$BIP_SETENV")"
        set +eu
        source "./$(basename -- "$BIP_SETENV")" > /dev/null
        set -eu
        cd -- "$previous_dir"
    fi
    if ! bip_env_set; then
        echo "Warning: BIP2_ENGINE_* variables are not set and could not be loaded from '$BIP_SETENV'; the build will probably fail." >&2
    fi
}

stage_build() {
    [[ "$FORMAT" == "bip" ]] && BIP_FILE="$FILE"
    local bip_dir package cpp_dir ext
    bip_dir="$(dirname -- "$BIP_FILE")"
    package="$(basename -- "$BIP_FILE" .bip)"

    cpp_dir="$OUTPUT_DIR"
    [[ "$FORMAT" == "bip" ]] && cpp_dir="$bip_dir"
    for ext in cpp hpp; do
        if [[ ! -f "$cpp_dir/$CPP_BASENAME.$ext" ]]; then
            echo "Error: '$cpp_dir/$CPP_BASENAME.$ext' is missing." >&2
            echo "Generate it from the .chips specification (--cpp-only) before building the system." >&2
            exit 1
        fi
    done

    load_bip_env

    BUILD_ROOT="$OUTPUT_DIR/output"
    mkdir -p "$BUILD_ROOT/build"

    run_step \
        "BIP -> C++ project" \
        "$OUTPUT_DIR/BipCppGeneratorDebug.log" \
        in_dir "$bip_dir" \
        "$BIPC" \
        -I "$bip_dir" \
        -p "$package" \
        -d "$ROOT_COMPONENT()" \
        --gencpp-cc-extra-opt=-std=c++17 \
        --gencpp-cc-extra-opt=-I"$cpp_dir" \
        --gencpp-cc-I="$CPP_BASENAME.hpp" \
        --gencpp-cc-extra-src="$cpp_dir/$CPP_BASENAME.cpp" \
        --gencpp-output-dir="$BUILD_ROOT"

    run_step \
        "CMake configuration" \
        "$OUTPUT_DIR/CMakeDebug.log" \
        cmake -S "$BUILD_ROOT" -B "$BUILD_ROOT/build" -Wno-dev

    run_step \
        "System build" \
        "$OUTPUT_DIR/BuildDebug.log" \
        cmake --build "$BUILD_ROOT/build"

    echo
    echo "System executable: $BUILD_ROOT/build/system"
}

stage_run() {
    run_step \
        "System execution" \
        "$OUTPUT_DIR/SystemRunDebug.log" \
        in_dir "$OUTPUT_DIR" \
        with_spinner "$OUTPUT_DIR/SystemTrace.log" \
        "$BUILD_ROOT/build/system"
    echo "Execution trace: $OUTPUT_DIR/SystemTrace.log"

    if [[ -n "$PROBE_FILE" && -f "$PROBE_FILE" ]]; then
        process_probes "$PROBE_FILE"
    fi
}

run_pipeline() {
    plan_stages
    if stage_selected 1; then
        stage_chips_xmi
    fi
    if stage_selected 2; then
        stage_bip_xmi
    fi
    if [[ "$DO_CPP" -eq 1 ]]; then
        stage_cpp
    fi
    if stage_selected 3; then
        stage_bip
    fi
    if stage_selected 4; then
        stage_build
        if [[ "$NO_RUN" -eq 0 ]]; then
            stage_run
        fi
    fi
}
