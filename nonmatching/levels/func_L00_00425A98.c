/* func_L00_00425A98 - near miss (W1, 28 October 2026): 568/568 bytes (was 556/568), 96 lines off at us
 * level 0 (was 126). Profile: -O2 -G8 -ffunction-sections.
 * What helped: the resident hero fields through a Hero union view (`((Hero *)D_00189E20)->b[0x22B4]`)
 * instead of `D_00189E20 + off`, which the compiler folds into the symbol; this is the form that
 * closed func_L00_004237C8. A plain `char *hero = D_00189E20` local gives 564/568.
 * Left: retail issues `lui $s6, 0x19` (the hero %hi) in the prologue, before the first load; here it
 * sits in the delay slot after the first two branches, which shifts every later line by one word and
 * adds nops from the hazard pass (-frac2-hazard-labels and -g do not change the count). */
#include "common.h"

extern char D_L00_001B8E20[];
extern char D_00189E20[];
typedef union { unsigned char b[0x2600]; int i[0x980]; } Hero;
extern float D_L00_001B14E0 __attribute__((sda));
extern float D_L00_001B14E4 __attribute__((sda));
extern float D_L00_001B1508 __attribute__((sda));
extern float D_L00_001B150C __attribute__((sda));
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern void func_L00_00424A08(int, float, float);

void func_L00_00425A98(char *object, float *first, float *second)
{
    char *state = *(char **)(object + 0x70);
    char *control = state + 0x240;
    char *movement = state + 0x160;
    char *camera = D_L00_001B8E20;
    float weight;
    float target;
    float candidate;
    if (*(short *)(control + 6)) goto fallback;
    if (*(short *)(control + 4) && *(float *)(camera + 0xA4) == 0.0f) {
        if (func_00282DB0((char *)((Hero *)D_00189E20)->i[0x2290 / 4] + 0xC0, object) <= -0.3f)
            goto active;
    }
    if (!(func_00282C48(*(float *)(camera + 0xA4)) > 0.0001f)) goto fallback;
    if (!(func_00282DB0(camera + 0x80, object) <= -0.3f)) goto fallback;
active:
    *(short *)(control + 4) = 120;
    weight = *(float *)(camera + 0xA4) * 14.2857f;
    if (weight > 1.0f) weight = 1.0f;
    target = ((Hero *)D_00189E20)->b[0x22B4] == 1 ? 4.0f : *(float *)(control + 0xC);
    candidate = *(float *)(movement + 0x58);
    candidate += (target - candidate) * weight;
    if (candidate > *(float *)(control + 8)) *(float *)(control + 8) = candidate;
    func_L00_00424A08(0, *(float *)(control + 8), 0.003f);
    *first = D_L00_001B14E0 + (D_L00_001B1508 - D_L00_001B14E0) * weight;
    *second = D_L00_001B14E4 + (D_L00_001B150C - D_L00_001B14E4) * weight;
    return;
fallback:
    if (*(short *)(control + 4)) {
        *(short *)(control + 4) = 0;
        *(float *)(control + 8) = *(float *)(movement + 0x58);
    }
    if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x84) {
        *first = 0.04f;
        *second = 0.2f;
    } else {
        *first = D_L00_001B14E0;
        *second = D_L00_001B14E4;
    }
}