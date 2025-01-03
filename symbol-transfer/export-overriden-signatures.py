from ghidra.program.model.listing import Function
from ghidra.program.model.symbol import RefType
from ghidra.program.model.pcode import HighFunctionDBUtil
from ghidra.program.model.symbol import SymbolType
import json


MIN_OFFSET = int("00100080", 16) # 1048576 == 2*20 + ...
MAX_OFFSET = int("00282d47", 16) # 2633031 == 2*21 + ...


def extract_overrides(instructions, symbol_table, function_manager):
    overrides = []
    for instruction in instructions:
        if instruction.getFlowType().isCall():
            call_site_address = instruction.getAddress()  # Address of the function being called
            override_symbols = [s for s in symbol_table.getSymbols(call_site_address) if s.getSymbolType() == SymbolType.CODE]
            for override_symbol in override_symbols:
                called_address = instruction.getAddress(0)
                if called_address != None and (called_function := function_manager.getFunctionAt(called_address)) != None:
                    if overriden_data_type_symbol := HighFunctionDBUtil.readOverride(override_symbol):
                        called_function_signature = called_function.getSignature(True).getPrototypeString()
                        overriden_signature = str(overriden_data_type_symbol.getDataType())
                        print(str(call_site_address), called_function_signature, overriden_signature)
                        overrides.append({
                            "call_site_address": str(call_site_address),
                            "function_name": called_function.getName(),
                            "function_address": str(called_address),
                            "signature": called_function_signature,
                            "override": overriden_signature,
                        })
    return overrides

def export_function_signature_overrides():
    program = getCurrentProgram()
    function_manager = program.getFunctionManager()
    functions = function_manager.getFunctions(True)
    symbol_table = program.getSymbolTable()
    listing = program.getListing()
    data = []
    for function in functions:
        address = function.getEntryPoint() # toAddr(offset) # offset = int("00266798", 16)
        if MIN_OFFSET <= address.getOffset() <= MAX_OFFSET:
            print("FUNCTION:", function.getName())
            body = function.getBody()
            instructions = list(listing.getInstructions(body, True))
            overrides = extract_overrides(instructions, symbol_table, function_manager)
            if overrides:
                data.append({
                    "name": function.getName(),
                    "entry_point": str(address),
                    "overrides": overrides,
                })
    with open("function_signature_overrides.json", "w") as f:
        json.dump(data, f, indent=4)
    print("Export complete. Saved to function_signature_overrides.json")


def efso():
    export_function_signature_overrides()


"""

for instruction in instructions:
    flow_type = instruction.getFlowType()
    if flow_type.isCall():
        call_site_address = instruction.getAddress(0)  # Address of the function being called
        if override_symbol := symbol_table.getPrimarySymbol(call_site_address):
            override_signature = HighFunctionDBUtil.readOverride(override_symbol)
            print(str(call_site_address), override_signature, "OVERRIDEN")
        called_function = function_manager.getFunctionAt(call_site_address)
        called_function_signature = called_function.getSignature(True).getPrototypeString()
        print(str(call_site_address), called_function_signature)
                    
for instruction in instructions:
    flow_type = instruction.getFlowType()
    if flow_type.isCall():
        call_site_address = instruction.getAddress()  # Address of the function being called
        override_symbol = symbol_table.getPrimarySymbol(call_site_address)
        if override_symbol != None: # The symbol might still be a label
            called_address = instruction.getAddress(0)
            called_function = function_manager.getFunctionAt(called_address)
            if called_function != None:
                overriden_data_type_symbol = HighFunctionDBUtil.readOverride(override_symbol)
                if overriden_data_type_symbol != None:
                    called_function_signature = called_function.getSignature(True).getPrototypeString()
                    overriden_signature = str(overriden_data_type_symbol.getDataType())
                    print(str(call_site_address), called_function_signature, overriden_signature)

for instruction in instructions:
    flow_type = instruction.getFlowType()
    if flow_type.isCall():
        called_address = instruction.getAddress(0)  # Address of the function being called
        called_function = function_manager.getFunctionAt(called_address)
        override_signature = None
        if called_function:
            override_signature = called_function.getSignature(True).getPrototypeString()
            print(str(called_address), override_signature)
"""


'''
error?
>>> for instruction in instructions:
>>>     flow_type = instruction.getFlowType()
>>>     if flow_type.isCall():
>>>         call_site_address = instruction.getAddress()  # Address of the function being called
>>>         override_symbol = symbol_table.getPrimarySymbol(call_site_address)
>>>         if override_symbol != None:
>>>             called_address = instruction.getAddress(0)
>>>             called_function = function_manager.getFunctionAt(called_address)
>>>             if called_function != None:
>>>                 print(called_function.getName())
>>>                 called_function_signature = called_function.getSignature(True).getPrototypeString()
>>>                 overriden_data_type_symbol = HighFunctionDBUtil.readOverride(override_symbol)
>>>                 overriden_signature = str(overriden_data_type_symbol.getDataType())
...                 print(str(call_site_address), called_function_signature, overriden_signature)
... 
ShutdownMachine
Traceback (most recent call last):
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
    more_input_needed = _jepeval(line)
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 45, in _jepeval
    exec(compile(source, "<string>", "single"), globals(), globals())
    ~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "<string>", line 13, in <module>
AttributeError: 'NoneType' object has no attribute 'getDataType'
>>> for instruction in instructions:
>>>     flow_type = instruction.getFlowType()
>>>     if flow_type.isCall():
>>>         call_site_address = instruction.getAddress()  # Address of the function being called
>>>         override_symbol = symbol_table.getPrimarySymbol(call_site_address)
>>>         if override_symbol != None: # The symbol might still be a label
>>>             called_address = instruction.getAddress(0)
>>>             called_function = function_manager.getFunctionAt(called_address)
>>>             if called_function != None:
>>>                 overriden_data_type_symbol = HighFunctionDBUtil.readOverride(override_symbol)
>>>                 if overriden_data_type_symbol != None:
>>>                     called_function_signature = called_function.getSignature(True).getPrototypeString()
>>>                     overriden_signature = str(overriden_data_type_symbol.getDataType())
...                     print(str(call_site_address), called_function_signature, overriden_signature)
... 
00266924 int sprintf(char * __s, char * __format, ...) void __stdcall dt_b7404d73(char * str, const_char * format, const_char * , const_char * )
>>> def export_function_signature_overrides():
>>>     program = getCurrentProgram()
>>>     function_manager = program.getFunctionManager()
>>>     functions = function_manager.getFunctions(True)
>>>     symbol_table = program.getSymbolTable()
>>>     listing = program.getListing()
>>>     data = []
>>> 
>>>     for function in functions:
>>>         address = function.getEntryPoint() # toAddr(offset) # offset = int("00266798", 16)
>>>         body = function.getBody()
>>>         instructions = list(listing.getInstructions(body, True))
>>>         func_data = {
>>>             "name": function.getName(),
>>>             "entry_point": str(address),
>>>             "overrides": []
>>>         }
>>>         for instruction in instructions:
>>>             flow_type = instruction.getFlowType()
>>>             if flow_type.isCall():
>>>                 call_site_address = instruction.getAddress()  # Address of the function being called
>>>                 if override_symbol := symbol_table.getPrimarySymbol(call_site_address): # The symbol might still be a label
>>>                     called_address = instruction.getAddress(0)
>>>                     if called_function := function_manager.getFunctionAt(called_address):
>>>                         if overriden_data_type_symbol := HighFunctionDBUtil.readOverride(override_symbol):
>>>                             called_function_signature = called_function.getSignature(True).getPrototypeString()
>>>                             overriden_signature = str(overriden_data_type_symbol.getDataType())
>>>                             print(str(call_site_address), called_function_signature, overriden_signature)
>>>                             if override_signature:
>>>                                 func_data["overrides"].append({
>>>                                     "call_site_address": str(call_site_address),
>>>                                     "signature": called_function_signature,
>>>                                     "override": override_signature,
>>>                                 })
>>>         if func_data["overrides"]:
>>>             data.append(func_data)
>>>     with open("function_signature_overrides.json", "w") as f:
>>>         json.dump(data, f, indent=4)
...     print("Export complete. Saved to function_signature_overrides.json")
... 
Traceback (most recent call last):
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
    more_input_needed = _jepeval(line)
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 45, in _jepeval
    exec(compile(source, "<string>", "single"), globals(), globals())
         ~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "<string>", line 1
    for function in functions:
IndentationError: unexpected indent
>>> 
>>> def export_function_signature_overrides():
>>>     program = getCurrentProgram()
>>>     function_manager = program.getFunctionManager()
>>>     functions = function_manager.getFunctions(True)
>>>     symbol_table = program.getSymbolTable()
>>>     listing = program.getListing()
>>>     data = []
>>>     for function in functions:
>>>         address = function.getEntryPoint() # toAddr(offset) # offset = int("00266798", 16)
>>>         body = function.getBody()
>>>         instructions = list(listing.getInstructions(body, True))
>>>         func_data = {
>>>             "name": function.getName(),
>>>             "entry_point": str(address),
>>>             "overrides": []
>>>         }
>>>         for instruction in instructions:
>>>             flow_type = instruction.getFlowType()
>>>             if flow_type.isCall():
>>>                 call_site_address = instruction.getAddress()  # Address of the function being called
>>>                 if override_symbol := symbol_table.getPrimarySymbol(call_site_address): # The symbol might still be a label
>>>                     called_address = instruction.getAddress(0)
>>>                     if called_function := function_manager.getFunctionAt(called_address):
>>>                         if overriden_data_type_symbol := HighFunctionDBUtil.readOverride(override_symbol):
>>>                             called_function_signature = called_function.getSignature(True).getPrototypeString()
>>>                             overriden_signature = str(overriden_data_type_symbol.getDataType())
>>>                             print(str(call_site_address), called_function_signature, overriden_signature)
>>>                             if override_signature:
>>>                                 func_data["overrides"].append({
>>>                                     "call_site_address": str(call_site_address),
>>>                                     "signature": called_function_signature,
>>>                                     "override": override_signature,
>>>                                 })
>>>         if func_data["overrides"]:
>>>             data.append(func_data)
>>>     with open("function_signature_overrides.json", "w") as f:
>>>         json.dump(data, f, indent=4)
>>>     print("Export complete. Saved to function_signature_overrides.json")
... 
>>> export_function_signature_overrides()
Traceback (most recent call last):
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
    more_input_needed = _jepeval(line)
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 49, in _jepeval
    exec(compile(line, "<string>", "single"), globals(), globals())
    ~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "<string>", line 1, in <module>
  File "<string>", line 23, in export_function_signature_overrides
RuntimeError: java.lang.NullPointerException: Cannot invoke "ghidra.program.model.address.Address.isMemoryAddress()" because "addr" is null


'''












































def foo():
    """
    >>> offset = int("00266798", 16)
    >>> address = toAddr(offset)
    >>> program = getCurrentProgram()
    >>> function_manager = program.getFunctionManager()
    >>> goal_function = function_manager.getFunctionAt(address)
    >>> reference_manager = program.getReferenceManager()
    >>> references = reference_manager.getReferencesFrom(address)
    >>> references = list(reference_manager.getReferencesFrom(address))
    >>> len(references)
    0
    >>> function.getEntryPoint()
    Traceback (most recent call last):
    File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
        more_input_needed = _jepeval(line)
    File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 49, in _jepeval
        exec(compile(line, "<string>", "single"), globals(), globals())
        ~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    File "<string>", line 1, in <module>
    NameError: name 'function' is not defined. Did you mean: 'getFunction'?
    >>> goal_function.getEntryPoint()
    <ghidra.program.model.address.GenericAddress object at 0x000002240ABFCAC0>
    >>> address
    <ghidra.program.model.address.GenericAddress object at 0x000002240ABC2B30>
    >>> listings = program.getListings()
    Traceback (most recent call last):
    File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
        more_input_needed = _jepeval(line)
    File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 49, in _jepeval
        exec(compile(line, "<string>", "single"), globals(), globals())
        ~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    File "<string>", line 1, in <module>
    AttributeError: 'ProgramDB' object has no attribute 'getListings'. Did you mean: 'getListing'?
    >>> listings = program.getListing()
    >>> listing = program.getListing()
    >>> instructions = clisting.getInstructions(goal_function.getBody())
    Traceback (most recent call last):
    File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
        more_input_needed = _jepeval(line)
    File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 49, in _jepeval
        exec(compile(line, "<string>", "single"), globals(), globals())
        ~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    File "<string>", line 1, in <module>
    NameError: name 'clisting' is not defined. Did you mean: 'listing'?
    >>> instructions = listing.getInstructions(goal_function.getBody())
    >>> instructions = list(instructions)
    >>> len(instructions)
    941948
    >>> body = goal_function.getBody()
    >>> instructions = listing.getInstructions(body, True)
    >>> instructions = list(instructions)
    >>> len(instructions)
    >>> print("hi")
    121
    """


"""
>>> call_instructions = [c for c in instructions if c.getFlowType().isCall()]
>>> len(call_instructions)
14
>>> symbol = sym
>>> str(sym)
'prt_266924_b7404d73'
>>> symbols_ = [symbol_table.getPrimarySymbol(c.getAddress()) for c in instructions if c.getFlowType().isCall()]
>>> len(symbols_)
14
>>> [str(s) for s in symbols]
Traceback (most recent call last):
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 74, in jepeval
    more_input_needed = _jepeval(line)
  File "C:\Users\Tijl\AppData\Roaming\ghidra\ghidra_11.1_PUBLIC\Extensions\Ghidrathon\data\python\jepeval.py", line 49, in _jepeval
    exec(compile(line, "<string>", "single"), globals(), globals())
    ~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  File "<string>", line 1, in <module>
NameError: name 'symbols' is not defined. Did you mean: 'symbol'?
>>> [str(s) for s in symbols_]
['None', 'None', 'None', 'None', 'None', 'None', 'None', 'None', 'None', 'None', 'LAB_002668bc', 'None', 'prt_266924_b7404d73', 'None']
>>> [str(s) for s in symbols_ if s != None]
['LAB_002668bc', 'prt_266924_b7404d73']
>>> [str(s.getSymbolType()) for s in symbols_ if s != None]
['Label', 'Label']
"""