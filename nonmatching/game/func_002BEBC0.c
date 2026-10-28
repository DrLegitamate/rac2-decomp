/* Game -O2 -G0: 672/680 bytes, 0/28 USA places. The first distance
 * relaxation and phase update are exact. The alpha-bound selection is
 * emitted as a default constant plus a conditional replacement, rather than
 * two separate arms; its block schedule and later alpha paths differ.
 * The step view retains the measured repeated load before incrementing alpha.
 * Next: reconstruct the actual bound/step record and its branch scopes.
 */
#include "common.h"
extern int func_00282978(void *), func_00283CF0(float);
extern void func_002B9180(void *), func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00282CC0(void *, void *, void *);
extern unsigned char *D_001F25B4;
extern float D_001B5340[];
#define F(p, offset) (*(float *)((p) + (offset)))

void func_002BEBC0(unsigned char *object)
{
    unsigned char *state;
    float t, ceiling, current, step;
    int alpha;
    float point[4], delta[4];
    if (!object) return;
    state = object + 0x20;
    if (func_00282978(object + 0xa) || !*(char **)state || *(signed char *)(*(char **)state + 0x20) < 0) goto destroy;
    *(unsigned short *)(state + 0xc) = (*(unsigned short *)(state + 0xc) + 1) & 15;
    if (F(object, 0xc) < 159600.0f) {
        F(object, 0xc) += 3989.999755859375f;
        if (F(object, 0xc) > 159600.0f) F(object, 0xc) = 159600.0f;
    } else if (F(object, 0xc) > 159600.0f) {
        F(object, 0xc) -= 15959.9990234375f;
        if (F(object, 0xc) < 159600.0f) F(object, 0xc) = 159600.0f;
    }
    F(state, 8) += 0.001f;
    object[8] = func_00283CF0(F(state, 8) * 255.0f);
    object[2] = D_001F25B4[*(short *)(state + 0xc)];
    if (!(F(object, 0xc) <= 159600.0f) && *(volatile float *)(state + 0x10) > 0.0f) F(state, 4) += *(volatile float *)(state + 0x10);
    if (F(object, 0xc) <= 159600.0f) {
        ceiling = 0.3f;
        goto test_bound;
    }
    ceiling = 0.15f;
test_bound:
    current = F(state, 4);
    if (!(current > ceiling)) {
        if (current < 0.0f) {
destroy:
            func_002B9180(object);
            return;
        }
    } else {
        step = -*(volatile float *)(state + 0x10);
        *(volatile float *)(state + 0x10) = step;
        F(state, 4) = current + step;
    }
    alpha = func_00283CF0(F(state, 4) * 256.0f);
    *(unsigned int *)(object + 4) = (*(unsigned int *)(object + 4) & 0xffffff) + ((unsigned int)alpha << 24);
    t = F(state, 0x14);
    t += (1.0f - t) * 0.175f;
    F(state, 0x14) = t;
    if (*(short *)(state + 0xe) != -1) {
        func_0029FCC0(*(void **)state, *(short *)(state + 0xe), point);
        func_00282CF0(delta, D_001B5340, point);
        func_00282F20(delta, delta, F(state, 0x14));
        func_00282CC0(object + 0x10, point, delta);
    }
    return;
}
#undef F
