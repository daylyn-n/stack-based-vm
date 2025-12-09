# Tiny Stack-Based VM and Assembler

This is a minimal stack-based virtual machine and assembler written in C++. Designed as a learning project to explore instruction encoding, bytecode execution, stack operations, the vim text editor, and modern C++ design (C++17).

## Overview

This VM executes a simple 32-bit instruction format:

- **Top 2 bits**: instruction type  
  - `00` = push positive integer  
  - `10` = push negative integer  
  - `01` = primitive opcode  
- **Lower 30 bits**: data payload (integer or primitive ID)

Execution model:

- Operands are pushed onto a stack
- Primitive instructions consume one or more stack values
- The VM halts when it encounters the `STOP` instruction


## Instruction Format

Each instruction is a 32-bit value:


Primitive opcodes currently implemented:

| Opcode | Meaning |
|--------|---------|
| 0      | STOP    |
| 1      | ADD     |
| 2      | SUB     |
| 3      | MUL     |
| 4      | DIV     |

---

## Example Program

Entering numbers in postfix notation:

2 3 + 5 * 1 /

1. push 2
2. push 3
3. add 2 3 -> 5
4. push 5
5. mul 5 5 -> 25
6. push 1
7. div 25 1 -> 25
8. STOP


