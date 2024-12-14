from collections import defaultdict
import json
# Import script (run in decrypted ELF project)
with open("exported-symbols-jakx.json", "r") as f:
    symbols = json.load(f)

count = 0
for offset, names in symbols.items():
    offset = int(offset, 10)
    if 0x100000 <= offset <= 0xffffffff:
        print("offset:", offset, "0x%0.2X" % offset, end="; ")
        # if count == 0:
        #     break
        address = currentProgram().getAddressFactory().getDefaultAddressSpace().getAddress(offset)
        for name in names:
            is_primary_label = "FUN" not in name and "case" not in name and "switch" not in name
            print("name:", name, is_primary_label, end="; ")
            if is_primary_label:
                count += 1
                createLabel(address, name, is_primary_label)
        print()
# https://docs.roblab.la/ghidra/9.0/api/ghidra/program/flatapi/FlatProgramAPI.html
# #createLabel(ghidra.program.model.address.Address,java.lang.String,boolean)