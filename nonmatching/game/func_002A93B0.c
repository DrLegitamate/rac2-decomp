/* Batch 3 (2026-10-28) handoff notes:
func_002A93B0 (404 B, 28 places): own unit not needed, it sits in src/game/002A7750.c in place of the marker (file's local qcopy is the same asm as common.h's). Delete the later `extern void func_002A93B0(void *);` line (it conflicts with the definition). draft.c = definition + externs.
9 masked lines left (size 404 = 404). Retail ends both "hit" arms in ONE shared tail `swc1 $f0,0x70; b end; swc1 $f1,0x74` (cross-jumped) so x and y must be shared variables (merged pseudos); retail has y in $f1 and the 0.000244140625 constant in $f2 (`lwc1 $f1,0xC; mtc1 $at,$f2; mul.s $f1,$f1,$f2`), ours has y in $f2 and the constant in $f1, so arm 2's 0.2f lands in $f2 too and the tails differ.
Writing the stores per arm with no shared locals gives retail's registers ($f0/$f1/$f2) but then no cross-jump (412 B).
Tried 16 combos of x/y declaration order x statement order in each arm: best 9, others 12 or +8..16 bytes.
*/

#include "common.h"
extern int D_001A8CA0[] __attribute__((sda));
extern float D_001BAFA0[] ;
extern float D_001BAFA8 ;
extern void func_00282D60(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
void func_002A93B0(char *o)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float x;
    float y;

    if (D_001A8CA0[0] == 0) {
        if (*(float *)(o + 0xE8) < 0.9f) {
            *(float *)(o + 0x70) = 0.0f;
            *(float *)(o + 0x74) = 0.0f;
            return;
        }
        qcopy(a, o + 0x10);
        a[2] = a[2] - 16.0f;
        if (a[2] < 0.5f)
            a[2] = 0.5f;
        qcopy(b, o + 0x10);
        b[2] = b[2] + 0.5f;
        if (func_002761F8(b, a, 0x22, 0, 0) != 0) {
            y = *(float *)(o + 0xC) * 0.000244140625f;
            x = D_001BAFA8 - *(float *)(o + 0x18);
            *(float *)(o + 0x70) = x;
            *(float *)(o + 0x74) = y;
        } else {
            *(float *)(o + 0x70) = 0.0f;
            *(float *)(o + 0x74) = 0.0f;
        }
    } else {
        func_00282D60(a, o, 0.0009765625f);
        func_00282D30(b, o + 0xE0, -8.0f);
        func_00282CC0(b, a, b);
        if (func_002761F8(a, b, 0x22, 0, 0) != 0) {
            func_00282CF0(c, D_001BAFA0, o + 0x10);
            x = func_00282DB0(c, (float *)(o + 0xE0));
            *(unsigned char *)(o + 0xBD) = 0xFF;
            y = 0.2f;
            *(float *)(o + 0x70) = x;
            *(float *)(o + 0x74) = y;
        } else {
            *(float *)(o + 0x70) = 0.0f;
            *(float *)(o + 0x74) = 0.0f;
        }
    }
}
