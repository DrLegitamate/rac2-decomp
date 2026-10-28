/* 28 October 2026: 712/708 bytes at -O2 -G0 -ffunction-sections.
 * Both table declarations with MACRO_ADDR reached 708 bytes but retained
 * table/parameter allocation and floating bound-register differences.
 * Explicit bound locals were worse (772 bytes). A typed 0xA0 record
 * view tied. Default qcopy preserves both full vector transfers.
 * Reopen with allocator evidence for table/parameter and FP bounds.
 * No strict match is claimed. */
#include "common.h"

typedef struct { char bytes[0xA0]; } EffectRecord;
extern EffectRecord D_0022AA10[];
extern char D_001B2520[] MACRO_ADDR;
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_00282C88(void *);
extern char *func_002AB1F0(void *);
extern void func_002B00B0(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* Initialize one of the three available effect records. */
void func_00316400(int type, char *object, int parameter)
{
    float offset[4] __attribute__((aligned(16)));
    char *position = object + 0x10;
    int i;
    for (i = 0; i < 3; i++) {
        char *record = (char *)&D_0022AA10[i];
        if (!*(int *)(record + 0x8C)) {
            char *attachment;
            *(int *)(record + 0x8C) = type;
            qcopy(record + 0x20, D_001B2520);
            *(float *)(record + 0x40) = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(record + 0x44) = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(record + 0x48) = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(record + 0x64) = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(record + 0x68) = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(record + 0x6C) = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(record + 0x4C) = func_002A78D8(0.001f, 0.005f);
            *(float *)(record + 0x50) = func_002A78D8(0.001f, 0.005f);
            *(float *)(record + 0x54) = func_002A78D8(0.001f, 0.005f);
            *(float *)(record + 0x70) = func_002A78D8(0.001f, 0.005f);
            *(float *)(record + 0x74) = func_002A78D8(0.001f, 0.005f);
            *(float *)(record + 0x78) = func_002A78D8(0.001f, 0.005f);
            *(float *)(record + 0x58) = func_002A7878(3.25f, 4.75f) * 0.5f;
            *(float *)(record + 0x5C) = func_002A7878(3.25f, 4.75f) * 0.5f;
            *(float *)(record + 0x60) = func_002A7878(3.25f, 4.75f) * 0.5f;
            *(float *)(record + 0x7C) = func_002A7878(3.25f, 4.75f) * 0.5f;
            *(float *)(record + 0x80) = func_002A7878(3.25f, 4.75f) * 0.5f;
            *(float *)(record + 0x84) = func_002A7878(3.25f, 4.75f) * 0.5f;
            func_00282C88(record);
            func_00282C88(record + 0x10);
            *(int *)(record + 0x98) = parameter;
            *(int *)(record + 0x94) = parameter;
            *(int *)(record + 0x88) = 15;
            *(char **)(record + 0x90) = object;
            *(int *)(record + 0x9C) = 0;
            attachment = func_002AB1F0(object);
            if (attachment) {
                func_002B00B0(object, offset, 1);
                func_00282D30(offset, offset, *(float *)(attachment + 0x10));
                func_00282CC0(record + 0x30, offset, position);
            } else {
                qcopy(record + 0x30, position);
            }
            break;
        }
    }
}
