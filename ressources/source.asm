IST 1 .my_isr1
IST 2 .my_isr2
INT 2
INT 1
HLT

.my_isr1
    LDI r1 1
    IRT

.my_isr2
    INT 2
    LDI r2 2
    IRT