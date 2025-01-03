import json
from ghidra.program.model.symbol import SymbolType
from ghidra.program.model.mem import MemoryBlockType

def run_script():
    program = getCurrentProgram()
    symbol_table = program.getSymbolTable()
    memory = program.getMemory()
    function_manager = program.getFunctionManager()
    
    sections = {}
    
    # Get all memory blocks
    for block in memory.getBlocks():
        if block.getType() == MemoryBlockType.DEFAULT:
            sections[block.getName()] = []
    
    # Add functions
    for function in function_manager.getFunctions(True):
        address = function.getEntryPoint()
        block = memory.getBlock(address)
        if block and block.getName() in sections:
            sections[block.getName()].append({
                "name": function.getName(),
                "address": "0x" + address.toString(),
                "type": "function"
            })
    
    # Add non-function symbols (excluding those inside functions)
    for symbol in symbol_table.getAllSymbols(True):
        if symbol.getSymbolType() == SymbolType.LABEL:
            address = symbol.getAddress()
            if not function_manager.getFunctionAt(address):  # Check if not inside a function
                block = memory.getBlock(address)
                if block and block.getName() in sections:
                    sections[block.getName()].append({
                        "name": symbol.getName(),
                        "address": "0x" + address.toString(),
                        "type": "label"
                    })
    
    # Sort sections by their start address
    sorted_sections = sorted(sections.items(), key=lambda x: memory.getBlock(x[0]).getStart().getOffset())
    
    # Create the final JSON structure
    result = {section: symbols for section, symbols in sorted_sections if symbols}
    
    # Export to JSON file
    output_file = askFile("Select output file", "Save")
    with open(output_file.getAbsolutePath(), "w") as f:
        json.dump(result, f, indent=2)
    
    print("Symbol export completed successfully.")

run_script()
