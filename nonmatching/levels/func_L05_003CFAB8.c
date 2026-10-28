/* Retained exact-C attempt: 212/212 bytes.
 * Profile: -O2 -G8 -ffunction-sections.
 * US and US2 0/2; PAL absent. The incomplete reach table uses an explicit SDATA view. The camera pointer and duration occupy different GPRs; measured volatile camera fields preserve the three real stores.
 * Local checks only; no strict linked match. Reopen with independent
 * source, allocation or assembler evidence for the stated difference.
 */
#include "common.h"

extern float D_L05_001AFB68[] SDATA(D_L05_001AFB68);
extern char D_L05_001B96C0[];
extern int func_L05_003CFC28(int);
extern float func_00282E48(void *, void *);
extern void func_L05_003CFB90(char *, void *);
extern int func_002E5DA0(int, int, char *, int);

struct ShakeCamera {
    char pad00[0x160];
    volatile float strength;
    int pad164;
    volatile int duration;
    volatile int timer;
};

void func_L05_003CFAB8(char *object)
{
    float reach = D_L05_001AFB68[func_L05_003CFC28(*(short *)(object + 0xAA))];
    char *position = D_L05_001B96C0;

    if (func_00282E48(object + 0x10, position) <= reach &&
        *(short *)(object + 0xAA) != 0x956) {
        struct ShakeCamera *camera;
        float strength;
        int duration;
        func_L05_003CFB90(object, position);
        func_002E5DA0(7, 0, object, 0xFBF);
        camera = (struct ShakeCamera *)(position - 0x140);
        if (*(short *)(object + 0xAA) == 0x955) {
            strength = 0.05f;
            duration = 30;
        } else {
            strength = 0.15f;
            duration = 60;
        }
        camera->timer = 0;
        camera->strength = strength;
        camera->duration = duration;
    }
}
