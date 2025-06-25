DEFINE x 3

ldi r1 1
LDI r2 x

.start
    CMP R1 r2
    JLT .end
    JMP .start

.end HLT