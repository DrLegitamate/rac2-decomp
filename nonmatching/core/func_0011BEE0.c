/* kputchar (libkernl.a:kprintf.o): wait for SIO and write the character.
   Public identity evidence: config/datamine/ntsc-u-sdk-matches.tsv names
   0x0011BEE0 libkernl.a:kprintf.o kputchar; rac1-decomp has the same routine
   at src/core/00119D88.c.

   The volatile SIO register-block view is a truthful model of the two device
   registers: status is at 0x1000F130 and data is 0x50 bytes later. In the
   original translation unit, this C compiles to 48/56 bytes, 0/1. The store
   and its jr delay slot now match; the compact status load, shorter wait-loop
   schedule and placement of the return-value copy still differ. The earlier
   register-pinned probe was discarded because register pins are prohibited.
   The current RAC1 kputchar carries the MMIO destination through an empty
   inline-assembly constraint so the store remains register based. This repo's
   rules prohibit empty-asm barriers, and that source offers no compliant
   replacement for the outstanding address materialization and delay-slot
   differences.
*/
struct SIORegs {
    volatile unsigned int status;
    unsigned char pad[0x4C];
    volatile unsigned char data;
};

int func_0011BEE0(int c)
{
    volatile struct SIORegs *sio = (volatile struct SIORegs *)0x1000F130;
    while (sio->status & 0x8000)
        ;
    sio->data = c;
    return c;
}
