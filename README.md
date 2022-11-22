# twilight-injector
ret2shellcode in Zelda: Twilight Princess (Gamecube) savefile.

Usage:
```
yourcode.s > code.s
make GCI="your_savefile.gci"
```

``code.s`` will be compiled into PowerPC raw machine code and will be copied in the savefile. At runtime, the instructions will be located at 0x803ed214. The payload is setting the saved return address at this value.

It takes advantage of the buffer overflow vulnerability widely used in 2008 by Team Twiizers : https://github.com/lewurm/savezelda & https://github.com/FIX94/twilight-hack-gc
