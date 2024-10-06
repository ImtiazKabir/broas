# Broas - A pseudo assembly interpreter for dummies

This is a Turing complete language interpreter.

## Installation
1. Clone the repository
2. run `make`

## Usage
Run `broas <filename> <...arguments to your broas code>`

### Variables
Variables are named with an alphabetic character followed by any non whitespace character. They take up a "machine word" (i.e. `64` bytes in a `64` bit machine and `32` bits in a `32` bit machine)

### Immediates
Immediates are numeric (`1`, `10`, `-5` etc) or character literals (`'a'`, `'b'`, `'x'` etc). They take the same size as variables. To include special characters, use the `C` escape sequences. For example, for newline characters, use `'\n'`. Additionally for space, instead of `' '`, `broas` requires `'\s'`

### Memory
The memory is an array of "machine words" (i.e. `64` bytes in a `64` bit machine and `32` bits in a `32` bit machine). It can be accessed freely. The size of the memory array is defined in `main.c` as `MEMORY_SIZE`

### Comments
Comments are written with a semicolon in front. Example - 
```
add a b c ; a = b + c
```

### Labels
Labels can be defined with the `@` notation. For example - 
```
@loop
add a b c
```

### Command line arguments
The argument count is stored at `memory[0]` and the arguments are stored from memory slot 1 onward. Beware that `broas` does not include the file name in the filename in the argument list. The arguments can be loaded into variables with `lw` instruction. 

### Supported instructions - 

#### R-Type instructions
```
<instruction> result leftOperand rightOperand
```
This performs the specified instruction with `leftOperand` and `rightOperand`, and stores the result in the `result` variable. Both the operands can be either variable or immediate
Currently supported r-type instructions are `add`, `sub`, `mult`, `div`, `mod`, `xor`, `and`, `not`, `sl`, `sr`
The bitwise operations are just like in `C`. `sl` and `sr` stand for shift left and shift right respectively where `rightOperand` denotes the shift amount

#### Memory instructions
##### Load store instructions
```
<lw/sw> variable memoryIndex
```
`memoryIndex` is the index where the load or store operation will take place in memory array. It can be either a variable that contains the memory index or an immediate. Example - `lw x 0` (equivalent to `x = memory[0]` or `sw y p` (equivalent to `memory[p] = y`)

##### Reference instruction
```
ref pointer memoryIndex
```
`memoryIndex` is the index where the reference operation will take place. It can be either a variable containing the memory index or an immediate.
This operation is identical to the `C` code - `pointer = memory + memoryIndex;`

##### Dereference instruction
```
deref variable pointer size
```
The `pointer` is a variable that is a `C` standard pointer.
`size` determines how many bytes will be dereferenced from the pointer. This can be either a variable containing the size or an immediate.
The result will be stored at `variable`
This is identical to the `C` code - `variable = *pointer;`, but the only difference is in `broas`, you can also control how many bytes will be taken from memory. For example `deref value address 4` is equivalent to - `value = *(int *)address;`

#### Branch and Jump instructions

##### Jump instruction
```
jmp @label
```

##### Branch instruction
```
<instruction> a b <label>
```

The allowed branch instructions are `beq`, `bneq`, `blt`, `bgt`, `ble`, `bge`
The operands can be either a variable or an immediate.

#### Miscellaneous

##### Print and scan instruction
```
<print/scan> variable
```

It is used for a **single** character input and output.

##### Exit instruction
```
exit code
```
Exits with a specific status code. `code` could be a variable or an immediate.

## XV6 support
For XV6-risc-v specifically, use the `broas.c` as a user program. It includes the ability to call a syscall directly from within `broas`
