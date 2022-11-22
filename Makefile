PPC = powerpc-eabi

inject : injector code.bin
        cat code.bin | ./injector $(GCI) 10000

code.bin : code.s 
        $(PPC)-as -s code.s -o code.o
        $(PPC)-ld --oformat binary -Ttext=0x803ED214 code.o -o code.bin

injector : main.c
        gcc main.c -o injector
clean:
        rm *.o *.bin
