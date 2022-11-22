PPC = powerpc-eabi

inject : injector code.bin
        ./injector $(GCI)

code.bin : code.s 
        $(PPC)-as -s $< -o code.o
        $(PPC)-ld --oformat binary -Ttext=0x803ED214 code.o -o $@

injector : main.c
        gcc $< -o $@
clean:
        rm *.o *.bin
