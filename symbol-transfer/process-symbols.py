import ghidra
from ghidra.program.model.symbol import SymbolType
from collections import defaultdict
import json
from typing import Iterable

with open("exported-symbols-jakx-from-memory.json", "r") as f:
    symbols = json.load(f)

MIN_OFFSET = int("00100080", 16) # 1048576 == 2*20 + ...
MIN_OFFSET = int("0x14CC70", 16) # 1363056 == 2*20 + ...
MAX_OFFSET = int("00282d47", 16) # 2633031 == 2*21 + ...

pass # address = currentProgram().getAddressFactory().getDefaultAddressSpace().getAddress(offset)

def prompt_confirmation():
    input = lambda: askString("Confirmation", "Would you like to proceed? Type 'y' (yes) or 'n' (no)")
    while (cli_input := input()) not in {"y", "n"}:
        print("Please type 'y' or 'n'")
    return cli_input == "y"
    
def prompt_option(options: dict, fallback_option = None):
    input = lambda: askString("Action", f"Type on of the following options: {options.keys()}")
    try:
        while (cli_input := input()) not in options.keys():
            print("Please type a character from this list:")
            for k, v in options.items():
                print(k, v)
        return cli_input
    except Exception as e:
        return fallback_option

def process_symbols(start = None, stop = None):
    global MIN_OFFSET
    global MAX_OFFSET
    options = {
        "+": "Increase address 4 bytes",
        "-": "Decrease address 4 bytes",
        "n": "Go To Next Function",
        "p": "Go To Previous Function",
        "c": "Clear Code Bytes",
        "d": "Disassemble",
        "s": "Edit Function Signature",
        "f": "Create Function",
        "l": "Label",
        "q": "Quit",
    }
    i = 0
    count = 0
    if start == None:
        start = MIN_OFFSET
    elif type(start) == str:
        start = int(start, 16)
    if stop == None:
        stop = MAX_OFFSET
    elif type(stop) == str:
        stop = int(stop, 16)
    print(start, stop)
    while 0 <= i < len(symbols):
        offset, names = list(symbols.items())[i]
        offset = int(offset, 10)
        MIN_OFFSET = offset
        if start <= offset <= stop:
            address = currentProgram().getAddressFactory().getDefaultAddressSpace().getAddress(offset)
            goTo(address)
            if not [name for name in names if "switch" in name or "case" in name or "prt_" in name]:
                print("0x%0.2X" % offset, offset, f"[{i}]", names)
                while True:
                    address = currentProgram().getAddressFactory().getDefaultAddressSpace().getAddress(offset)
                    goTo(address)
                    match prompt_option(options, fallback_option="q"):
                        case "+":
                            offset += 4
                        case "-":
                            offset -= 4
                        case "n":
                            i += 1
                            break
                        case "p":
                            i -= 1
                            break
                        case "c":
                            print("Clear code bytes")
                            break
                            pass # clear_or_something(address)
                        case "d":
                            print("Disassembling")
                            disassemble(address)
                            break
                        case "f":
                            print("Creating a function")
                            createFunction(address, None)
                            break
                        case "s":

                            # >>> toAddr(int("001201b8", 16))
                            # <ghidra.program.model.address.GenericAddress object at 0x0000025167ACE170>
                            # >>> a = toAddr(int("001201b8", 16))
                            # >>> getFunctionAt(a)
                            # <ghidra.program.database.function.FunctionDB object at 0x0000025164DF2350>
                            # >>> f = getFunctionAt(a)
                            # >>> f == None
                            # False
                            # >>> f.getSignature()
                            # <ghidra.program.model.data.FunctionDefinitionDataType object at 0x00000251650ADC90>
                            # >>> s = f.getSignature()
                            # >>> help(s)
                            # >>> str(s)
                            # 'undefined FUN_001201b8(void)'

                            # >>> service_provider = state().getTool()
                            # >>> function_definition = CParserUtils.parseSignature(service_provider, getCurrentProgram(), str(s))
                            # >>> function_definition.getName()
                            # 'FUN_001201b8'
                            # >>> str(function_definition)
                            # 'undefined FUN_001201b8(void)'

                            break
                        case "l":
                            print("Labeling")
                            for name in names:
                                is_primary_label = "FUN" not in name and "case" not in name and "switch" not in name
                                print("name:", name, "; primary: ", is_primary_label)
                                if is_primary_label:
                                    createLabel(address, name, is_primary_label)
                                print()
                        case "q":
                            print("Quiting at offset: ", offset)
                            return
                        case _:
                            print("Unexpected option")
            else:
                print(f"doesn't match: {i} {offset} {names} {count}")
                i += 1
        else:
            i += 1
        count += 1
        if count % 1000 == 0 and count != 0:
            print("reaching max loop iteration count", count)
        if count > 8000:
            print("reached max loop iteration count", count)
            return

def ps(start = None, stop = None):
    process_symbols(start, stop)