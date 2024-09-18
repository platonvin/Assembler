[![Build](https://github.com/platonvin/Assembler/actions/workflows/build.yml/badge.svg)](https://github.com/platonvin/Assembler/actions/workflows/build.yml)

# Assembler

CPU emulator for custom ASM language

- `assembler` - tool to compile text assembly to bytecode
- `processor` - tool to run compiled bytecode

## Installation
- Get source code 
  - `git clone https://github.com/platonvin/Assembler`
- Build
  - `cd Assembler`
  - `make`


## Usage
`assembler dir/filename [--log]` - compiles text assembly into bytecode. Compiled file is placed near source file
 - [--log] means you either pass --log or nothing

`processor dir/filename [--log]` - runs bytecode. `processor` will try to find _dir/filename.compiled_ first, then _dir/filename_

## Examples
in _programs/_ you can find few examples
 - **circle** - draws circle in terminal
   valid usage:
     ```bash
     assembler programs/circle
     processor programs/circle.compiled
     <radius> <threshold>
     ```
     e.g.:
      ```bash
        assembler programs/circle
        processor programs/circle.compiled
        42 100
     ```
 - **factor** - calculates factorial
   valid usage:
     ```bash
     assembler programs/factor
     processor programs/factor.compiled
     <number_to_calculate_factorial_for>
     ```
 - **quadr** - solves quadratic equation
    valid usage:
     ```bash
     assembler programs/quadr
     processor programs/quadr.compiled
     <a> <b> <c>
     ```
      floating point numbers are not supported, scaled integers used instead (1.012 -> 1012)

## Language reference
    All instructions can also be found in [commands.h](src/defines/commands.h)

| Instruction | Opcode | Operands | Description | 
| --- | --- | --- | --- | 
| HLT | 0x00 | None | Halts program execution and terminates the emulator. | 
| PUSH | 0x01 | 1 | Pushes a value onto the stack (from register, immediate value, or VRAM address). | 
| POP | 0x02 | 1 | Pops a value from the stack (into register, VRAM, or discarded). | 
| ADD | 0x03 | None | Adds the top two stack values and pushes the result. | 
| SUB | 0x04 | None | Subtracts the second stack value from the first and pushes the result. | 
| IMUL | 0x05 | None | Multiplies the top two stack values (signed) and pushes the result. | 
| MUL | 0x06 | None | Multiplies the top two stack values (unsigned) and pushes the absolute result. | 
| IDIV | 0x07 | None | Divides the first stack value by the second (signed) and pushes the result. | 
| DIV | 0x08 | None | Divides the first stack value by the second (unsigned) and pushes the absolute result. | 
| OUT | 0x09 | None | Pops and prints the top stack value. | 
| IN | 0x0a | None | Reads an input value and pushes it onto the stack. | 
| JB | 0x0b | 1 | Jumps to the specified address if the first stack value is less than the second. | 
| JBE | 0x0c | 1 | Jumps to the specified address if the first stack value is less than or equal to the second. | 
| JA | 0x0d | 1 | Jumps to the specified address if the first stack value is greater than the second. | 
| JAE | 0x0e | 1 | Jumps to the specified address if the first stack value is greater than or equal to the second. | 
| JE | 0x0f | 1 | Jumps to the specified address if the first stack value equals the second. | 
| JNE | 0x10 | 1 | Jumps to the specified address if the first stack value is not equal to the second. | 
| JMP | 0x11 | 1 | Unconditional jump to the specified address. | 
| NEG | 0x12 | None | Negates the top stack value and pushes the result. | 
| SQRT | 0x13 | None | Computes the square root of the top stack value and pushes the result. | 
| DUP | 0x14 | None | Duplicates the top stack value and pushes both copies. | 
| VPOP | 0x15 | None | Pops two values and stores the second in VRAM at the index specified by the first. | 
| VFL | 0x16 | None | Outputs VRAM content to the screen and clears VRAM up to the first zero or MAX_VRAM. |