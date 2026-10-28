/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections, as its own unit src/levels/shared/L00_002BA220.c
 * (it needs common.h for qcopy; replace the marker in L00_002B91C0.c with a note).
 * Retail: 492 bytes; compiled: 488 bytes.
 * Coverage: us: 0/22 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * The calls, constants (exact bit patterns) and arithmetic match. Retail holds the
 * hero block twice: $s5 = D_00189E20 + 0x80 (the qcopy source) and $s4 = $s5 - 0x80
 * (cse's related-value form), and reads +0x334 and +0x264 through $s4; cc1 keeps only
 * base + 0x80 and folds the field offsets (0x2B4, 0x1E4). The loop counter's decrement
 * and a nop also move.
 * Tried: a base local inside or outside the loop, for the fields, the copy or both
 * (500 bytes); a pointer at base + 0x80 with the fields at -0x80 (488).
 * Next: a spelling where the block's own address is needed in a register after
 * base + 0x80 is.
 */
#include "common.h"

extern char D_00189E20[];
extern s32 D_001A79F0;

extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002BAE50(void *, void *, s32, s32, s32, s32, s32, s32);

/* Throws ten sparks around the hero: each with random lifetimes, a random direction
   and a random distance on the ground plane, kept at the hero's height except in
   mode 6. */
void func_L00_002BA220(void)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 vel[4] __attribute__((aligned(16)));
    f32 speed;
    f32 yaw;
    f32 pitch;
    f32 dist;
    s32 life;
    s32 fade;
    s32 i;

    for (i = 9; i >= 0; i--) {
        life = func_00283CF0(func_002A7878(4200.0f, 7350.0f) * 0.0010000000474974513f);
        fade = func_00283CF0(func_002A7878(21000.0f, 31500.001953125f) * 0.0010000000474974513f);
        speed = func_002A7878(0.002500000176951289f, 0.011666666716337204f);
        qcopy(pos, D_00189E20 + 0x80);
        if (D_001A79F0 != 6)
            pos[2] = *(f32 *)(D_00189E20 + 0x334);
        yaw = func_002A7940();
        pitch = func_002A7878(0.349065899848938f, 1.396263599395752f);
        dist = func_002A7878(0.05f, *(f32 *)(D_00189E20 + 0x264) + 0.2f);
        func_002AF000(vel, speed, yaw, pitch);
        pos[0] += func_00283180(yaw) * dist;
        pos[1] += func_00283198(yaw) * dist;
        func_002BAE50(pos, vel, 0x7000C0F0, 0x70F0, 0x28, life, fade, 1);
    }
}
