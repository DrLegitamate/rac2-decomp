/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections; the complete retained compilation context
 * follows below, independently of any linked source unit.
 * Retail: 376 bytes; compiled: 380 bytes.
 * Contract-correction replay: US 0/1, US2 0/1, PAL 0/1; each compiles to 380/376 bytes.
 * The complete retained body is compiled as an isolated private G8 unit, never linked.
 * Residual: the loop. Retail tests `i < 4` first in each iteration (the test is also
 * copied into the latch's `bnel` slot) and increments i after the second call; this C
 * computes the corner arguments before the test and increments early, one word longer;
 * the saved registers are rotated (retail: table in $s0, position in $s3).
 * Measured: the four extents as one Vec4[4] (two arrays cost two more saves); the push
 * vector D_001B27B0 as an incomplete `sda` array keeps retail's per-iteration
 * `lui ; addiu` (an ordinary array is hoisted into $s5, 20 bytes long). The increment
 * moved after the if or a while loop changes nothing.
 * Reopen: a loop form that puts the `i < 4` test at the iteration's head.
 */

#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern f32 D_001B0108 __attribute__((sda));
extern f32 D_001B010C __attribute__((sda));
extern f32 D_001B27B0[] __attribute__((sda));
extern f32 D_0022AFA0[][4];

extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);

void func_00326EC0(u8 *self) {
    f32 axis[4][4] __attribute__((aligned(16)));
    f32 tmp[4] __attribute__((aligned(16)));
    f32 end[4] __attribute__((aligned(16)));
    f32 (*out)[4] = D_0022AFA0;
    f32 *pos;
    s32 i;

    qcopy(axis[0], self + 0xC0);
    qcopy(axis[3], self + 0xD0);
    func_00282D30(axis[1], axis[0], -1.0f);
    func_00282D30(axis[2], axis[3], -1.0f);
    qcopy(D_0022AFA0[4], axis[0]);
    qcopy(D_0022AFA0[5], axis[1]);
    qcopy(D_0022AFA0[6], axis[2]);
    qcopy(D_0022AFA0[7], axis[3]);
    pos = (f32 *)(self + 0x10);
    for (i = 0; i < 8; i++) {
        if (i < 4) {
            func_00282CC0(*out, axis[i >> 1], axis[2 + (i & 1)]);
        }
        func_00282F20(*out, *out, D_001B010C);
        func_00282CC0(*out, *out, pos);
        func_00282F20(tmp, D_001B27B0, -D_001B0108);
        func_00282CC0(*out, *out, tmp);
        out++;
        func_00282CC0(end, tmp, pos);
    }
}
