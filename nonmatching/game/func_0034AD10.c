/* Near miss, not linked. Game -O2 -G0 -ffunction-sections.
 * 712/728 bytes; local USA v1.01 check: 0/28 placements.
 * Recovered menu positions, quadrant scaling, foreground and outline drawing.
 * Remaining: retail keeps the boolean one in a saved register and uses a
 * different quadrant branch tree and loop-index lifetime. Six trials include
 * switch/explicit branch forms and separate calls; these did not close it.
 * Reopen with a measured boolean/scale lifetime, not artificial dependencies.
 */
#include "common.h"

extern void func_00336320(void *);
extern void func_00336548(void *);
extern int func_002A9588(int, int, int, int, int);
extern void func_0034A808(void *, int, int, float *, float *, float *, int *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00336390(void *, void *, int);
extern int *func_00335E20(void *);
extern char *D_001A8CFC[] MACRO_ADDR;

void func_0034AD10(char *object)
{
    float x, y, scale;
    int quadrant;
    int flashColor;
    int i;
    int flashing;
    int highlighted;
    char *label;
    float sx, sy;

    if (*(int *)(object + 0xC) == 0)
        return;
    func_00336320(object + 0x5C);
    flashColor = 0;
    func_00336320(object + 0xA8);
    func_00336548(object + 0xF4);
    x = 0.0f;
    y = 0.0f;
    scale = 0.0f;
    quadrant = 0;
    if (*(int *)(object + 0x3F8)) {
        flashColor = func_002A9588(-1, 0x22222222, 10, 0, 0);
        --*(int *)(object + 0x3F8);
    }
    highlighted = 1;
    for (i = 0; i < *(int *)(object + 4);) {
        flashing = 0;
        if (*(int *)(object + 0x3F8)) {
            flashing = highlighted;
            if (i < *(int *)(object + 0x3FC))
                flashing = 0;
        }
        func_0034A808(object, *(int *)(object + 4), i, &x, &y, &scale, &quadrant);
        label = object + 0x10;
        func_00335E38(label, x, y, 0.0f, 0.0f);
        sx = scale;
        sy = scale;
        if (quadrant == 1) {
            sx = -scale;
        } else if (quadrant >= 2) {
            if (quadrant == 2) {
                sy = -scale;
            } else if (quadrant == 3) {
                sy = -scale;
                sx = -scale;
            }
        }
        func_00335F88(label, sx, sy, 0.0f, 0.0f);
        if (*(int *)(object + 4) < 21) {
            if (*(int *)object >= i + 1) {
                func_00336390(label, D_001A8CFC[0] + 0x8710, 0x1A);
                if (flashing)
                    *func_00335E20(label) = flashColor;
                else
                    *(float *)func_00335E20(label) = **(float **)(object + 0x1C8);
                func_00336320(label);
            }
            func_00336390(label, D_001A8CFC[0] + 0x8710, 0x19);
            *func_00335E20(label) = 0x55F0C070;
            func_00336320(label);
        } else {
            if (*(int *)object >= i + 1) {
                func_00336390(label, D_001A8CFC[0] + 0x8710, 0x1B);
                if (flashing)
                    *func_00335E20(label) = flashColor;
                else
                    *(float *)func_00335E20(label) = **(float **)(object + 0x1C8);
                func_00336320(label);
            }
            func_00336390(label, D_001A8CFC[0] + 0x8710, 0x18);
            *func_00335E20(label) = 0x55F0C070;
            func_00336320(label);
        }
        ++i;
    }
}
