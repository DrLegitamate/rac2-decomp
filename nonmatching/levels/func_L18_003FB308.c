/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections, appended to
 * src/levels/18_damosel/L18_003F80A0-g8.c (replace the marker in L18_003F80A0.c with a note).
 * Retail: 504 bytes; compiled: 504 bytes.
 * Coverage: us: 0/1 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Everything but one block matches: in the last countdown step (state 1, n == 1)
 * retail loads the matrix index into $v1 and the table pointer into $v0 and computes
 * n - 1 in $a0; cc1 uses $a0 for the table pointer and $v1 for n - 1 (3 instructions).
 * Sharing self + 0x10 across both branches and adding the shifted index before the
 * table pointer closed the rest.
 * Tried: five spellings of the slot address (operand orders, an indexed form, a
 * local), n - 1 before or after the copy, qcopy_nc for either copy.
 */

#include "common.h"

extern void func_00282CC0(void *arg0, void *arg1, void *arg2);

extern s32 D_L18_001B0580 __attribute__((sda));
extern f32 D_L18_001B0584 __attribute__((sda));
extern s32 D_L18_001B0588 __attribute__((sda));
extern u8 *D_L18_001B281C[] __attribute__((sda));

extern void func_00282F20(void *, void *, float);
extern void func_002A7750(char *, int, int);
extern void func_00282CF0(void *, void *, void *);
extern int func_002B3868(void *);
extern int func_002E5DA0(int, int, char *, int);
extern void func_L18_003FB620(u8 *object);

/* A platform that slides over D_L18_001B0580 frames: state 0 stores its rest position and
   per-frame step, state 1 slides back toward it, state 2 slides out while triggered. The
   object's +0x96 counts frames up to 0xFFFF. */
void func_L18_003FB308(u8 *self)
{
    u8 *st = *(u8 **)(self + 0x68);
    u8 *pos;
    s32 n;

    switch (self[0x20]) {
    case 0:
        qcopy(st, self + 0x10);
        func_00282F20(st + 0x10, self + 0xC0, D_L18_001B0584 / (f32)D_L18_001B0580);
        func_002A7750((char *)self, 1, -1);
        *(s32 *)(st + 0x20) = 0;
        break;
    case 1:
        n = *(s32 *)(st + 0x20);
        pos = self + 0x10;
        if (n >= 2) {
            func_00282CF0(pos, pos, st + 0x10);
            func_00282CC0(D_L18_001B281C[0] + (*(s32 *)(st + 0x24) << 8) + 0x10,
                          D_L18_001B281C[0] + (*(s32 *)(st + 0x24) << 8) + 0x10, st + 0x10);
            *(s32 *)(st + 0x20) -= 1;
        } else if (n > 0) {
            qcopy(pos, st);
            qcopy((*(s32 *)(st + 0x24) << 8) + D_L18_001B281C[0] + 0x10, st);
            *(s32 *)(st + 0x20) = n - 1;
        }
        break;
    case 2:
        if (func_002B3868(self) != 0)
            func_002E5DA0(0, 0, (char *)self, 0x1152);
        if (*(s32 *)(st + 0x20) < D_L18_001B0580) {
            func_00282CC0(self + 0x10, self + 0x10, st + 0x10);
            func_00282CF0(D_L18_001B281C[0] + (*(s32 *)(st + 0x24) << 8) + 0x10,
                          D_L18_001B281C[0] + (*(s32 *)(st + 0x24) << 8) + 0x10, st + 0x10);
            *(s32 *)(st + 0x20) += 1;
        }
        if (*(s32 *)(st + 0x28) != 0)
            func_L18_003FB620(self);
        if (D_L18_001B0588 < *(u16 *)(self + 0x96))
            func_002A7750((char *)self, 1, -1);
        break;
    }
    if (*(u16 *)(self + 0x96) < 0xFFFF)
        *(u16 *)(self + 0x96) += 1;
}
