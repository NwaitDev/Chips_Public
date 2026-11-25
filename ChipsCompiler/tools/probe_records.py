import csv
import os
import sys

INDEX_COLUMNS = {"file", "instance", "location", "expression"}
LEGACY_COLUMNS = {"instance", "ticks", "location", "expression", "value"}


def index_path(path):
    return os.path.join(path, "index.csv") if os.path.isdir(path) else path


def join_value(fields):
    return fields[0] if len(fields) == 1 else "[" + ",".join(fields) + "]"


def read_probe_file(path, entry):
    records = []
    with open(path, newline="") as stream:
        for row in csv.reader(stream):
            if not row:
                continue
            records.append({
                "instance": entry["instance"],
                "ticks": row[0],
                "location": entry["location"],
                "expression": entry["expression"],
                "value": join_value([field.strip() for field in row[1:]]),
            })
    return records


def read_records(path):
    path = index_path(path)
    with open(path, newline="") as stream:
        reader = csv.DictReader(stream)
        columns = set(reader.fieldnames or [])
        if LEGACY_COLUMNS.issubset(columns):
            return list(reader)
        if not INDEX_COLUMNS.issubset(columns):
            sys.exit(f"error: '{path}' is not a probe index (expected columns: file,instance,location,expression)")
        entries = list(reader)
    folder = os.path.dirname(path)
    records = []
    for entry in entries:
        probe_file = os.path.join(folder, entry["file"])
        if not os.path.isfile(probe_file):
            print(f"warning: '{probe_file}' listed in '{path}' is missing", file=sys.stderr)
            continue
        records.extend(read_probe_file(probe_file, entry))
    return records
