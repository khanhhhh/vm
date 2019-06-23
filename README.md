# VIRTUAL MACHINE
Personal project, greatly inspired by Java Bytecode, 

# TODO

- Design the language
	- 2 main datatypes (primitive and array)
	- primitive has size 1, located on stack (int32, float, addr)
	- array has size known at compile time, similar to c struct, used to represent user data type.
	- addr is single size data type which either points to function on code memory or vector on data (heap) memory. (cannot point to data on stack / faster run time)

# FEATURES

- Stack machine

- Both Separated/Combined memory model.

- Integer, Float data type

- Instruction size 1 byte / 5 bytes (1 param)

- Function call

# SPECIFICATION

- Code: array[byte]

- Stack/Heap: array[uint32]
