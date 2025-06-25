LDI r1 2
LDI r2 3

.start CMP r1 r2
BRH < .end
JMP .start

.end HLT