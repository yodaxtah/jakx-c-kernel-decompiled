import json
from ghidra.program.model.listing import Function

def export_function_signatures():
    program = getCurrentProgram()
    function_manager = program.getFunctionManager()
    functions = function_manager.getFunctions(True)
    
    signatures = {}
    
    for func in functions:
        name = func.getName()
        address = func.getEntryPoint().getOffset()
        signature = str(func.getSignature())  # Get the function signature as a string
        signatures[address] = {"name": name, "signature": signature}
    
    with open("function-signatures-from-memory.json", "w") as f:
        json.dump(signatures, f, indent=4)
    
    print(f"Exported {len(signatures)} function signatures.")

# Run the script
export_function_signatures()


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
