process_probes() {
    local probe_file="$1"
    local stem
    stem="$(basename -- "$probe_file" .csv)"
    stem="${stem%.probe}"
    local probe_table="$OUTPUT_DIR/$stem.table.csv"
    run_step \
        "Probes -> table" \
        "$OUTPUT_DIR/Probe2TableDebug.log" \
        python3 "$PROBE2TABLE" "$probe_file" -o "$probe_table"
    echo "Probe table: $probe_table"

    if [[ "$PLOT" -eq 1 ]]; then
        run_step \
            "Probes -> plots" \
            "$OUTPUT_DIR/Probe2PlotDebug.log" \
            python3 "$PROBE2PLOT" "$probe_file" -o "$OUTPUT_DIR/probes.pdf"
        echo "Probe plots: $OUTPUT_DIR/probes.pdf"
    fi
}
