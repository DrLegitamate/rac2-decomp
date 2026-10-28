/* Game -O2 -G0: 656/660 bytes. Composite state induction and the
 * retained object position spill need different lifetimes; explicit array
 * views and no-strength-reduce do not resolve the frame/allocation mismatch.
 */
#include "common.h"
extern void func_L14_004308D0(void *, int, int, int, float, float, float);
extern float func_L14_00430898(float);
extern void func_L14_00430E08(void *);
extern int func_00282948(void *);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_00283B98(float, float);
#define F(offset) (*(float *)(state + (offset)))
#define I(offset) (*(int *)(state + (offset)))

void func_L14_00430B70(char *object)
{
    char *state = *(char **)(object + 0x68);
    int i, count;
    int *timer = (int *)(state + 0x50);
    int *end_colour = (int *)(state + 0x40);
    unsigned int colour;
    float fraction, radius, angle;
    func_L14_004308D0(object + 0x10, I(0xb8), I(0xc0), 1, F(0xbc) * F(0x80), F(0x80) * 0.5f, 0.0f);
    for (i = 0, count = 1; count >= 0; i += 4, timer++, end_colour++, count--) {
        if (func_00282948(timer)) I(0x50 + i) = (int)((float)I(0x10) / F(0x20 + i));
        fraction = 1.0f - (float)I(0x50 + i) / (float)(int)((float)I(0x10) / F(0x20 + i));
        if (F(0x14) < fraction) {
            colour = (*end_colour & 0xffffff) + (((int)((1.0f - fraction) / (1.0f - F(0x14)) * 80.0f) + 48) << 24);
        } else {
            colour = func_00283D38(I(0x30 + i), *end_colour, fraction / F(0x14)) & 0xffffff;
            colour += ((int)(fraction / F(0x14) * 80.0f) + 48) << 24;
        }
        radius = F(0x80) * F(0x18);
        angle = func_L14_00430898(fraction * (F(0x60 + i) * 6.2831855f));
        func_L14_004308D0(object + 0x10, I(0x1c), colour, 1, radius, F(0x80) * 0.5f, angle - 3.1415927f);
    }
    angle = func_00283B98(F(0), 0.007f);
    F(0) = angle;
    func_L14_004308D0(object + 0x10, I(4), I(12), 1, F(8) * F(0x80), F(0x80) * 0.5f, angle);
    func_L14_00430E08(object);
}
#undef F
#undef I
