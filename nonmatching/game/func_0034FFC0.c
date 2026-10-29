/*
 * func_0034FFC0 (boot, 464 bytes, 28 places). Near miss, not in src/.
 *
 * Measured with tools/check.py: this C is 456 bytes, retail 464 (boot). Retail's
 * two exits run "sync ; ei" (0x350088 and the shared exit at 0x35016C); C cannot
 * emit those without inline asm, which is forbidden, and no builtin supplies them
 * (docs/COMPILER-NOTES.md: neither compiler supplies a sync pattern). Without them
 * the compiler copies the epilogue into each early exit and the layout drifts from
 * retail, so the 8-byte gap is not the only difference.
 *
 * Tried: the GS-register arm and the field-toggle arm swapped (the branch-likely
 * shape of retail's 0x34FFE8): 452 bytes, further away. Not kept.
 *
 * Needs: D_001B23CC via $gp (-G8 file, sda), GS CSR at 0x12001000 (bit 13 = field),
 * D_001AE7D0..E0 are volatile handshake words in the boot.
 */

extern char *D_001B23CC[] __attribute__((sda));
extern int D_001B23C8;
extern void func_002B6480(void *, int);
extern volatile int D_001AE7D0;
extern volatile int D_001AE7D4;
extern volatile int D_001AE7D8;
extern volatile int D_001AE7DC;
extern volatile int D_001AE7E0;
extern int D_001A7BB8;
extern int func_00126F38(unsigned int);
extern int func_001244B8(int, int);
extern void func_00127218(int *, int);
extern int func_00351F38(volatile int *);

int func_0034FFC0(void)
{
    int *s2 = (int *)func_00126F38(2);
    int *s0;
    int s1;

    if (D_001A7BB8 == 0)
        D_001AE7DC = (int)((*(volatile unsigned long long *)0x12001000 >> 13) & 1);
    else
        D_001AE7DC = D_001AE7DC ^ 1;

    if (D_001AE7D0 != 0) {
        D_001AE7D4 = D_001AE7D4 + 1;
        D_001AE7E0 = func_001244B8(1, 0);
        if (D_001AE7E0 == 0) {
            s0 = (int *)func_00351F38((volatile int *)(D_001B23CC[0] + 0xD9168));
            if (s0 != 0) {
                if (D_001AE7DC == 0 && s0[0] == 2) {
                    func_001244B8(0, 0);
                    func_002B6480((void *)(D_001B23C8 + (s0[1] << 14) + 0x1C81C0), 0);
                    func_00127218(s2, (int *)((char *)s0 + 0x40));
                    s0[0] = 1;
                } else if (D_001AE7DC == 1 && s0[0] == 1) {
                    s1 = s0[0];
                    func_001244B8(0, 0);
                    func_002B6480((void *)(D_001B23C8 + (s0[1] << 14) + 0x1C81C0), 0);
                    func_00127218(s2, (int *)((char *)s0 + 0x13880));
                    s0[0] = 0;
                    D_001AE7D8 = s1;
                }
            }
        }
    }
    return 0;
}
