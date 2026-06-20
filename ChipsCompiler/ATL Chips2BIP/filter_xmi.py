"""
Removes all root children except the first one, preserving namespaces.
Usage: python3 filter_xml.py <file.xmi>
"""

import xml.etree.ElementTree as ET
import sys


def register_namespaces(file: str):
    """Parse all namespace declarations from the file and register them."""
    namespaces = dict(
        [node for _, node in ET.iterparse(file, events=["start-ns"])]
    )
    for prefix, uri in namespaces.items():
        ET.register_namespace(prefix, uri)


def main():
    if len(sys.argv) != 2:
        print("Usage: python3 filter_xml.py <file.xmi>")
        sys.exit(1)

    file = sys.argv[1]

    # Must register namespaces BEFORE parsing to avoid prefix mangling
    register_namespaces(file)

    tree = ET.parse(file)
    root = tree.getroot()

    children = list(root)
    for child in children[1:]:
        root.remove(child)

    tree.write(file, encoding="utf-8", xml_declaration=True)


if __name__ == "__main__":
    main()