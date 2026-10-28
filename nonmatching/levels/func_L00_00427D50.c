/* Near miss, not linked. Game -O2 -G8 -ffunction-sections.
 * Preliminary USA v1.01 draft: 680/684 bytes, 0/27 placements after one trial.
 * Recovered camera parameter smoothing, attached-owner basis copy, quaternion
 * rotation and fallback matrix update. The quaternion helper's actual axis
 * argument is retained. Its angle constant was corrected from the retail bits
 * after that first trial; this final source has not been rechecked.
 * Work was reprioritized to a smaller reserved tranche, not classified impossible.
 */
#include "common.h"

extern float func_00283B98(float, float);
extern float func_002703B0(char *, float, float, float, float, float);
extern float func_002702C8(float *, float, float, float, float, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AB668(void *, int, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_L00_002DA0B8(void *, void *);
extern void func_00283410(void *, void *);
extern void func_00283678(void *, void *);
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern float D_L00_001B1624 SDATA(D_L00_001B1624);
extern float D_L00_001B1628 SDATA(D_L00_001B1628);
extern float D_L00_001B162C SDATA(D_L00_001B162C);

void func_L00_00427D50(char *object)
{
    float displacement[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x70);
    char *focus = state + 0xB0;
    char *position;
    char *secondAxis;
    char *owner;
    float angle;

    angle = func_00283B98(*(float *)(focus + 0x18), *(float *)(state + 0x14));
    *(float *)(object + 0x50) = func_002703B0((state + 0x0),
        *(float *)(object + 0x50), angle,
        *(float *)(state + 0x28), *(float *)(state + 0x3C), *(float *)(state + 0x50));
    *(float *)(object + 0x54) = func_002703B0((state + 0x4),
        *(float *)(object + 0x54), *(float *)(state + 0x18),
        *(float *)(state + 0x2C), *(float *)(state + 0x40), *(float *)(state + 0x54));
    *(float *)(object + 0x58) = func_002702C8((float *)(state + 0x8),
        *(float *)(object + 0x58), *(float *)(state + 0x1C),
        *(float *)(state + 0x30), *(float *)(state + 0x44), *(float *)(state + 0x58));
    *(float *)(object + 0x5C) = func_002703B0((state + 0xC),
        *(float *)(object + 0x5C), *(float *)(state + 0x20),
        *(float *)(state + 0x34), *(float *)(state + 0x48), *(float *)(state + 0x5C));
    *(float *)(object + 0x60) = func_002703B0((state + 0x10),
        *(float *)(object + 0x60), *(float *)(state + 0x24),
        *(float *)(state + 0x38), *(float *)(state + 0x4C), *(float *)(state + 0x60));
    if (*(int *)(state + 0x9C) == 0) {
        *(float *)(state + 0xB0) = func_002702C8((float *)(state + 0x90),
            *(float *)(state + 0xB0), *(float *)(state + 0x80),
            *(float *)(state + 0xA0), *(float *)(state + 0xA4), *(float *)(state + 0xA8));
        *(float *)(focus + 4) = func_002702C8((float *)(state + 0x94),
            *(float *)(focus + 4), *(float *)(state + 0x84),
            *(float *)(state + 0xA0), *(float *)(state + 0xA4), *(float *)(state + 0xA8));
        *(float *)(focus + 8) = func_002702C8((float *)(state + 0x98),
            *(float *)(focus + 8), *(float *)(state + 0x88),
            *(float *)(state + 0xA0), *(float *)(state + 0xA4), *(float *)(state + 0xA8));
    } else {
        qcopy(focus, state + 0x80);
    }
    if (D_L00_001A8FF0[0] && *(char **)(focus + 0x44)) {
        func_00282D30(displacement, *(char **)(focus + 0x44) + 0xE0, D_L00_001B1624);
        position = object + 0x30;
        func_00282CC0(position, *(char **)(focus + 0x44) + 0x10, displacement);
        func_00282D30(offset, *(char **)(focus + 0x44) + 0xC0, D_L00_001B1628);
        func_00282CC0(position, position, offset);
        owner = *(char **)(focus + 0x44);
        qcopy(object, owner + 0xC0);
        qcopy(object + 0x10, owner + 0xD0);
        secondAxis = object + 0x20;
        qcopy(secondAxis, owner + 0xE0);
        /* The quaternion helper consumes both the axis pointer and angle. */
        func_002AB668(rotation, (int)(object + 0x10), D_L00_001B162C * 0.01745329424738884f);
        func_002ACDE8(object, object, rotation);
        func_002ACDE8(secondAxis, secondAxis, rotation);
    } else {
        func_L00_002DA0B8(object + 0x30, object + 0x50);
        *(float *)(object + 0x40) = *(float *)(state + 0xAC);
        *(float *)(object + 0x44) = func_00283B98(*(float *)(object + 0x54), *(float *)(object + 0x5C));
        *(float *)(object + 0x48) = func_00283B98(3.1415927f, *(float *)(object + 0x50));
        *(float *)(object + 0x48) = func_00283B98(*(float *)(object + 0x48), *(float *)(object + 0x60));
        func_00283410(matrix, object + 0x40);
        func_00283678(object, matrix);
    }
}
