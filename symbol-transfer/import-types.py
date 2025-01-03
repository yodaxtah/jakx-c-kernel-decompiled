import json
from ghidra.app.util.cparser.C import CParserUtils
from ghidra.program.model.symbol import SourceType
from ghidra.program.model.data import CategoryPath
from ghidra.program.model.data import DataUtilities

MIN_OFFSET = int("00100080", 16) # 1048576 == 2*20 + ...
MIN_OFFSET = int("001dad30", 16) # 1363056 == 2*20 + ...
MAX_OFFSET = int("002d2b2f", 16) # 2633031 == 2*21 + ...
MAX_COUNT = 1000

# seperately for .data

MIN_OFFSET = int("00282d80", 16) # 1048576 == 2*20 + ...
MAX_OFFSET = int("002d2b2f", 16) # 2633031 == 2*21 + ...

def prompt_option(options: dict, fallback_option = None, action: str = ""):
    input = lambda: askString("Action" + action, f"Type on of the following options: {options.keys()}")
    try:
        while (cli_input := input()) not in options.keys():
            print("Please type a character from this list:")
            for k, v in options.items():
                print(k, v)
        return cli_input
    except Exception as e:
        return fallback_option

def prompt_continue():
    input = lambda: askString("Continue?", "Would you like to proceed to the next function? Type 'y' (yes) or 'q' (quit).")
    while (cli_input := input()) not in {"y", "q"}:
        print("Please type 'y' or 'q'")
    return cli_input == "y"

def import_symbol_types(start = None, stop = None):
    global MIN_OFFSET
    global MAX_OFFSET
    global MAX_COUNT
    if start == None:
        start = MIN_OFFSET
    elif type(start) == str:
        start = int(start, 16)
    if stop == None:
        stop = MAX_OFFSET
    elif type(stop) == str:
        stop = int(stop, 16)
    count = 0
    print(start, stop)
    program = getCurrentProgram()
    symbol_table = program.getSymbolTable()
    data_type_manager = program.getDataTypeManager()
    with open("exported-types-jakx-tst.json", "r") as f:
        types = json.load(f)
    rename_options = {
        "k": "Keep function name",
        "o": "Overwrite function name",
        "q": "Quit",
    }
    type_options = {
        "k": "Keep symbol type",
        "o": "Overwrite symbol type",
        "q": "Quit",
    }
    for offset_string, data in types.items():
        offset = int(offset_string)
        address = toAddr(offset) # func.getEntryPoint()
        symbols = symbol_table.getSymbols(address)
        symbol_type_string = data["type"]
        symbol_name = data["name"]
        if start <= offset <= stop and "switch" not in symbol_name and "case" not in symbol_name:    
            # if (length := len(symbols)) > 1:
            #     print(f"unexpected number of symbols: {length}"m)
            if len(symbols) != 1:
                print(f"symbols not 1 at {address}")
                continue
            print(offset, address, symbol_name, symbols[0].getName(), symbol_type_string, d.getDataType().getName() if (d := getDataAt(address)) else None)
            goTo(address)
            symbol = symbols[0]
            data_type = data_type_manager.getDataType(CategoryPath("/Memory"), symbol_type_string) or data_type_manager.getDataType(CategoryPath("/"), symbol_type_string)
            changes = False
            if len(symbols) == 1 and data_type is not None:
                if symbol_name != symbol.getName():
                    match prompt_option(rename_options, fallback_option="q", action=": Rename symbol"):
                        case "k":
                            print(symbol_name, symbol.getName())
                        case "o":
                            symbol.setName(symbol_name, SourceType.USER_DEFINED)
                            changes = True
                        case "q":
                            print("Quiting at offset: ", offset)
                            return
                        case _:
                            print("Unexpected option")
                symbol_data = getDataAt(address)
                if symbol_data is None or symbol_type_string != symbol_data.getDataType().getName():
                    match prompt_option(type_options, fallback_option="q", action=": Type symbols"):
                        case "k":
                            pass
                        case "o":
                            length = 0 # data_type.getLength()
                            DataUtilities.createData(program, address, data_type, length, False, DataUtilities.ClearDataMode.CLEAR_ALL_CONFLICT_DATA)
                            changes = True
                        case "q":
                            print("Quiting at offset: ", offset)
                            return
                        case _:
                            print("Unexpected option")
                if changes and not prompt_continue():
                    return
            else:
                print(f"No symbol found at {address}")
            count += 1
            MIN_OFFSET = offset
            if count > MAX_COUNT:
                return

def ifs(start = None, stop = None):
    import_symbol_types(start, stop)

# Run the script
import_symbol_types()