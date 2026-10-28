/* func_L05_004247C8 (w2 batch 3, 2026-10-28). Profile -O2 -G0 -ffunction-sections. 420/420 bytes, 2 differing
   lines (was 9): only the order of `ori $s4,$s4,0x8080` and `addiu $s5,$zero,0x1D` in the prologue.
   Fixed here: the first colour is built inline in the call (no `color` local); the second colour calls
   ref_07 first (`alpha`), then reads the field and masks it. Tried for the prologue pair: i < 30 up-count,
   while (i-- > 0), do/while, i = 29 first, all 6 orders of the three pre-loop statements, all 35
   int/float interleavings of the ref_08 prototype, -g, -fno-strength-reduce. No change. */
#include "common.h"

/* Mid worker 11 near miss (func_L05_004247C8).
   Profile: -O2 -G0 -ffunction-sections.
   Status: same 420 bytes; constants and calls match, only the scheduling of the colour shift/or around the jal delay slot and the order of two prologue constants differ. */

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern void ref_L05_004247C8_00(char *, void *);
extern char ref_L05_004247C8_01[];
extern float ref_L05_004247C8_02(void);
extern float ref_L05_004247C8_03(float);
extern float ref_L05_004247C8_04(float);
extern void ref_L05_004247C8_05(float *, float *, char *);
extern void ref_L05_004247C8_06(float *, float *, char *);
extern int ref_L05_004247C8_07(float);
extern void ref_L05_004247C8_08(float *, int, int, int, float, float, float);
extern float ref_L05_004247C8_09(float, float);
extern float ref_L05_004247C8_10(float);

void func_L05_004247C8(char *obj) {
    float v[4];
    char *state;
    int color;
    int i;
    float full;

    full = 128.0f;
    state = FLD(obj, char *, 0x68);
    ref_L05_004247C8_00(obj + 0x10, ref_L05_004247C8_01);
    for (i = 29; i >= 0; i--) {
        float angle = ref_L05_004247C8_02();
        v[0] = 0.0f;
        v[1] = ref_L05_004247C8_03(angle);
        v[2] = -ref_L05_004247C8_04(angle);
        ref_L05_004247C8_05(v, v, obj + 0xC0);
        ref_L05_004247C8_06(v, v, obj + 0x10);
        ref_L05_004247C8_08(v, 0x13, (ref_L05_004247C8_07(full) << 24) | 0x808080, 1, 0.25f, 0.1f, ref_L05_004247C8_02());
        {
            float half = 0.5f;
            int alpha = ref_L05_004247C8_07(full * half);
            color = FLD(state, int, 8);
            color &= 0xFFFFFF;
            color |= alpha << 24;
            ref_L05_004247C8_08(v, 0x13, color, 1, half, 0.1f, ref_L05_004247C8_02());
        }
    }
    FLD(state, float, 4) = 0.13380859792232513f;
    FLD(state, float, 0) = ref_L05_004247C8_09(FLD(state, float, 0), 0.13380859792232513f);
    ref_L05_004247C8_10(FLD(state, float, 0));
}
