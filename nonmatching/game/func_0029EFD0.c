/* func_0029EFD0 - 248 bytes, boot + 27 levels, USA v1.01.
   Retained candidate: 256 bytes, 0/28 USA v1.01 placements, freshly replayed
   29 October 2026 in a standalone default-profile unit, checked in a
   default-profile temporary unit (`-O2 -G0 -ffunction-sections`). The first
   structured candidate was 280 bytes. A 29 October probe replacing
   `((p - base) >> 8) << 7` with `(p - base) >> 1` measured 252 bytes, but is
   not retained: the source reloads mutable `D_001B1B60` after a helper call,
   so the required multiple-of-0x100 difference is not established. The
   retained candidate keeps a 0x10-byte frame against retail's 0x30-byte
   frame and differs in register allocation and branch/delay-slot scheduling. */
extern unsigned char *D_001B1B60 __attribute__((section(".data")));
extern unsigned char *D_001B1B64 __attribute__((section(".data")));
extern unsigned int D_001B1B6C __attribute__((section(".data")));
extern int D_001B1688 __attribute__((section(".data")));
extern int D_001B1A80 __attribute__((section(".data")));
extern void func_0029F0C8(void *, void *);
extern void func_00282A60(void *, int, int);
extern void func_0026FEB8(void *, int);
int func_0029EFD0(void *arg) {
    unsigned char *p = D_001B1B60;
    unsigned char *end = D_001B1B64;
loop:
    if (p >= end)
        goto done;
    if (p[0x20] < 0xFE)
        goto next;
    if ((unsigned int)*(int *)(p + 0xA0) > (unsigned int)D_001B1688)
        goto next;
    if (p[0x20] != 0xFF)
        p[0x120] = p[0x20];
    func_0029F0C8(p, arg);
    *(void **)(p + 0x68) = (void *)(D_001B1B6C + (((unsigned int)(p - D_001B1B60) >> 8) << 7));
    func_00282A60(*(void **)(p + 0x68), 0, 0x80);
    if (D_001B1A80 != 0)
        D_001B1A80--;
next:
    p += 0x100;
    goto loop;
done:
    func_0026FEB8(D_001B1B60 - 0x6240, D_001B1688);
    return 0;
}
