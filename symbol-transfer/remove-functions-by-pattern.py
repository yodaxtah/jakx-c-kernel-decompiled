from ghidra.program.model.symbol import SourceType

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

def find_all_functions(pattern, function_manager):
    functions = function_manager.getFunctions(True)  # True to get functions in ascending order
    match_functions = []
    for function in functions:
        if function.getName().startswith(pattern):
            match_functions.append(function)
    return match_functions

def remove_functions_by_pattern():
    program = getCurrentProgram()
    function_manager = program.getFunctionManager()
    match_functions = find_all_functions("prt_", function_manager)
    delete_options = {
        "k": "Keep function",
        "o": "Overwrite function",
        "q": "Quit",
    }
    for func in match_functions:
        print(f"Function: {func.getName()} at address {func.getEntryPoint()}")
        address = func.getEntryPoint()
        goTo(address)
        match prompt_option(delete_options, fallback_option="q", action=": Rename function"):
            case "k":
                pass
            case "o":
                removeFunction(func)
            case "q":
                print("Quiting at offset: ", address)
                return
            case _:
                print("Unexpected option")
        if not prompt_continue():
            return

def rfbp():
    remove_functions_by_pattern()
