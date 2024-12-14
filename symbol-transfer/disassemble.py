import ghidra
from ghidra.program.model.symbol import SymbolType

def prompt_confirmation():
    input = lambda: askString("Confirmation", "Would you like to proceed? Type 'y' (yes) or 'n' (no)")
    while (cli_input := input()) not in {"y", "n"}:
        print("Please type 'y' or 'n'")
    return cli_input == "y"

symbol_table = currentProgram().getSymbolTable()
for symbol in symbol_table.getAllSymbols(False):
    if symbol.getSymbolType() == SymbolType.LABEL: # [SymbolType.FUNCTION, SymbolType.LABEL]:
        address = symbol.getAddress()
        if getInstructionAt(address) is None and "switch" not in name:
            goTo(address) # goTo(toAddr(int("00113d90", 16)))
            print(f"Disassemble symbol {symbol.getName()} at {address}?")
            execute_dissambler = prompt_confirmation()
            if execute_dissambler:
                disassemble(address) # print(address, address.getOffset())
