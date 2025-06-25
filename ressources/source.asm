LDI r1 2
LDI r2 1

.start
    CMP r1 r2
    JGE .end
    JMP .start

.end HLT