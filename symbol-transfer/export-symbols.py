from collections import defaultdict
import json
from jsbeautifier import beautify, default_options

# Export script (run in memory dump project)
symbols = defaultdict(list)

for symbol in currentProgram().getSymbolTable().getAllSymbols(False):
    offset = symbol.getAddress().getOffset()
    name = symbol.getName()
    symbols[offset].append(name)

with open("exported-symbols-jakx.json", "w") as f:
    options = default_options()
    options.indent_size = 2
    f.write(beautify(json.dumps(symbols), options))
    print("jsbeautifier not found")
    json.dump(symbols, f, indent=4)
    

"""
>>> from pathlib import Path
>>> Path.cwd()
"""
