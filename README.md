# FlaPU2Engine
This project is an emulator for an 8 bits CPU that has (for now) 255 bytes of memory and 16 registers. 
This is my first C++ project so it is more a learning project than an actual useful project. 
You can find my [ISA](https://docs.google.com/spreadsheets/d/1aE8e7TodV6_dxUF-UbF0xdbSolc1Z1ntD5Rz3ESL6Uk/edit?gid=0#gid=0) here.
***

## Summary
1. [Getting started](#getting-started)
2. [Addionnal information](#additionnal-information)
3. [Features](#features)
4. [Examples](#examples)

## Getting started
The build tool this project uses is xmake, and it also needs for the unit tests the gtest library (if you are interrested in tests, otherwise you can remove the tests part from the xmake.lua). 
This project is written using the C++ 17 convention. 
For now the only way to tell to the program which file you want to execute is by modifying the hard coded file name in the main file and making sure the file is in the ressource source folder at compilation. 
To see the result you have to look the values displayed after the program execution which represents the values of the 6 first registers.

## Additionnal information
With the ISA and some basic knowledge of assembly you should be able to program in my assembly language.
However, you may need some extra information on some particular things.

This project uses my own architecture so the first register (r0) is an eternal null register which means that no matter what value you assign to it its value will always be 0. 
That also means that you can use this register in instruction calls, and you will be sure that the value of the register will be 0.

To create a definition you have to use the ``define`` keyword and you this format : ``define <definition name> <definition value>``.
For example : ``define NULL_VALUE 0``

The labels always start with a dot and are placed before the instruction that you want to jump from. 
Take a look at the [examples](#examples) for a better understanding.

Comments are only singleline and start with a ``#``.

## Features
- [x] Working structure (registers, memory, etc...)
- [ ] Support to all instructions
  - Need ports instructions
- [x] Support to comments
- [x] Support to labels
- [x] Support to definitions
- [ ] Support to ports
- [ ] Support to interruptions
- [ ] Better error messages
- [ ] GUI

## Examples
Note that these programs can be hugely optimized, it is just to give you examples of how to use my assembly language.

### Fibonacci
r1 is the register result of the program. Here : x = 13, F_x = 233
```asm
define x 13

LDI r2 x

CAL .fib
HLT

.fib
    LDI r1 0
    LDI r3 0
    LDI r4 1
    LDI r5 0

    .fib.start
        SUB r3 r2 r0
        BRH = .fib.end
        ADI r3 1
        ADD r1 r4 r5
        ADD r1 r0 r4
        ADD r5 r0 r1
        JMP .fib.start

    .fib.end RET
```

### Division
r3 is the register result. Here : x = 13, y = 5, x/y = 2
```asm
define x 13
define y 5

LDI r1 x
LDI r2 y

CAL .div
HLT

.div
    LDI r3 0
    LDI r4 0

    SUB r2 r0 r0
    BRH = .div.end

    .div.start
        ADD r2 r4 r4
        SUB r1 r4 r0
        BRH < .div.end
        ADI r3 1
        JMP .div.start

    .div.end RET
```

### Modulo
r3 is the register result. Here : x = 13, y = 5, x % y = 3
```asm
define x 13
define y 5

LDI r1 x
LDI r2 y

CAL .mod
HLT

.mod
    ADD r1 r0 r3

    .mod.start
        SUB r2 r3 r0
        BRH = .mod.is_0
        BRH >= .mod.end
        SUB r3 r2 r3
        JMP .mod.start

    .mod.is_0 LDI r3 0

    .mod.end RET
```

### Multiplication
r3 is the register result. Here : x = 5, y = 13, x * y = 65
```asm
define x 5
define y 13

LDI r1 x
LDI r2 y

CAL .mul
HLT

.mul
    LDI r3 0
    LDI r4 0

    .mul.start
        SUB r2 r4 r0
        BRH = .mul.end
        ADD r1 r3 r3
        ADI r4 1
        JMP .mul.start

    .mul.end RET
```