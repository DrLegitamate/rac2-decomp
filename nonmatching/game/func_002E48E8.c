/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections (in place in src/game/002E10B8.c).
 * Retail: 384 bytes; compiled: 392 bytes.
 * Coverage: us: 0/1 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Clears the header and the 52 0x70-byte records of the table at 0x188660, then
 * configures the engine slots. The catalogue names the function at 0x132978
 * func_00132968; that is the call retail makes.
 *
 * Every instruction from the record loop to the return matches. Only the prologue
 * differs: retail loads %hi(D_00188660) straight into $s0 and keeps it there until
 * the first call's delay slot turns it into the table base. Here cc1 loads it into
 * $v0, copies it to $s0 and adds the low part to $v0 for the quadword loop (+2
 * instructions). Tried without closing it: the quadword loop as do/while, for and
 * indexed forms, counting up or down; the base taken at the top, after the loops or
 * before the calls; func_002E5FE0's volatile quadword clear (reloads the high part
 * instead); -frac2-zero-ti-barrier, -frac2-zero-ti-por and -mno-split-addresses on
 * the unit (equal or worse). Next: allocator evidence for why the high part gets a
 * second pseudo across the first loop.
 */

typedef unsigned char u8;
typedef int TI128_48E8 __attribute__((mode(TI)));

extern u8 D_00188660[];
extern int D_001A7B98;
extern void func_00131DE8(int);
extern void func_00132938(int);
extern void func_00132968(int, int);
extern void func_001329B0(int, int, int);
extern void func_00132888(int, int);
extern void func_002E4860(void);
extern void func_001328C0(int, int *);

void func_002E48E8(void) {
    int cfg[5];
    TI128_48E8 *q;
    u8 *p;
    u8 *end;
    int i;
    u8 *base;

    q = (TI128_48E8 *)D_00188660;
    for (i = 3; i >= 0; i--) {
        *q++ = 0;
    }
    {
        u8 *t = D_00188660;
        *(int *)(t + 0x40) = 0;
        *(int *)(t + 0x44) = 0;
        p = t;
    }
    end = p + 0x16C0;
    do {
        *(int *)(p + 0x70) = 0;
        p[0x74] = 0;
        p += 0x70;
    } while ((int)p < (int)end);
    func_00131DE8(2);
    base = D_00188660;
    func_00132938(D_001A7B98 == 0);
    func_00132968(0, 1);
    func_001329B0(1, 0x18, 0x2F);
    func_001329B0(2, 0x18, 0x2F);
    func_001329B0(4, 0x18, 0x2F);
    func_001329B0(5, 0x18, 0x2F);
    func_001329B0(6, 0x18, 0x2F);
    func_002E4860();
    func_00132888(0, *(int *)(base + 0x48));
    func_00132888(1, *(int *)(base + 0x4C));
    func_00132888(2, *(int *)(base + 0x50));
    func_00132888(3, *(int *)(base + 0x54));
    func_00132888(4, *(int *)(base + 0x58));
    func_00132888(5, *(int *)(base + 0x5C));
    func_00132888(6, *(int *)(base + 0x50));
    cfg[0] = 6;
    cfg[1] = 0x3B;
    cfg[2] = 0x6666;
    cfg[3] = 0x8000;
    cfg[4] = 0x8000;
    func_001328C0(0, cfg);
}
