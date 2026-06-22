import re

def fix_mips_file(input_file, output_file):
    with open(input_file, 'r') as f:
        lines = f.readlines()

    # 1. Map absolute addresses (from comments) to line numbers
    # Matches lines starting with: /* 004003dc */
    addr_pattern = re.compile(r'^\s*/\*\s+([0-9a-fA-F]+)\s+\*/')

    addr_to_line = {}
    for i, line in enumerate(lines):
        match = addr_pattern.match(line)
        if match:
            # Convert hex string to integer to handle "004003dc" vs "4003dc"
            addr_val = int(match.group(1), 16)
            addr_to_line[addr_val] = i

    # 2. Find branch/jump instructions and replace hex targets with labels
    # Matches: bne $v0, $at, 0x4003dc
    branch_pattern = re.compile(r'\b(b\w*|j|jal)\s+([^#]*)(0x[0-9a-fA-F]+)')

    labels_to_create = set()
    new_lines = list(lines)
    count = 0

    for i, line in enumerate(lines):
        match = branch_pattern.search(line)
        if match:
            _, _, hex_target = match.groups()
            try:
                # Convert target to int for comparison
                target_val = int(hex_target, 16)

                if target_val in addr_to_line:
                    # Generate a consistent label name, e.g., lbl_4003dc
                    label_name = f"lbl_{target_val:x}"
                    labels_to_create.add(target_val)

                    # Replace the hex string in the line with the label name
                    new_lines[i] = line.replace(hex_target, label_name)
                    count += 1
            except ValueError:
                continue

    # 3. Insert the label definitions at the target lines
    for addr_val in labels_to_create:
        idx = addr_to_line[addr_val]
        label_name = f"lbl_{addr_val:x}"

        # Prepend label to the line if it isn't there already
        # Result: lbl_4003dc: /* 004003dc */ sw ...
        if not new_lines[idx].strip().startswith(label_name + ":"):
            new_lines[idx] = f"{label_name}: {new_lines[idx]}"

    with open(output_file, 'w') as f:
        f.writelines(new_lines)

    print(f"Fixed {count} instructions. Created {len(labels_to_create)} labels. Saved to {output_file}")

# Run the fix
fix_mips_file('gview_disasm.s', 'gview_fixed.s')
