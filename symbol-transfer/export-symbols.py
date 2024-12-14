from collections import defaultdict
import json

# Export script (run in memory dump project)
symbols = defaultdict(list)

for symbol in currentProgram().getSymbolTable().getAllSymbols(False):
    offset = symbol.getAddress().getOffset()
    name = symbol.getName()
    symbols[offset].append(name)

with open("exported-symbols-jakx.json", "w") as f:
    json.dump(symbols, f)

"""
>>> from pathlib import Path
>>> Path.cwd()
"""
