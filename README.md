# Abstract-Vm

The purpose of this project is to create a simple virtual machine that can interpret programs written in a basic assembly language.

## How to run

1. 
```bash
./avm
```

The avm will read from standard input and interpret code after each ';;' token.

2.
```bash
./avm example.avm
```

The avm will read the file and execute the instructions in it provided the assembly code is correct.

## Features

This project features multiple things:

### Virtual Machine

AVM is a stack based virtual machine that can interpret an assembly language with a limited and explicit type system.

### .avm files

.avm are files that contain assembly code that respects the grammar dictated in grammar.txt.

### Errors

Files containing syntax error will not be interpreted.
An .avm file needs to contain an exit instruction.

## Implementation details

The project is implemented using a Lexer/Parser couple, and a Vm class that interprets the instructions generated by the parser.
It executes mathematical operations following an infix notation, and it checks for overflows and underflows.
It is compiled with c++17.