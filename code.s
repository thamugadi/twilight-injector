.macro .mov reg imm
li \reg, 0
ori \reg, \reg, (\imm >> 16) & 0x0000ffff
slwi \reg, \reg, 16
ori \reg, \reg, \imm & 0x0000ffff
.endm

# Place your code here.
b $
