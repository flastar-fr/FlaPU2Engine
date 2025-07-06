LDI r1 1
LDI r2 2

.start
    ADD r1 r2 r1
    JMP .start

HLT