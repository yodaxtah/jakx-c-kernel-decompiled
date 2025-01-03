import json
from ghidra.app.cmd.function import ApplyFunctionSignatureCmd
from ghidra.app.util.cparser.C import CParserUtils
from ghidra.program.model.symbol import SourceType

MIN_OFFSET = int("00100080", 16) # 1048576 == 2*20 + ...
MIN_OFFSET = int("00108948", 16) # 1363056 == 2*20 + ...
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

def import_function_signatures(start = None, stop = None):
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
    service_provider = state().getTool()
    program = getCurrentProgram()
    with open("function-signatures-from-memory.json", "r") as f:
        signatures = json.load(f)
    rename_options = {
        "k": "Keep function name",
        "o": "Overwrite function name",
        "q": "Quit",
    }
    sign_options = {
        "k": "Keep function signature",
        "o": "Overwrite function signature",
        "q": "Quit",
    }
    for offset_string, data in signatures.items():
        offset = int(offset_string)
        address = toAddr(offset) # func.getEntryPoint()
        func = getFunctionAt(address)
        signature_string = data["signature"]
        function_name = data["name"]
        if start <= offset <= stop:
            print(offset, address, signature_string, None if func == None else str(func.getSignature()))
            goTo(address)
            signature = CParserUtils.parseSignature(service_provider, program, signature_string)
            changes = False
            if func is not None:
                if function_name != func.getName():
                    match prompt_option(rename_options, fallback_option="q", action=": Rename function"):
                        case "k":
                            if signature_string.count(function_name) == 1:
                                signature_string = signature_string.replace(function_name, func.getName())
                            print(signature_string, str(func.getSignature()))
                        case "o":
                            func.setName(function_name, SourceType.USER_DEFINED)
                            changes = True
                        case "q":
                            print("Quiting at offset: ", offset)
                            return
                        case _:
                            print("Unexpected option")
                if signature_string != str(func.getSignature()):
                    match prompt_option(rename_options, fallback_option="q", action=": Sign function"):
                        case "k":
                            pass
                        case "o":
                            cmd = ApplyFunctionSignatureCmd(address, signature, SourceType.USER_DEFINED) # SourceType.IMPORTED
                            if cmd.applyTo(program):
                                changes = True
                                print(f"Applied signature to function at {address}")
                            else:
                                print(f"Failed to apply signature at {address}")
                        case "q":
                            print("Quiting at offset: ", offset)
                            return
                        case _:
                            print("Unexpected option")
                if changes and not prompt_continue():
                    return
            else:
                print(f"No function found at {address}")
            count += 1
            if count > MAX_COUNT:
                return

def ifs(start = None, stop = None):
    import_function_signatures(start, stop)

# Run the script
import_function_signatures()