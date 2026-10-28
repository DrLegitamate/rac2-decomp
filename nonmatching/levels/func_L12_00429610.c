/* func_L12_00429610: NOT matched (same size, 600 bytes; 3 instructions differ).
   (1) The `flag ? 0.5f : -0.5f` select: retail's beqz lands on the mtc1->swc1 hazard nop
   (label before the nop); this is the "labels on hazard nops" case that only
   -frac2-hazard-labels fixes (a per-file flag in config/cflags.txt: would need its own file).
   (2) In the second block retail schedules `addiu s0,s0,0x20` before `sh 10,0xA(p)` (sh in
   the jal delay slot); cc1 puts the sh first. Tried d += 0x20 before/after the store, a
   separate result variable (gets v1, wrong register), d = r; d += 0x20.
   Key to getting this far: func_002BDCE8's float arguments are interleaved
   (void *, f32, f32, f32, s32, void *, f32, u32, s32): the ABI bank order is unchanged and
   the 4th float evaluated after the pointer arguments fixes the f21/f22 allocation. */
#include "common.h"
extern s32 func_002A77E0(s32);
extern s32 func_00283CF0(f32);
extern u8 *func_002BDCE8(void *, f32, f32, f32, s32, void *, f32, u32, s32);

void func_L12_00429610(u8 *self, s32 flag)
{
    f32 velocity[4];
    f32 pos[4];
    u8 *p;
    u8 *q;
    u8 *d;
    s32 side;

    velocity[0] = 0.0f;
    velocity[2] = flag ? 0.5f : -0.5f;
    velocity[1] = 0.0f;
    velocity[3] = 1.0f;
    side = func_002A77E0(16);
    if (func_002A77E0(2))
        side = -side;
    qcopy(pos, self + 0x10);
    pos[2] -= 0.25f;
    p = func_002BDCE8(pos, 0.1f, 1.0f, 0.9f, side, velocity, 420000.0f, 0xDF204080, 0);
    if (p) {
        u8 *t = p + 0x20;
        *(u16 *)(p + 10) = 10;
        p[9] = func_00283CF0(4.0f) + 0x70;
        *(s32 *)(t + 4) = 2;
        t[10] = 0xDF;
        t[11] = p[10];
    }
    d = func_002BDCE8(pos, 0.1f, 1.0f, 0.9f, side, velocity, 420000.0f, 0xDF204080, 0);
    if (d) {
        d += 0x20;
        *(u16 *)(p + 10) = 10;
        p[9] = func_00283CF0(4.0f) + 0x70;
        *(s32 *)(d + 4) = 2;
        d[10] = 0xDF;
        d[11] = p[10];
    }
    q = func_002BDCE8(pos, 0.05f, 1.0f, 0.97f, 16, velocity, 210000.0f, 0xDFFFFFFF, 0);
    if (q) {
        u8 *d = q + 0x20;
        q[9] = func_00283CF0(4.0f) + 0x70;
        *(u16 *)(q + 10) = 5;
        q[8] = func_002A77E0(255);
        *(s32 *)(d + 4) = 2;
        d[10] = 0xDF;
        d[11] = p[10];
    }
}
