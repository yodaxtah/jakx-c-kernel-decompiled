import json
import re

def run():
    function_references = {}
    program = getCurrentProgram()
    function_manager = program.getFunctionManager()
    reference_manager = program.getReferenceManager()
    functions = function_manager.getFunctions(True)
    pattern = re.compile(r'FUN_........')
    for function in functions:
        if pattern.search(function.getName()):
            references = []
            for ref in reference_manager.getReferencesTo(function.getEntryPoint()):
                from_function = function_manager.getFunctionContaining(ref.getFromAddress())
                if from_function:
                    references.append(from_function.getName())
            function_references[function.getName()] = references
    with open("function_references.json", "w") as f:
        json.dump(function_references, f, indent=2)
    print("JSON file 'function_references.json' has been created.")

run()

Traceback (most recent call last):
  File "C:\Users\User\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
    more_input_needed = _jepeval(line)
  File "C:\Users\User\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 49, in _jepeval
    exec(compile(line, "<string>", "single"), globals(), globals())
    ~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "<string>", line 1, in <module>
  File "<string>", line 10, in run
AttributeError: 'FunctionDB' object has no attribute 'getReferences'