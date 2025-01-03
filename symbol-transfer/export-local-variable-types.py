from ghidra.program.model.listing import Function
import json

MIN_OFFSET = int("00100080", 16) # 1048576 == 2*20 + ...
MAX_OFFSET = int("002d2b2f", 16) # 2633031 == 2*21 + ...

def export_function_variable(variable: "LocalVariableDB"):
    return {
        "name": variable.getName(),
        "data_type": str(variable.getDataType()),
        "first_use": str(variable.getFirstUseOffset()),
        "min_address": str(variable.getMinAddress()),
        "length": str(variable.getLength()),
        "storage": str(variable.getVariableStorage()),
    }

def export_function_variables():
    current_program = getCurrentProgram()
    function_manager = current_program.getFunctionManager()
    functions = function_manager.getFunctions(True)
    data = []
    for function in functions:
        if MIN_OFFSET <= function.getEntryPoint().getOffset() <= MAX_OFFSET:
            func_data = {
                "name": function.getName(),
                "entry_point": str(function.getEntryPoint()),
                "variables": []
            }
            variables = function.getLocalVariables()
            for var in variables:
                func_data["variables"].append(export_function_variable(var))
            data.append(func_data)
    with open("function_variables.json", "w") as f:
        json.dump(data, f, indent=4)
    print("Export complete. Saved to function_variables.json")

export_function_variables()