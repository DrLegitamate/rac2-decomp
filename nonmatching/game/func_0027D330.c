/* Timed bar/progress packet routine, retained near miss.
 *
 * The earlier 384/392 result was compiled in the containing -G0 unit, which
 * is not the right profile for D_001B1598 and D_001B22A8. Replayed in the
 * existing -G8 sibling with the canonical 64-bit func_002FC560 prototype,
 * this source compiles to 356/392 bytes and matches 0/28 USA v1.01 places.
 * PAL and USA v2.00 checks could not run because their retail boot images are
 * absent. The target computes count-1 before its setup calls; cc1 saves count
 * and delays the subtraction until after those calls. The remaining diff is
 * too broad to infer further from the current size-mismatched comparison. */
#include "include_asm.h"

extern unsigned char *D_001B22A8 __attribute__((sda));
extern int D_001B1598 __attribute__((sda));
extern char D_00138990[];
extern void func_002FC3C0(unsigned long);
extern int func_001261F0(int);
extern void func_002FC1D8(void);
extern void func_002FC280(void);
extern void func_002FC220(void);
extern void func_00284EA8(void);
extern void func_00284F40(int);
extern void func_00284FC0(void);
extern void func_002FC560(unsigned int, unsigned long long);

void func_0027D330(int count)
{
    int frame = count - 1;

    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598++;
    func_002FC1D8();
    if (frame < 0)
        return;

    func_00284EA8();
    func_00284F40(1);
    func_00284FC0();
    func_002FC560(0x42, 0x800000000044UL);
    do {
        int fill = 0x80 - (frame << 7) / (frame + 1);
        frame--;
        func_002FC560(1, (unsigned long)fill << 24);
        *(unsigned int *)(D_001B22A8 + 0x00) = 0x30000014;
        *(unsigned int *)(D_001B22A8 + 0x04) = (unsigned int)(unsigned long)D_00138990;
        *(unsigned int *)(D_001B22A8 + 0x08) = 0;
        *(unsigned int *)(D_001B22A8 + 0x0C) = 0x50000014;
        D_001B22A8 += 0x10;
        func_002FC3C0(1);
        func_001261F0(0);
        D_001B1598++;
        func_002FC280();
        func_002FC220();
    } while (frame >= 0);

    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598++;
    func_002FC1D8();
    func_00284EA8();
    func_00284F40(1);
}
