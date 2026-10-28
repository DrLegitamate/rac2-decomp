/* func_L00_00424F98 (380 bytes) - near miss (M22, 2026-10-26; W1 28 October 2026).
 * Profile: src/levels/shared/L00_00424F98-g8.c, "-O2 -G8 -ffunction-sections".
 * 376 of 380 bytes, 8 lines off at us level 0 (was 372, 63 lines). One word is missing: retail has
 * `lwc1 $f0 ; lwc1 $f1 ; nop ; div.s`, here the nop before div.s is not emitted (-g and
 * -frac2-hazard-labels do not add it; with the divisor as a bare sda scalar it is emitted but the
 * load then fills the bc1f delay slot, which retail leaves as a nop).
 * W1 found: the run count is read as `c->count` every time (no local) - the compare then uses the
 * `andi 0xFFFF` copy of the lhu and the +1 store uses the raw load, as in retail; and the divisor
 * as an element of an incomplete SDATA array (base placed 4 bytes below it) keeps the $gp load out
 * of the delay slot. */
#include "include_asm.h"
#include "common.h"

/* The resident challenge counter: runs, best time and a bit per level. */
typedef struct {
    char pad[0x60];
    unsigned short count;
    unsigned short pad62;
    unsigned int best;
    unsigned int flags;
} L00_00424F98_Counter;

/* The vehicle's input block, at +0x1C0 of its motion record. */
typedef struct {
    char pad0[0x10];
    int flags;
    float steer_out;
    char pad18[4];
    float steer;
    char pad20[4];
    float throttle;
} L00_00424F98_Input;

extern float D_00138280[];
extern float D_00138284[];
extern s32 D_001A7BA8 MACRO_ADDR;
extern s32 D_001A7BA4 MACRO_ADDR;
extern s32 D_001A79F0 MACRO_ADDR;
extern unsigned int D_001A7390 MACRO_ADDR;
extern L00_00424F98_Counter D_0018C750;
extern s32 ref_L00_00424F98_00 __attribute__((sda));
extern s32 ref_L00_00424F98_01 __attribute__((sda));
extern float ref_L00_00424F98_02 __attribute__((sda));
extern float ref_L00_00424F98_03[] SDATA(ref_L00_00424F98_03);

/* The vehicle's steering and throttle inputs, with the stunt counter: holding the
   stick centred for a second counts one run and records the best time. */
void func_L00_00424F98(char *obj, float *x, float *y)
{
    L00_00424F98_Input *t = (L00_00424F98_Input *)(*(char **)(obj + 0x70) + 0x1C0);
    L00_00424F98_Counter *c;
    unsigned short n;
    float v;

    if (t->flags & 1) {
        *x = 0.0f;
    } else {
        *x = D_00138280[0];
        if (D_001A7BA8 == 0)
            *x = -*x;
    }
    if (*x == 0.0f) {
        ref_L00_00424F98_00 = 0;
        ref_L00_00424F98_01 = 0;
        if (t->steer != 0.0f)
            *x = t->steer;
    } else {
        t->steer_out = ref_L00_00424F98_02;
        c = &D_0018C750;
        if (c->count < 3U) {
            ref_L00_00424F98_00++;
            if (ref_L00_00424F98_01 == 0 && ref_L00_00424F98_00 > 0x3C) {
                if (c->count < 0xFFFF)
                    c->count = c->count + 1;
                if (D_001A7390 > c->best)
                    c->best = D_001A7390;
                ref_L00_00424F98_01 = 1;
                c->flags = (c->flags | (1 << D_001A79F0)) | 0x80000000;
            }
        }
    }
    if (t->flags & 2) {
        *y = 0.0f;
    } else {
        v = D_00138284[0];
        *y = -v;
        if (D_001A7BA4 == 0)
            *y = v;
    }
    if (*y == 0.0f)
        *y = t->throttle / ref_L00_00424F98_03[1];
}
