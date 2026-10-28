/* Current retained result, 28 October 2026: 196/200 bytes. Reviewed copies replace the obsolete
 * MMI-only refusal, but pointer-load coalescing removes the retail v0-to-s0 copy and hoists a
 * copy address. A 200-byte experiment changed the real load count and was rejected. No strict
 * match. Older diagnostic notes below are historical and do not rule out C. */

/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 profile: -O2 -G0 -ffunction-sections -fno-cse-follow-jumps -fno-cse-skip-blocks -fno-regmove.
 * 196/200 compiled/retail bytes. Approved qcopy, non-clobbering copy and qualified TI-copy profiles were tested. Pointer-load coalescing removes the retail v0-to-s0 copy and hoists the copy address into a branch slot. Disabling cross-block CSE with two loads gives 200 bytes but changes the measured load count; no candidate.
 * US object comparison only in this retry; no linked strict-build claim.
 * Reopen with a measured allocation, scheduling or source-interface witness.
 */
#include "common.h"
typedef unsigned int ChildQuad __attribute__((mode(TI)));
extern void func_0029FCC0(void *, int, void *);
extern unsigned char *func_L08_003D4600(void *, void *);
extern float func_00283CE0(int);
void func_L08_003C66F0(unsigned char *m)
{
    float position[4];
    unsigned char **children = (unsigned char **)(*(unsigned char **)(m + 0x68) + 0x80);
    int i;
    for (i = 0; i < 2; i++, children++) {
        unsigned char *child;
        unsigned char *loaded;
        func_0029FCC0(m, i + 7, position);
        loaded = *children;
        if (!loaded) *children = func_L08_003D4600(m, position);
        else {
            child = loaded;
            qcopy(child + 0x10, position);
            *(float *)(child + 0xf8) = *(float *)(m + 0xf8);
            *(float *)(child + 0xf4) = *(float *)(m + 0xf4);
            *(float *)(child + 0xf0) = func_00283CE0(i) * 3.1415927f;
        }
    }
}

/* from src/levels/shared/L08_002F2D10.c: not written this wave. Retail 200 bytes, 3 place(s), first word at L08:003c66f0.
 * Rule: MMI/LQ/SQ (op 0x1e).
 * No C attempt was made (wave-5 tour-2 discard rule).
 * Retail opens with:
 *   0x003c66f0  addiu       $sp, $sp, -0x50
 *   0x003c66f4  sd          $s1, 0x18($sp)
 *   0x003c66f8  sd          $s2, 0x20($sp)
 *   0x003c66fc  sd          $s3, 0x28($sp)
 *   0x003c6700  daddu       $s2, $a0, $zero
 *   0x003c6704  swc1        $f20, 0x40($sp)
 * Kept as data for the maintainers. */
