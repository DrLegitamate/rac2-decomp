/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections, in src/levels/shared/L05_003D33E8-g8.c (the
 * unit then needs #include "common.h" for qcopy).
 * Retail: 292 bytes; compiled: 292 bytes.
 * Coverage: us: 0/4 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Replaces an earlier 296-byte draft that passed the last two arguments of
 * func_00281EB8 in the wrong order (retail: a2 = a3 argument, a3 = 1).
 *
 * The loop body and the epilogue match. Only the prologue differs (28 lines): retail
 * sets i = 0 in the delay slot of the first func_00283CE0 call, so $s0 is saved
 * after $s2-$s4 and the float registers; cc1 sets i = 0 at the top of the function,
 * which pulls the $s0 save first and reorders the other saves and argument copies.
 * What closed the rest: qcopy for the buf[1] copy (retail stores through $s1) and
 * the scale as one expression. Tried without closing the prologue: all orders of
 * the argument copies, the buffer load and the step; i = 0 as its own statement;
 * while and guarded do/while loops; -g, -frac2-qcopy and both on the unit.
 * Next: what makes sched1 keep a constant set to the end of the entry block.
 */

#include "common.h"

extern float func_00283CE0(int);
extern float func_002A7940(void);
extern void func_002ACB48(void *, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);
extern int D_L05_001B0FBC __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);

typedef int TI128 __attribute__((mode(TI)));

void func_L05_00418D68(void *a0, void *a1, int a2, int a3, float f12, float f13, float f14)
{
    TI128 buf[2];
    float step;
    float p;
    float q;
    float scale;
    float angle;
    float dir;
    float len;
    int i;

    dir = f12;
    angle = f13;
    len = f14;
    buf[0] = *(TI128 *)a0;
    step = 1.0f / func_00283CE0(a2);
    for (i = 0; i < a2; i++) {
        p = func_00283CE0(i) * step;
        scale = dir + (angle - dir) * p;
        q = func_002A7940();
        qcopy(&buf[1], &buf[0]);
        func_002ACB48(&buf[1], len);
        func_00281EB8(&buf[1], D_L05_001B0FBC, a3, 1, scale, 0.0f, q);
        func_00282CC0(&buf[0], &buf[0], a1);
    }
}
