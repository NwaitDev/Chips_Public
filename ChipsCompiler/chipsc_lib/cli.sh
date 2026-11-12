declare -A DESCRIPTIONS=(
    ["-h"]="Print this message."
    ["-i"]="Print information about this software."
    ["file"]="Source file to work with. Accepted formats are .chips, .chips.xmi, .bip.xmi, .bip or .csv. A .csv file must be a probe file: only the probe table (and the plots with --plot) are generated from it."
    ["--chips-xmi"]="Stop the compilation after having generated the xmi serialized version of <file> chips model. Only works with .chips files."
    ["--bip-xmi"]="Stop the compilation after having generated the xmi serialized version of <file> equivalent bip model. Only works with .chips and .chips.xmi files."
    ["--bip"]="Stop the compilation after having generated the bip model of <file>. Only works with .chips, .chips.xmi and .bip.xmi files."
    ["--cpp-only"]="Only generate the c++ procedures relative to <file> components. Only works with .chips files."
    ["--max-ticks"]="Maximum number of computation cycles after which every component stops (default: 1000)."
    ["--metrics"]="Print the time spent in each step and statistics about the models."
    ["--include"]="Prepend the content of the chips <lib> file to <file> before compiling it. <lib> is either a path or the name of a file in the libs folder (the .chips extension can be omitted). Can be given several times: the files are prepended in the given order. An included file must not contain a system section. Only works with .chips files."
    ["-o"]="The name of the folder in which to store the model elements generated. If no <folder> is specified, artifacts will be stored in CHIPS_GENERATED."
    ["--no-run"]="Build the system executable without running it nor post-processing its probes."
    ["--plot"]="Plot the probed values (one pdf page per instance) in <folder>/probes.pdf. Only works with .chips files (after running the system) and .csv probe files."
)

OPTION_ORDER=(-h -i --chips-xmi --bip-xmi --bip --cpp-only --max-ticks --metrics --include -o --no-run --plot)
declare -A OPTION_ARGS=(
    ["--max-ticks"]="<n>"
    ["--include"]="<lib>"
    ["-o"]="<folder>"
)

print_usage() {
    echo "Usage: $(basename "$0") [options] <file>"
    echo
    echo "Positional arguments:"
    printf "  %-17s %s\n" "file" "${DESCRIPTIONS["file"]}"
    echo
    echo "Options:"
    local option
    for option in "${OPTION_ORDER[@]}"; do
        printf "  %-17s %s\n" "$option${OPTION_ARGS[$option]:+ ${OPTION_ARGS[$option]}}" "${DESCRIPTIONS[$option]}"
    done
}

print_info() {
    echo " ▗▄▄▖▐▌   ▄ ▄▄▄▄   ▄▄▄      ▗▄▄▖▄▄▄  ▄▄▄▄  ▄▄▄▄  ▄ █ ▗▞▀▚▖ ▄▄▄ "
    echo "▐▌   ▐▌   ▄ █   █ ▀▄▄      ▐▌  █   █ █ █ █ █   █ ▄ █ ▐▛▀▀▘█    "
    echo "▐▌   ▐▛▀▚▖█ █▄▄▄▀ ▄▄▄▀     ▐▌  ▀▄▄▄▀ █   █ █▄▄▄▀ █ █ ▝▚▄▄▖█    "
    echo "▝▚▄▄▖▐▌ ▐▌█ █              ▝▚▄▄▖           █     █ █           "
    echo "            ▀                              ▀                   "
    echo ""
    echo "v1.0.0 October 2026"
    echo "The command line interface for the interpretation of"
    echo "Distributed Cyber-Physical Systems specifications in"
    echo "the Chips language."
}

fail_usage() {
    echo "Error: $1" >&2
    print_usage
    exit 1
}

require_value() {
    if [[ "$2" -lt 2 ]]; then
        fail_usage "$1 requires a value."
    fi
}

parse_args() {
    FILE=""
    STOP_FLAGS=()
    MAX_TICKS=""
    METRICS=0
    NO_RUN=0
    PLOT=0
    OUTPUT_DIR=""
    INCLUDES=()

    while [[ $# -gt 0 ]]; do
        case "$1" in
            --chips-xmi|--bip-xmi|--bip|--cpp-only)
                STOP_FLAGS+=("$1")
                shift
                ;;
            --max-ticks)
                require_value "$1" "$#"
                if ! [[ "$2" =~ ^[0-9]+$ ]]; then
                    echo "Error: --max-ticks expects a non-negative integer, got '$2'." >&2
                    exit 1
                fi
                MAX_TICKS="$2"
                shift 2
                ;;
            --metrics)
                METRICS=1
                shift
                ;;
            --include)
                require_value "$1" "$#"
                INCLUDES+=("$2")
                shift 2
                ;;
            -o)
                require_value "$1" "$#"
                OUTPUT_DIR="$2"
                shift 2
                ;;
            -h)
                print_usage
                exit 0
                ;;
            -i)
                print_info
                exit 0
                ;;
            --no-run)
                NO_RUN=1
                shift
                ;;
            --plot)
                PLOT=1
                shift
                ;;
            -*)
                fail_usage "unknown option '$1'."
                ;;
            *)
                [[ -n "$FILE" ]] && fail_usage "unexpected extra positional argument '$1'."
                FILE="$1"
                shift
                ;;
        esac
    done
}

detect_format() {
    case "$FILE" in
        *.chips.xmi) FORMAT="chips.xmi" ;;
        *.bip.xmi)   FORMAT="bip.xmi" ;;
        *.chips)     FORMAT="chips" ;;
        *.bip)       FORMAT="bip" ;;
        *.csv)       FORMAT="csv" ;;
        *)
            echo "Error: unrecognized file format for '$FILE'." >&2
            echo "Accepted formats are .chips, .chips.xmi, .bip.xmi, .bip or .csv." >&2
            exit 1
            ;;
    esac
}

require_format() {
    local flag="$1"
    shift
    local f
    for f in "$@"; do
        [[ "$FORMAT" == "$f" ]] && return 0
    done
    echo "Error: $flag does not work with .$FORMAT files." >&2
    exit 1
}

validate_args() {
    [[ -z "$FILE" ]] && fail_usage "missing required <file> argument."

    if [[ ! -f "$FILE" ]]; then
        echo "Error: '$FILE' does not exist." >&2
        exit 1
    fi

    if [[ "${#STOP_FLAGS[@]}" -gt 1 ]]; then
        echo "Error: only one of --chips-xmi, --bip-xmi, --bip and --cpp-only can be given." >&2
        exit 1
    fi
    STOP_FLAG="${STOP_FLAGS[0]:-}"

    detect_format

    case "$STOP_FLAG" in
        --chips-xmi) require_format "$STOP_FLAG" chips ;;
        --bip-xmi)   require_format "$STOP_FLAG" chips chips.xmi ;;
        --bip)       require_format "$STOP_FLAG" chips chips.xmi bip.xmi ;;
        --cpp-only)  require_format "$STOP_FLAG" chips ;;
    esac

    if [[ "${#INCLUDES[@]}" -gt 0 ]]; then
        require_format --include chips
    fi
    if [[ -n "$MAX_TICKS" ]]; then
        require_format --max-ticks chips
    fi
    if [[ "$NO_RUN" -eq 1 ]]; then
        require_format --no-run chips chips.xmi bip.xmi bip
    fi
    if [[ "$PLOT" -eq 1 ]]; then
        require_format --plot chips csv
        if [[ "$NO_RUN" -eq 1 || -n "$STOP_FLAG" ]]; then
            echo "Error: --plot needs the system to be run, it cannot be combined with ${STOP_FLAG:---no-run}." >&2
            exit 1
        fi
    fi
}
