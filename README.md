
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
     <width> <height>
     ```
     e.g.:
      ```bash
        assembler programs/circle
        processor programs/circle.compiled
        12 13
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

> HLT
> - **Opcode:** 0x00
> - **Operands:** None
> - **Description:** Halts program execution and terminates the emulator.

> PUSH
> - **Opcode:** 0x01
> - **Operands:** 1
> - **Description:** Pushes a value onto the stack. The value can be sourced from a register, an immediate value, or a VRAM address.

> POP
> - **Opcode:** 0x02
> - **Operands:** 1
> - **Description:** Pops a value from the stack. The value can be stored in a register or VRAM, or discarded.

> ADD
> - **Opcode:** 0x03
> - **Operands:** None
> - **Description:** Adds the top two stack values and pushes the result back onto the stack.

> SUB
> - **Opcode:** 0x04
> - **Operands:** None
> - **Description:** Subtracts the second stack value from the first and pushes the result back onto the stack.

> IMUL
> - **Opcode:** 0x05
> - **Operands:** None
> - **Description:** Multiplies the top two stack values (signed multiplication) and pushes the result.

> MUL
> - **Opcode:** 0x06
> - **Operands:** None
> - **Description:** Multiplies the top two stack values (unsigned multiplication) and pushes the absolute result.

> IDIV
> - **Opcode:** 0x07
> - **Operands:** None
> - **Description:** Divides the first stack value by the second (signed division) and pushes the result.

> DIV
> - **Opcode:** 0x08
> - **Operands:** None
> - **Description:** Divides the first stack value by the second (unsigned division) and pushes the absolute result.

> OUT
> - **Opcode:** 0x09
> - **Operands:** None
> - **Description:** Pops and prints the top stack value.

> IN
> - **Opcode:** 0x0a
> - **Operands:** None
> - **Description:** Reads an input value and pushes it onto the stack.

> JB
> - **Opcode:** 0x0b
> - **Operands:** 1
> - **Description:** Jumps to the specified address if the first stack value is less than the second.

> JBE
> - **Opcode:** 0x0c
> - **Operands:** 1
> - **Description:** Jumps to the specified address if the first stack value is less than or equal to the second.

> JA
> - **Opcode:** 0x0d
> - **Operands:** 1
> - **Description:** Jumps to the specified address if the first stack value is greater than the second.

> JAE
> - **Opcode:** 0x0e
> - **Operands:** 1
> - **Description:** Jumps to the specified address if the first stack value is greater than or equal to the second.

> JE
> - **Opcode:** 0x0f
> - **Operands:** 1
> - **Description:** Jumps to the specified address if the first stack value equals the second.

> JNE
> - **Opcode:** 0x10
> - **Operands:** 1
> - **Description:** Jumps to the specified address if the first stack value is not equal to the second.

> JMP
> - **Opcode:** 0x11
> - **Operands:** 1
> - **Description:** Unconditional jump to the specified address.

> NEG
> - **Opcode:** 0x12
> - **Operands:** None
> - **Description:** Negates the top stack value and pushes the result.

> SQRT
> - **Opcode:** 0x13
> - **Operands:** None
> - **Description:** Computes the square root of the top stack value and pushes the result.

> DUP
> - **Opcode:** 0x14
> - **Operands:** None
> - **Description:** Duplicates the top stack value and pushes both copies.

> VPOP
> - **Opcode:** 0x15
> - **Operands:** None
> - **Description:** Pops two values and stores the second in VRAM at the index specified by the first.

> VFL
> - **Opcode:** 0x16
> - **Operands:** None- 
> - **Description:** Outputs VRAM content to the screen and clears VRAM up to the first zero or MAX_VRAM