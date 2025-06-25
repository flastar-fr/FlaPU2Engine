LDI r1 1
LDI r2 1

.start
    CMP r1 r2
    JEQ .end
    JMP .start

.end HLT