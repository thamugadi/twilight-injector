.macro .mov reg imm
li \reg, 0
ori \reg, \reg, (\imm >> 16) 
slwi \reg, \reg, 16
ori \reg, \reg, \imm & 0x0000ffff
.endm

.macro .store32 addr val reg1 reg2
lis \reg1, (\addr >> 16)
ori \reg1, \reg1, (\addr & 0x0000ffff)
.mov \reg2 \val
stw \reg2, 0(\reg1)
.endm

.macro .store8 addr val reg1 reg2
lis \reg1, (\addr >> 16)
ori \reg1, \reg1, (\addr & 0x0000ffff)
.mov \reg2 \val
stb \reg2, 0(\reg1)
.endm
