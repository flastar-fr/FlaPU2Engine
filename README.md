# FlaPU2Engine
This project is an emulator for an 8-bit CPU that has more than 65MB (can be configured but cannot be more than actually configured) of memory and 16 registers.
This is my first C++ project, so it is more a learning project than an actual useful project.
You can find my [ISA](https://docs.google.com/spreadsheets/d/1aE8e7TodV6_dxUF-UbF0xdbSolc1Z1ntD5Rz3ESL6Uk/edit?gid=0#gid=0) here (not followed 100%).
***

## Summary
1. [Getting started](#getting-started)
   1. [Compile](#compile)
2. [How to program ?](#how-to-program-)
    1. [Null register](#null-register)
    2. [Definitions](#definitions)
    3. [Labels](#labels)
    4. [Ports](#ports)
    5. [Interrupts](#interrupts)
    6. [Extra information](#extra-information)
3. [Features](#features)
4. [Examples](#examples)
   1. [Fibonacci](#fibonacci)
   2. [Division](#division)
   3. [Modulo](#modulo)
   4. [Multiplication](#multiplication)
   5. [Example using all ports](#example-using-all-ports)
   6. [Complete example with interrupts](#complete-example-with-interrupts)

## Getting started
The build tool this project uses is xmake, and it also needs for the unit tests the gtest library (if you are interested in tests, otherwise you can remove the "tests" part from the [xmake.lua](xmake.lua)).
This project is written using the C++ 17 convention.

For now the only way to tell to the program which file you want to execute is by modifying the hard coded file name in the main file and making sure the file is in the ressource source folder at compilation.
To see the result, you have to look at the values displayed after the program execution, which represent the values of the 6 first registers.

### Compile
To compile and launch the main program you have to have xmake installed and launch the ``xmake run FlaPU2Engine`` command. 
This command will start downloading ImGui and all dependencies and then compile to execute.
Same for the unit tests and launch ``xmake run tests``. Same as before, it will download this time the gtest package. 
All this configuration can be found in [the xmake.lua file](xmake.lua).

I tested my program to compile with MCVS on Windows and gcc on Arch Linux. 
Both the main program and the tests work properly with both of the compilers / systems. 
However, for the tests, the gcc compiler returns me warnings, but it seems to be version related and I do not understand where is the issue so you might not have the issue.

## How to program ?
With the ISA and some really basic knowledge of assembly, you should be able to program in my assembly language.
However, you may need some extra information on some particular things. 
Note that I do not follow a 100% the ISA. I added a couple more features for some instructions, so I recommend you watching my code for the instruction implementation before calling it.

### Null register
This project uses my own architecture, so the first register (r0) is an eternal null register, which means that no matter what value you assign to it, its value will always be 0.
That also means that you can use this register in instruction calls, and you will be sure that the value of the register will be 0.

### Definitions
To create a definition, you have to use the ``define`` keyword, and use this format : ``define <definition name> <definition value>``.
Example : ``define NULL_VALUE 0``

Definitions are implemented using an unordened map during preprocessing and does not check if a definition already exists. 
So you have to make sure to define a definition name only one time to not deal with undefined behaviour.

### Labels
Labels always start with a dot and are placed before the instruction that you want to jump from.
Take a look at the [examples](#examples) for a better understanding.

### Ports
Ports can be accessed via their name or their id. The id looks close to register id but instead of starting with an ``r`` it starts with a ``p`` so for example : ``p0``, ``p1``, ``p2``.
There are 18 ports so the last port is p17.

Ports names are evaluated at preprocessing to be replaced by a port id.

Here is the list of all available ports name :
1. Text display
   - write_char
   - clear_chars
   - print_chars
2. Number display
   - write_number
   - clear_number
   - print_number
3. Screen
   - pixel1_x
   - pixel1_y
   - pixel2_x
   - pixel2_y
   - draw_pixel
   - draw_rect
   - clear_pixel
   - clear_rect
   - clear_screen
   - print_screen
4. Random device
   - rng_range
   - random_nb
5. Keyboard input
   - keyboard_input
6. Periodic interrupt timer
   - input_timer_ms
7. Interrupts controles
   - switch_interrupt
   - get_interrupt_state
Note : this order also represents the order where it is left in the vector. That means that the id of the first name in the list is ``p0``, next is ``p1`` and so on to ``p17``.

To interract with ports you have to use the ``PLD`` and ``PST`` instructions. The first one loads the value of a port into a register, the second one stores the value of a register into a port.

For ports that only needs to be triggered you can just pass no register with ``PST`` instruction, and it will be triggered. Even if you pass a register that has a value of 0 it will be triggered (might change later).

You can check the complete example on ports [here](#example-using-all-ports)

### Interrupts
The interrupt system is very simple. The engine has an Interrupt Vector Table (IVT) of 255 interrupts (so the max amount of interrupts) and each index correspond to an address for the ISR. 
Instructions for interrupts varies a bit from the ISA. The ``IST`` instruction used as ``IST <interrupt code (immediate value)> <ISR address (immediate value)>`` is used to store the ISR address in the IVT. 
The ``INT`` instruction used as ``INT <interrupt code (immediate value)>`` trigger an interrupt. 

At the end of your ISR code you have to put the ``IRT`` instruction which tells the engine to pop from the address stack exactly like a ``RET`` instruction after being ``CAL``. 
What is the point of ``IRT`` instruction then ? The ``IRT`` instruction also sets the flag for instructions to be triggerable as enabled because ``INT`` one deactivate the flag. 
A flag deactivated means that no interrupts can be triggered.

The interrupt with the code 0 is reserved for the timer interrupt. This interrupt is thrown once every n ms where n is by default 1000ms. 
You can edit this value with the ``input_timer_ms`` port that takes 2 registers values argument (high / low bytes).
If this interrupt is called during when the interrupt flag is false it will just be avoided.

I ugely recommend you to check out [my example](#complete-example-with-interrupts) before trying to using interrupts.

### Extra information
Comments are only singleline and start with a ``#``.

All the configurations are available in .hpp or .cpp files. 
The config files for the engine are [src/config_hardware.hpp](src/config_hardware.hpp) and [src/config_hardware.cpp](src/config_hardware.cpp). 
The config file for the GUI is [src/gui/config_gui.hpp](src/gui/config_gui.hpp). 
I do not recommend you to remove some datas from these files, but you can change the default values, add new instructions, new chars, etc... But already existing values (mainly in enums) could result in compilation error.

## Features
- [x] Working structure (registers, memory, etc...)
- [x] Support for all instructions
- [x] Support for all pseudoinstructions
- [x] Support for comments
- [x] Support for labels
- [x] Support for definitions
- [x] Support for ports
  - [x] Main window
    - [x] Draw pixel
    - [x] Draw filled rectangles
    - [x] Clear pixel
    - [x] Clear rectangle
    - [x] Clear screen
    - [x] Update screen
  - [x] Basic number 16-bit display
    - [x] Clear display
    - [x] Add number
    - [x] Show number
  - [x] Basic text display 20 chars
    - [x] Add char
    - [x] Clear chars
    - [x] Display chars
  - [x] Random 8 bits number generator
  - [x] Input system
- [ ] Support for interruptions
- [ ] Better way to select a program
- [x] Better error messages
- [x] Remove case sensitivity for keywords
- [x] Be able to have more than 255 memory cells
- [x] GUI
  - [x] See / draw main window
  - [x] Basic number display
  - [x] Basic text display
  - [x] See registers values
  - [x] See memory values
  - [x] Adapt clock speed
  - [x] See program counter and flags
  - [x] See the current number of executed instructions
  - [x] Run / Pause / Stop the program

## Examples
Note that these programs can be hugely optimized and readibility improved. It is just to give you some examples of how to use my assembly language.

In these examples the labels are nammed following this format : ``.<prog name>.<function>`` but this is just the choice I made.
I could just use the format : ``.<function>`` if I wanted to. As long as it starts with a ``.``, you can name a label as you want.

### Fibonacci
r1 is the register result of the program. Here: x = 13, F_x = 233
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
        JEQ .fib.end
        INC r3
        ADD r1 r4 r5
        MOV r1 r4
        MOV r5 r1
        JMP .fib.start

    .fib.end RET
```

### Division
r3 is the register result. Here: x = 13, y = 5, x/y = 2
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
    JEQ .div.end

    .div.start
        ADD r2 r4 r4
        CMP r1 r4
        JLT .div.end
        INC r3
        JMP .div.start

    .div.end RET
```

### Modulo
r3 is the register result. Here: x = 13, y = 5, x % y = 3
```asm
define x 13
define y 5

LDI r1 x
LDI r2 y

CAL .mod
HLT

.mod
    MOV r1 r3

    .mod.start
        CMP r2 r3
        JEQ .mod.is_0
        JGE .mod.end
        SUB r3 r2 r3
        JMP .mod.start

    .mod.is_0 LDI r3 0

    .mod.end RET
```

### Multiplication
r3 is the register result. Here: x = 5, y = 13, x * y = 65
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
        CMP r2 r4
        JEQ .mul.end
        ADD r1 r3 r3
        INC r4
        JMP .mul.start

    .mul.end RET
```

### Example using all ports
In this example I dive into each port (except those used for interrupts, check the example with interrupts to get the examples) and use these ports using the appropriate instruction (PLD or PST). 
This is a fairly simple but complete example which shows all the available ports.
```asm
# write "HELLO WORLD!"
LDI r1 'H'
LDI r2 'E'
LDI r3 'L'
LDI r4 'L'
LDI r5 'O'
LDI r6 ' '
LDI r7 'W'
LDI r8 'O'
LDI r9 'R'
LDI r10 'L'
LDI r11 'D'
LDI r12 '!'
PST write_char [r1]
PST write_char [r2]
PST write_char [r3]
PST write_char [r4]
PST write_char [r5]
PST write_char [r6]
PST write_char [r7]
PST write_char [r8]
PST write_char [r9]
PST write_char [r10]
PST write_char [r11]
PST write_char [r12]
PST print_chars

# write "666"
LDI r13 2
LDI r14 154
PST write_number [r13:r14]
PST print_number

# draw pixel
LDI r1 50
PST pixel1_x [r0:r1]
PST pixel1_y [r0:r1]
PST draw_pixel
PST print_screen

# draw rectangle
LDI r1 80
PST pixel1_x [r0:r1]
PST pixel1_y [r0:r1]
LDI r2 1
LDI r3 244
PST pixel2_x [r2:r3]
PST pixel2_y [r2:r3]
PST draw_rect
PST print_screen
PST clear_rect
PST print_screen
PST clear_screen
PST print_screen

# randomly place 5 rectangles
LDI r3 5
LDI r4 255
PST rng_range [r0:r4]
.start_rects
    PLD random_nb r1
    PLD random_nb r2
    PST pixel1_x [r0:r1]
    PST pixel1_y [r0:r1]
    PST pixel2_x [r0:r2]
    PST pixel2_y [r0:r2]
    PST draw_rect
    PST print_screen
    PST clear_screen
    DEC r3
    CMP r3 r0
    BRH != .start_rects

PST clear_screen
PST print_screen

# draw rectangle following the pressed arrows
LDI r1 10
LDI r2 40
LDI r3 45
LDI r4 70
LDI r5 75
LDI r6 105
LDI r7 135
LDI r9 35 # UP
LDI r10 36 # DOWN
LDI r11 37 # LEFT
LDI r12 38 # RIGHT
.rects.start
    PLD keyboard_input r8
    CMP r8 r9
    BRH = .rects.up
    CMP r8 r10
    BRH = .rects.down
    CMP r8 r11
    BRH = .rects.left
    CMP r8 r12
    BRH = .rects.right
    JMP .rects.start

HLT

.rects.up
    PST pixel1_x [r0:r5]
    PST pixel1_y [r0:r1]
    PST pixel2_x [r0:r6]
    PST pixel2_y [r0:r2]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start

.rects.down
    PST pixel1_x [r0:r5]
    PST pixel1_y [r0:r3]
    PST pixel2_x [r0:r6]
    PST pixel2_y [r0:r5]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start

.rects.left
    PST pixel1_x [r0:r2]
    PST pixel1_y [r0:r3]
    PST pixel2_x [r0:r4]
    PST pixel2_y [r0:r5]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start

.rects.right
    PST pixel1_x [r0:r6]
    PST pixel1_y [r0:r3]
    PST pixel2_x [r0:r7]
    PST pixel2_y [r0:r5]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start
```

### Complete example with interrupts
This example first set the ISR of each interrupt. After that it modifies the default duration for the timer (1000ms -> 500ms). It then triggers the interrupts 2 and 1, the first one displays 'Hello World!' in the text display and the second one displays 666. 
During this process the timer interrupt might be good to be triggered but is not triggered because interrupts can't be triggered during another interrupt. 
Because trigerring the third interrupt it switches off (on -> off) the interrupts, and it checks if the interrupt state is true or false (purly for the demonstration, it is not needed). 
So the interrupt get triggered but because the state is off it is not executed. It then switches back the interrupt state to on (off -> on).
After the 2 interrupts are executed and the third triggered, the timer interrupt can be executed during the infinite loop to increment r1 each time the interrupt is triggered.
```asm
IST 0 .timer_isr
IST 1 .set_2_isr
IST 2 .set_3_isr
IST 3 .set_4_isr
LDI r5 1
LDI r6 244
PST input_timer_ms [r5:r6]
LDI r5 0
LDI r6 0

INT 2
INT 1

PST switch_interrupt
PLD get_interrupt_state r3
CMP r3 r0
BRH != .end
INT 3
PST switch_interrupt

LDI r1 0
.start
    JMP .start

.end
    HLT

.timer_isr
    INC r1
    IRT

.set_2_isr
    CAL .say_666
    IRT

.set_3_isr
    CAL .write_hello_world
    IRT

.set_4_isr
    LDI r2 4
    IRT

.write_hello_world
    LDI r1 'H'
    LDI r2 'E'
    LDI r3 'L'
    LDI r4 'L'
    LDI r5 'O'
    LDI r6 ' '
    LDI r7 'W'
    LDI r8 'O'
    LDI r9 'R'
    LDI r10 'L'
    LDI r11 'D'
    LDI r12 '!'
    PST write_char [r1]
    PST write_char [r2]
    PST write_char [r3]
    PST write_char [r4]
    PST write_char [r5]
    PST write_char [r6]
    PST write_char [r7]
    PST write_char [r8]
    PST write_char [r9]
    PST write_char [r10]
    PST write_char [r11]
    PST write_char [r12]
    PST print_chars
    RET

.say_666
    LDI r13 2
    LDI r14 154
    PST write_number [r13:r14]
    PST print_number
    RET
```