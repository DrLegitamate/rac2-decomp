/* func_L18_00432310 (L18, 568 bytes): NOT matched. Compiles to 568 bytes; control flow, calls, immediates
 * and the 0xFE/0xFD/<2 type test are instruction-identical. Remaining difference: register choice for
 * the qcopy destinations. Retail keeps the node pointer in $v1 and forms the destination (p+0x10)
 * in $a0 (second node: pointer $a0, destination $a1); mine puts the pointer in $a1 and the
 * destination in $v1/$a0 (about 9 instructions differ, no size change). Tried: pointer variable vs
 * repeated loads vs a struct pointer, store/qcopy order, loading s0 before the 0x96 update (needed).
 * The retail unit may use -frac2-qcopy, which this file's flags lack. Place in
 * src/levels/18_damosel/L18_003F80A0.c. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_0032C5E0(u8 *a0, s32 a1, void *a2);
extern void func_0033EE00(u8 *a0, u8 *a1, s32 a2, s32 a3);
extern void func_0032D1E8(void);
extern void func_0032DB88(u8 *a0);
extern void func_00309158(u8 *a0, u8 *a1);
extern void func_0032DD28(u8 *a0);
extern void func_L18_00433460(u8 *a0);
extern void func_L18_00433B70(u8 *a0);
extern void func_L18_00432F18(u8 *a0);
extern void func_L18_00434FC0(u8 *a0);
extern void func_L18_004350E0(char *pos, int count);
extern void func_00301720(void *fn, u8 *a0);
extern s32 func_00335738(s32 a0);
extern s32 func_00335778(s32 a0, s32 a1);
extern u8 D_L18_001B97C0[];

typedef struct {
    u8 pad00[0x10];
    u8 pos[0x10];
    u8 pad20[0x28];
    f32 f48;
    u8 pad4C[0xA4];
    u8 pos2[0x10];
} L18Node;

void func_L18_00432310(u8 *a0)
{
    u8 *s0;
    u8 v[16] __attribute__((aligned(16)));
    L18Node *p;

    s0 = *(u8 **)(a0 + 0x68);
    if (*(u16 *)(a0 + 0x96) <= 0xFFFEu) {
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
    }
    if (*(s16 *)(s0 + 0x804) < 0x7FFF) {
        *(u16 *)(s0 + 0x804) = *(u16 *)(s0 + 0x804) + 1;
    }
    if (*(u8 **)(s0 + 0x7C0) != 0) {
        func_0032C5E0(a0, 0, v);
        p = *(L18Node **)(s0 + 0x7C0);
        qcopy(p->pos, v);
        p->f48 = *(float *)(a0 + 0x48);
        if (*(u8 **)(s0 + 0x7C8) != 0) {
            func_0033EE00(*(u8 **)(s0 + 0x7C0), *(u8 **)(s0 + 0x7C8), 2, 0);
        }
        if (*(u8 **)(s0 + 0x7C4) != 0) {
            *(float *)(*(u8 **)(s0 + 0x7C4) + 0x48) = *(float *)(a0 + 0x48);
            func_0032C5E0(*(u8 **)(s0 + 0x7C0), 0, v);
            p = *(L18Node **)(s0 + 0x7C4);
            qcopy(p->pos, v);
            qcopy(p->pos2, *(u8 **)(s0 + 0x7C0) + 0xF0);
            func_0032D1E8();
            func_0032DB88(*(u8 **)(s0 + 0x7C4));
            func_00309158(*(u8 **)(s0 + 0x7C4) + 0xC0, *(u8 **)(s0 + 0x7C4) + 0xF0);
            func_0032DD28(*(u8 **)(s0 + 0x7C4));
        }
    }
    if (a0 != 0 && a0[0x20] != 0xFE && a0[0x20] != 0xFD && a0[0x20] >= 2) {
        if (*(s16 *)(s0 + 0x7FC) == 0) {
            if (*(u8 **)(s0 + 0x7C8) != 0) {
                func_L18_00433460(a0);
                func_00301720(func_L18_00433B70, a0);
            }
        }
        if (a0[0x31] != 0) {
            func_00301720(func_L18_00432F18, a0);
        }
        if (*(u8 **)(s0 + 0x7C0) == 0) {
            func_0032C5E0(a0, 0, v);
            if (func_00335738(0x14) == 0) {
                func_L18_004350E0((char *)v, func_00335778(10, 15));
            }
            func_00301720(func_L18_00434FC0, a0);
        }
    }
    if (a0[0x31] != 0) {
        if (func_00308A98(a0 + 0x10, D_L18_001B97C0) < 24.0f) {
            func_00337920(a0);
            a0[0x6F] = 0x16;
        }
    }
    *(u16 *)(s0 + 0x808) = 0;
    if (*(u8 **)(s0 + 0x7C4) != 0) {
        func_00340BD8(*(u8 **)(s0 + 0x7C4), s0 + 0x810, 5, 1, 2.5f);
    }
}
