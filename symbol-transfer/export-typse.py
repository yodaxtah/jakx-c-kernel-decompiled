import json
from ghidra.program.model.symbol import SymbolType
from ghidra.program.model.listing import Data


ALL_SYMBOLS = True

MIN_OFFSET = int("00100080", 16) # 1048576 == 2*20 + ...
MIN_OFFSET = int("00108948", 16) # 1363056 == 2*20 + ...
MAX_OFFSET = int("00282d47", 16) # 2633031 == 2*21 + ...

# seperately for .data

MIN_OFFSET = int("00282d80", 16) # 1048576 == 2*20 + ...
MAX_OFFSET = int("002d2b2f", 16) # 2633031 == 2*21 + ...

def prompt_continue():
    input = lambda: askString("Continue?", "Would you like to proceed to the next symbol? Type 'y' (yes) or 'q' (quit).")
    while (cli_input := input()) not in {"y", "q"}:
        print("Please type 'y' or 'q'")
    return cli_input == "y"

def export_global_types():
    global ALL_SYMBOLS
    program = getCurrentProgram()
    symbol_table = program.getSymbolTable()
    data_type_manager = program.getDataTypeManager()
    global_vars = {}
    nones = 0
    for symbol in symbol_table.getAllSymbols(ALL_SYMBOLS):
        if symbol.getSymbolType() in [SymbolType.LABEL] or True: # [SymbolType.GLOBAL_VAR, SymbolType.GLOBAL, SymbolType.LOCAL_VAR]:
            address = symbol.getAddress()
            data = getDataAt(address)
            offset = address.getOffset()
            if MIN_OFFSET <= offset <= MAX_OFFSET:
                if data is None:
                    # print(offset, symbol.getName())
                    nones += 1
                if int("0027d478", 16) <= offset <= int("0027d498", 16):
                    print(offset, data == None)
                if data is not None:
                    name = symbol.getName()
                    data_type = data.getDataType()
                    type_name = data_type.getName()
                    global_vars[address.getOffset()] = {
                        "name": name,
                        "type": type_name
                    }
    with open("exported-types-jakx-tst.json", "w") as f:
        json.dump(global_vars, f, indent=4)
    print(f"Exported {len(global_vars)} global variables.")
    print(nones)

export_global_types()


# Generated, don't use!

def export_global_types_2():
    program = getCurrentProgram()
    memory = program.getMemory()
    listing = program.getListing()
    global_vars = {}
    for block in memory.getBlocks():
        if block.isInitialized():
            addr = block.getStart()
            while addr < block.getEnd():
                data = listing.getDataAt(addr)
                if data is not None:
                    name = data.getFieldName()
                    if name is None or name == "":
                        symbol = getSymbolAt(addr)
                        if symbol is not None:
                            name = symbol.getName()
                    if name is not None and name != "":
                        data_type = data.getDataType()
                        type_name = data_type.getName()
                        global_vars[addr.getOffset()] = {
                            "name": name,
                            "type": type_name
                        }
                    addr = addr.add(data.getLength())
                else:
                    addr = addr.next()
    with open("exported-types-jakx-2.json", "w") as f:
        json.dump(global_vars, f, indent=4)
    print(f"Exported {len(global_vars)} global variables.")

export_global_types_2()

def export_global_types_3():
    global ALL_SYMBOLS
    program = getCurrentProgram()
    symbol_table = program.getSymbolTable()
    listing = program.getListing()
    global_vars = {}

    for symbol in symbol_table.getAllSymbols(ALL_SYMBOLS):
        if symbol.getSymbolType() in [SymbolType.LABEL]:
            address = symbol.getAddress()
            goTo(address)
            if listing.getFunctionContaining(address):
                continue # Skip if the address belongs to a function
            data = getDataAt(address)
            if data is None: # If no data exists, try to create string data
                try:
                    if prompt_continue():
                        return
                    data = DataUtilities.createData(program, address, StringDataType(), -1, False, DataUtilities.ClearDataMode.CLEAR_ALL_CONFLICTS)
                    if not prompt_continue():
                        return
                except Exception as e:
                    print(f"Failed to create data at {address}: {e}")
                    continue
            if data is not None: # Process the data if it exists
                name = symbol.getName()
                data_type = data.getDataType()
                type_name = data_type.getName()
                global_vars[address.getOffset()] = {
                    "name": name,
                    "type": type_name
                }
