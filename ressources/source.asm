LDI r1 1
LDI r2 2

.start
    CMP r1 r2
    JNE .end

.end HLT