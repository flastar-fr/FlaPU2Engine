IST 0 .timer_isr
IST 1 .set_2_isr
IST 2 .set_3_isr

INT 2
INT 1
.start
    JMP .start
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