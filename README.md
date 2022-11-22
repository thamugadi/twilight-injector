# twilight-injector
ret2shellcode in Zelda: Twilight Princess savefile.

``code.s`` will be compiled into PowerPC raw machine code and will be copied in the savefile. At runtime, the instructions will be located at 0x803ed214. The payload is setting the saved return address at this value.

It will take advantage of the buffer overflow vulnerability, widely used in 2008 by Team Twiizers, to overwrite the return address and to return to a shellcode : https://github.com/lewurm/savezelda & https://github.com/FIX94/twilight-hack-gc
