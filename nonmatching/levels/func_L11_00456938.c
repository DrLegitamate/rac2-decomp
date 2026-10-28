/* Retained reconstruction, USA v1.01.
 * 260/268 bytes with game -O2 -G8 -frac2-qcopy -frac2-zero-ti-por. The probe and copied argument occupy the opposite stack slots, and retreat branches fold directly to the shared call instead of retaining retail thunks. Keep-block-order, gcse-unsplit-edges and no-thread-jumps did not close the difference.
 * No strict linked match.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Probe;
extern float D_L11_001B1DA0 SDATA(D_L11_001B1DA0);
extern float D_L11_001B1DA4 SDATA(D_L11_001B1DA4);
extern int D_L11_001B1DA8 SDATA(D_L11_001B1DA8);
extern void func_002A7750(void *, int, int);
extern float func_00282E80(void *, void *);
extern int func_00283DB8(void *, float);
extern int func_002A77E0(int);

void func_L11_00456938(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *target = *(unsigned char **)(state + 0x240);
    float distance;
    Probe probe, copy;
    if (target == 0) {
        func_002A7750(object, 4, 2);
        return;
    }
    distance = func_00282E80(object + 0x10, target + 0x10);
    if (distance < D_L11_001B1DA4) {
        func_002A7750(object, 7, 3);
    } else {
        probe.q = 0;
        probe.f[0] = *(float *)(object + 0x10);
        probe.f[1] = *(float *)(object + 0x14);
        probe.f[2] = *(float *)(object + 0x18);
        probe.f[3] = 0.5f;
        qcopy(&copy, &probe);
        if (func_00283DB8(&copy, 128.0f) <= 0) {
            func_002A7750(object, 7, 3);
        } else if (distance > D_L11_001B1DA0) {
            func_002A7750(object, 7, 3);
        } else if (func_002A77E0(D_L11_001B1DA8) == 0) {
            func_002A7750(object, 9, 3);
        }
    }
}
