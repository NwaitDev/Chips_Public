STEP_NAMES=()
STEP_DURATIONS=()

run_step() {
    local step_name="$1"
    local log_file="$2"
    shift 2

    echo "${YELLOW}running : $*${RESET}"
    local start_time end_time elapsed
    start_time=$(date +%s.%N)

    set +e
    "$@" 2>"$log_file"
    local status=$?
    set -e

    end_time=$(date +%s.%N)
    elapsed=$(awk -v s="$start_time" -v e="$end_time" 'BEGIN { printf "%.3f", e - s }')

    if [[ $status -ne 0 ]]; then
        echo
        echo "PIPELINE FAILED"
        echo "Step: $step_name"
        echo "Exit code: $status"
        echo "Time elapsed: ${elapsed}s"
        echo "Log file: $log_file"
        echo

        if [[ -f "$log_file" ]]; then
            echo "-------------------- BEGIN LOG --------------------"
            remap_positions < "$log_file"
            echo "--------------------- END LOG ---------------------"
        else
            echo "WARNING: Log file '$log_file' does not exist."
        fi

        echo
        exit "$status"
    fi

    STEP_NAMES+=("$step_name")
    STEP_DURATIONS+=("$elapsed")

    echo "${GREEN}Step '$step_name' completed successfully in ${elapsed}s.${RESET}"
}

in_dir() {
    local dir="$1"
    shift
    (cd -- "$dir" && "$@")
}

with_spinner() {
    local trace_file="$1"
    shift
    "$@" > "$trace_file" &
    local pid=$!
    trap 'kill "$pid" 2>/dev/null' INT TERM
    if [[ -t 1 ]]; then
        local frames='|/-\' i=0 start=$SECONDS
        while kill -0 "$pid" 2>/dev/null; do
            printf '\r%s simulation running (%ss)' "${frames:i++%4:1}" "$((SECONDS - start))"
            sleep 0.1
        done
        printf '\r\033[K'
    fi
    wait "$pid"
    local status=$?
    trap - INT TERM
    return "$status"
}
