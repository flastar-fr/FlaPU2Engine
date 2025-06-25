define x 3

LDI r1 1
LDI r2 x

.start
    CMP r1 r2
    JLT .end
    JMP .start

.end HLT