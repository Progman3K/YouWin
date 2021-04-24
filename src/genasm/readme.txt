Simple command-line tool that expects binary input from the console and emits Oracle x86 Assembler byte literal directive representations of the input.

It is meant to be used to take the application's compiled resource file and generate a literal bytestream the system assembler can understand.

Ex:

genasm < resource.res > fbe_asm.s 

A symbol name such as the default, _binary_resource_res will emit _binary_resource_res, and _binary_resource_res_size an int containing the size of the object.
