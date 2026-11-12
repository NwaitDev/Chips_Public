absolute_path() {
    echo "$(cd -- "$(dirname -- "$1")" && pwd)/$(basename -- "$1")"
}

resolve_include() {
    local name="$1"
    if [[ -f "$name" ]]; then
        echo "$name"
    elif [[ -f "$LIBS_DIR/$name" ]]; then
        echo "$LIBS_DIR/$name"
    elif [[ -f "$LIBS_DIR/$name.chips" ]]; then
        echo "$LIBS_DIR/$name.chips"
    else
        return 1
    fi
}

resolve_includes() {
    local i include
    for i in "${!INCLUDES[@]}"; do
        if ! include="$(resolve_include "${INCLUDES[$i]}")"; then
            echo "Error: included file '${INCLUDES[$i]}' not found (searched as a path and in '$LIBS_DIR')." >&2
            exit 1
        fi
        INCLUDES[$i]="$include"
        if sed -e 's://.*$::' -- "$include" | grep -qE '(^|[^[:alnum:]_])(system|SYSTEM)[[:space:]]*(\{|$)'; then
            echo "Error: included file '$include' must not contain a system section." >&2
            exit 1
        fi
    done
}

merge_sources() {
    CHIPS_SOURCE="$FILE"
    SOURCE_MAP=""
    [[ "${#INCLUDES[@]}" -eq 0 ]] && return 0

    local merged_dir="$OUTPUT_DIR/merged"
    mkdir -p "$merged_dir"
    CHIPS_SOURCE="$merged_dir/$(basename -- "$FILE")"
    SOURCE_MAP="$CHIPS_SOURCE.map"
    : > "$CHIPS_SOURCE"
    : > "$SOURCE_MAP"
    local next_line=1 part
    for part in "${INCLUDES[@]}" "$FILE"; do
        part="$(absolute_path "$part")"
        printf '%s\t%s\n' "$next_line" "$part" >> "$SOURCE_MAP"
        cat -- "$part" >> "$CHIPS_SOURCE"
        if [[ -s "$part" && "$(tail -c 1 -- "$part" | od -An -c | tr -d ' ')" != '\n' ]]; then
            echo >> "$CHIPS_SOURCE"
        fi
        next_line=$(( $(wc -l < "$CHIPS_SOURCE") + 1 ))
    done
}

remap_positions() {
    if [[ -z "${SOURCE_MAP:-}" ]]; then
        cat
        return
    fi
    awk -v map="$SOURCE_MAP" -v merged="$CHIPS_SOURCE" '
        BEGIN {
            n = 0
            while ((getline entry < map) > 0) {
                split(entry, parts, "\t")
                n++
                first[n] = parts[1] + 0
                path[n] = parts[2]
            }
        }
        function locate(line,    i, k) {
            k = 0
            for (i = 1; i <= n; i++)
                if (first[i] <= line)
                    k = i
            return k
        }
        function position(line, column,    k) {
            k = locate(line)
            if (k == 0)
                return merged ":" line ":" column
            return path[k] ":" (line - first[k] + 1) ":" column
        }
        {
            out = ""
            rest = $0
            while (1) {
                if (match(rest, /line [0-9]+(, column |:)[0-9]+/)) {
                    token = substr(rest, RSTART, RLENGTH)
                    split(token, f, /[^0-9]+/)
                    out = out substr(rest, 1, RSTART - 1) position(f[2] + 0, f[3] + 0)
                    rest = substr(rest, RSTART + RLENGTH)
                } else if ((i = index(rest, merged ":")) > 0 && match(substr(rest, i + length(merged) + 1), /^[0-9]+:[0-9]+/)) {
                    token = substr(rest, i + length(merged) + 1, RLENGTH)
                    split(token, f, ":")
                    out = out substr(rest, 1, i - 1) position(f[1] + 0, f[2] + 0)
                    rest = substr(rest, i + length(merged) + 1 + RLENGTH)
                } else
                    break
            }
            print out rest
        }'
}
