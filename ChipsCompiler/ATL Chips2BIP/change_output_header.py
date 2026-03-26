# change /models/output.xmi first line to /BIP_XMI_HEADER.xmi content and adds "</xmi:XMI>" at the end of the file
import os

def change_output_header():
    with open("models/output.xmi", "r") as f:
        lines = f.readlines()

    with open("BIP_XMI_HEADER.xmi", "r") as f:
        header_lines = f.readlines()

    # Replace the first line of output.xmi with the header content
    new_lines = header_lines + lines[1:]

    # Add the closing tag at the end of the file
    new_lines.append("</xmi:XMI>\n")

    with open("models/output.xmi", "w") as f:
        f.writelines(new_lines)

if __name__ == "__main__":
    change_output_header()

