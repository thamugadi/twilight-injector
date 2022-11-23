.macro .mov reg addr
li \reg, 0
ori \reg, \reg, (\addr >> 16) & 0x0000ffff
slwi 0, 0, 16
ori \reg, \reg, \addr & 0x0000ffff
.endm

# Place your code here.
b $
