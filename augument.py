def parse_mapping_file(file_path):
    """
    Reads a file and parses its content into a dictionary.
    Each line in the file should be in the format: key : value.
    """
    with open(file_path, "r") as file:
        data = file.read()

    mapping = {}
    for line in data.strip().split("\n"):
        key, value = line.split(" : ")
        mapping[key.strip()] = int(value.strip())
    
    return mapping


def read_source_code(file_path):
    """
    Reads a source code file and returns a dictionary mapping
    line numbers to their corresponding statements.
    """
    with open(file_path, "r") as source_code:
        code_lines = source_code.readlines()

    line_mapping = {}
    for i, line in enumerate(code_lines, start=1):
        line_mapping[i] = line.strip()  # Strip to remove leading/trailing whitespace
    
    return line_mapping


def process_mapping_and_code(mapping, line_mapping):
    """
    Processes the mapping and source code line mapping.
    If the secondary key in the mapping matches any statement number
    in the line mapping, appends ";free(&<varName>);" to the statement.
    """
    updated_lines = {}
    for key, value in mapping.items():
        if value in line_mapping:
            updated_lines[value] = f"{line_mapping[value]} free(&{key});"
        else:
            updated_lines[value] = line_mapping.get(value, "")
    return updated_lines


def write_updated_code_to_file(updated_lines, original_file_path):
    """
    Writes all lines (updated and non-updated) to a new .c file.
    The new file is named sweeped<original_file_name>.c.
    """
    import os

    # Extract the original file name without extension
    original_file_name = os.path.splitext(os.path.basename(original_file_path))[0]
    new_file_name = f"sweeped{original_file_name}.c"
    new_file_path = os.path.join(os.path.dirname(original_file_path), new_file_name)

    # Read the original file to preserve all lines
    with open(original_file_path, "r") as original_file:
        original_lines = original_file.readlines()

    # Write all lines to the new file, applying updates where necessary
    with open(new_file_path, "w") as new_file:
        for line_num, line in enumerate(original_lines, start=1):
            if line_num in updated_lines:
                new_file.write(updated_lines[line_num] + "\n")  # Write updated line
            else:
                new_file.write(line)  # Write original line
    
    print(f"Updated code written to: {new_file_path}")


def main():
    # Parse the mapping file
    mapping = parse_mapping_file("testData/parse.txt")

    # Read and process the source code file
    source_file_path = "testData/test.c"
    line_mapping = read_source_code(source_file_path)

    # Process the mapping and source code to apply modifications
    updated_lines = process_mapping_and_code(mapping, line_mapping)

    # Write the updated lines to a new .c file
    write_updated_code_to_file(updated_lines, source_file_path)


if __name__ == "__main__":
    main()
    
