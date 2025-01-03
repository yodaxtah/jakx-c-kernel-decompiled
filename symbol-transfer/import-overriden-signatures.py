import json
from ghidra.app.cmd.function import ApplyFunctionSignatureCmd
from ghidra.app.util.cparser.C import CParserUtils
from ghidra.program.model.pcode import HighFunctionDBUtil
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

def import_overriden_signatures(start = None, stop = None):
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
    service_provider = state().getTool()
    function_manager = program.getFunctionManager()
    with open("function_signature_overrides.json", "r") as f:
        functions = json.load(f)
    signature_options = {
        "k": "Keep signature",
        "o": "Overwrite signature",
        "q": "Quit",
    }
    for function_data in functions:
        function_name = function_data["name"]
        function_address = toAddr(function_data["entry_point"])
        function = function_manager.getFunctionAt(function_address)
        for override_data in function_data["overrides"]:
            call_site_address = toAddr(override_data["call_site_address"]) # : "0012d11c",
            override_function_name = override_data["function_name"] # ignored
            override_function_address = toAddr(override_data["function_address"])
            override_function = function_manager.getFunctionAt(override_function_address)
            function_signature_string = override_data["signature"] # : "int sprintf(char * __s, char * __format, ...)",
            override_signature_string = override_data["override"] # : "void __stdcall dt_68f3f722(char * str, const_char * format, const_char * version)"
            override_signature = CParserUtils.parseSignature(service_provider, program, override_signature_string)
            goTo(call_site_address)
            print(address, override_function_name, function_signature_string, str(override_signature))
            match prompt_option(signature_options, fallback_option="q"):
                case "k":
                    continue
                case "o":
                    try:
                        transaction = program.startTransaction("Apply Function Signature Override")
                        HighFunctionDBUtil.writeOverride(override_function, call_site_address, override_signature)
                        print("Function signature override applied successfully.")
                    except Exception as e:
                        print(f"Error applying function signature override: {str(e)}")
                    finally:
                        program.endTransaction(transaction, True)
                    if not prompt_continue():
                        return
                case "s":
                    continue
                case "q":
                    print("Quiting at offset: ", str(call_site_address))
                    return

def ios():
    import_overriden_signatures()