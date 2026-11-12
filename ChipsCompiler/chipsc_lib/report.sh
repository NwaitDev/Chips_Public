print_timing_summary() {
    if [[ "${#STEP_NAMES[@]}" -eq 0 ]]; then
        return
    fi

    local total=0
    local i
    for i in "${!STEP_NAMES[@]}"; do
        printf "  %-30s %ss\n" "${STEP_NAMES[$i]}" "${STEP_DURATIONS[$i]}"
        total=$(awk -v t="$total" -v d="${STEP_DURATIONS[$i]}" 'BEGIN { printf "%.3f", t + d }')
    done
    echo "----------------------------------------------------------------"
    printf "  %-30s %ss\n" "Total" "$total"
}

count_instances() {
    awk -v root="$2" '
        function components(type,    total, i, n, parts) {
            if (type in memo_components)
                return memo_components[type]
            if (!(type in compound))
                return 1
            total = 0
            n = split(children[type], parts, " ")
            for (i = 1; i <= n; i++)
                total += components(parts[i])
            memo_components[type] = total
            return total
        }
        function connectors(type,    total, i, n, parts) {
            if (type in memo_connectors)
                return memo_connectors[type]
            if (!(type in compound))
                return 0
            total = own_connectors[type]
            n = split(children[type], parts, " ")
            for (i = 1; i <= n; i++)
                total += connectors(parts[i])
            memo_connectors[type] = total
            return total
        }
        {
            sub(/\/\/.*/, "")
        }
        $1 == "compound" && $2 == "type" {
            current = $3
            sub(/\(.*/, "", current)
            compound[current] = 1
            children[current] = ""
            own_connectors[current] = 0
            next
        }
        current != "" && $1 == "end" {
            current = ""
            next
        }
        current != "" && $1 == "component" {
            children[current] = children[current] " " $2
            next
        }
        current != "" && $1 == "connector" && $2 != "type" {
            own_connectors[current]++
            next
        }
        END {
            if (!(root in compound)) {
                print 0, 0
                exit
            }
            print components(root), connectors(root)
        }' "$1"
}

print_model_statistics() {
    echo
    if [[ "$FORMAT" == "chips" ]]; then
        printf "  %-30s %s\n" "Lines of the chips model" "$(wc -l < "$CHIPS_SOURCE")"
    fi
    if [[ -n "${BIP_FILE:-}" && -f "$BIP_FILE" ]]; then
        local components connectors
        read -r components connectors < <(count_instances "$BIP_FILE" "$ROOT_COMPONENT")
        printf "  %-30s %s\n" "Components (instances)" "$components"
        printf "  %-30s %s\n" "Connectors (instances)" "$connectors"
        printf "  %-30s %s\n" "Lines of the bip model" "$(wc -l < "$BIP_FILE")"
    fi
}

print_report() {
    if [[ "$METRICS" -eq 1 ]]; then
        print_timing_summary
        print_model_statistics
    fi
}
