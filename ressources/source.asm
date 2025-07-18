# write "HELLO WORLD!"
LDI r1 'H'
LDI r2 'E'
LDI r3 'L'
LDI r4 'L'
LDI r5 'O'
LDI r6 ' '
LDI r7 'W'
LDI r8 'O'
LDI r9 'R'
LDI r10 'L'
LDI r11 'D'
LDI r12 '!'
PST write_char [r1]
PST write_char [r2]
PST write_char [r3]
PST write_char [r4]
PST write_char [r5]
PST write_char [r6]
PST write_char [r7]
PST write_char [r8]
PST write_char [r9]
PST write_char [r10]
PST write_char [r11]
PST write_char [r12]
PST print_chars

# write "666"
LDI r13 2
LDI r14 154
PST write_number [r13:r14]
PST print_number

# draw pixel
LDI r1 50
PST pixel1_x [r0:r1]
PST pixel1_y [r0:r1]
PST draw_pixel
PST print_screen

# draw rectangle
LDI r1 80
PST pixel1_x [r0:r1]
PST pixel1_y [r0:r1]
LDI r2 1
LDI r3 244
PST pixel2_x [r2:r3]
PST pixel2_y [r2:r3]
PST draw_rect
PST print_screen
PST clear_rect
PST print_screen
PST clear_screen
PST print_screen

# randomly place 5 rectangles
LDI r3 5
LDI r4 255
PST rng_range [r0:r4]
.start_rects
    PLD random_nb r1
    PLD random_nb r2
    PST pixel1_x [r0:r1]
    PST pixel1_y [r0:r1]
    PST pixel2_x [r0:r2]
    PST pixel2_y [r0:r2]
    PST draw_rect
    PST print_screen
    PST clear_screen
    DEC r3
    CMP r3 r0
    BRH != .start_rects

PST clear_screen
PST print_screen

# draw rectangle following the pressed arrows
LDI r1 10
LDI r2 40
LDI r3 45
LDI r4 70
LDI r5 75
LDI r6 105
LDI r7 135
LDI r9 35 # UP
LDI r10 36 # DOWN
LDI r11 37 # LEFT
LDI r12 38 # RIGHT
.rects.start
    PLD keyboard_input r8
    CMP r8 r9
    BRH = .rects.up
    CMP r8 r10
    BRH = .rects.down
    CMP r8 r11
    BRH = .rects.left
    CMP r8 r12
    BRH = .rects.right
    JMP .rects.start

HLT

.rects.up
    PST pixel1_x [r0:r5]
    PST pixel1_y [r0:r1]
    PST pixel2_x [r0:r6]
    PST pixel2_y [r0:r2]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start

.rects.down
    PST pixel1_x [r0:r5]
    PST pixel1_y [r0:r3]
    PST pixel2_x [r0:r6]
    PST pixel2_y [r0:r5]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start

.rects.left
    PST pixel1_x [r0:r2]
    PST pixel1_y [r0:r3]
    PST pixel2_x [r0:r4]
    PST pixel2_y [r0:r5]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start

.rects.right
    PST pixel1_x [r0:r6]
    PST pixel1_y [r0:r3]
    PST pixel2_x [r0:r7]
    PST pixel2_y [r0:r5]
    PST clear_screen
    PST draw_rect
    PST print_screen
    JMP .rects.start