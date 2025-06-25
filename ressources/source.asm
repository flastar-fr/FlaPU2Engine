LDI r1 1
LDI r2 2

.start
    CMP r1 r2
    JLT .end
    JMP .start

.end HLT