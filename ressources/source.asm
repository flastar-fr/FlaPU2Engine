DEFINE x 3

ldi r1 1
LDI r2 x
STR [r1:r2] [r2]
LOD r3 [r1:r2]

HLT