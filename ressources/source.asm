IST 0 .my_isr
.start
    NOP
    JMP .start
HLT

.my_isr
    INC r1
    IRT