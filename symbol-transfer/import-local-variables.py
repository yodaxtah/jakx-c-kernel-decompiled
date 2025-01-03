import json
from ghidra.app.cmd.function import ApplyFunctionSignatureCmd
from ghidra.app.util.cparser.C import CParserUtils
from ghidra.program.model.symbol import SourceType

MIN_OFFSET = int("00100080", 16) # 1048576 == 2*20 + ...
MAX_OFFSET = int("00282d47", 16) # 2633031 == 2*21 + ...
MAX_COUNT = 1000

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

def export_function_variable(variable: "LocalVariableDB"):
    return {
        "name": variable.getName(),
        "data_type": str(variable.getDataType()),
        "first_use": str(variable.getFirstUseOffset()),
        "min_address": str(variable.getMinAddress()),
        "length": str(variable.getLength()),
        "storage": str(variable.getVariableStorage()),
    }

def import_local_variables(start = None, stop = None):
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
    function_manager = program.getFunctionManager()
    data_type_manager = program.getDataTypeManager()
    with open("function_variables.json", "r") as f:
        functions = json.load(f)
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
    function_options = {
        "f": "Create Function",
        "l": "Remove Label",
        "s": "Skip label",
        "q": "Quit",
    }
    for function_data in functions:
        address_string = function_data["entry_point"]
        offset = int(address_string, 16)
        address = toAddr(offset) # func.getEntryPoint()
        function = function_manager.getFunctionAt(address)
        function_name = function_data["name"]
        imported_function_variables = list(function_data["variables"])
        if start <= offset <= stop:
            print(offset, address, function_name, function != None)
            goTo(address)
            if function == None:
                match prompt_option(function_options, fallback_option="q"):
                    case "f":
                        print("Creating a function")
                        function = createFunction(address, None)
                    case "l":
                        print("Remove label")
                        for name in names:
                            print("Ignoring input")
                            break
                            pass # DeleteLabelCmd(address,
                            pass # createLabel(address, name, is_primary_label)
                    case "s":
                        continue
                    case "q":
                        print("Quiting at offset: ", offset)
                        return
            function_variables = [export_function_variable(v) for v in function.getLocalVariables()]
            if imported_function_variables == function_variables:
                print("local function variables match!")
            elif len(imported_function_variables) == len(function_variables):
                for i in range(len(function_variables)):
                    imported_variable_data = imported_function_variables[i]
                    variable_data = function_variables[i]
                    variable_name = variable_data["name"]
                    variable_data_type = variable_data["data_type"]
                    variable_storage = variable_data["storage"]
                    if variable_data == imported_variable_data:
                        print("variable matches")
                    print(variable_data) # print(json.dumps(variable_data, indent=2))
                    print(imported_variable_data)
                    if not prompt_continue():
                        return
            else:
                print("Current")
                for v in function_variables:
                    print(v) # print(json.dumps(imported_function_variables, indent=2))
                print("Imported")
                for v in imported_function_variables:
                    print(v) # print(json.dumps(function_variables, indent=2))
                if not prompt_continue():
                    return
            MIN_OFFSET = offset





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

def ilv(start = None, stop = None):
    import_local_variables(start, stop)
