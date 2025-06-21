LDI r1 0
CAL .inc
CAL .add_2
CAL .add_3
HLT

.inc ADI r1 1
    RET

.add_2
    ADI r1 2
    RET

.add_3






    ADI r1 3
    RET