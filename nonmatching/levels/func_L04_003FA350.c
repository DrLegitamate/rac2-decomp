/* func_L04_003FA350: same size as retail (596 bytes), 2 of 2 places differ only in the
 * two branch offsets (0xD vs 0xC words at +0x1f0 and +0x210): retail's two hit paths branch to
 * the nop before the shared "swc1 $f0,0($a2)", mine to the swc1 itself. Everything else
 * (registers, constants, schedule) is identical. Tried: single r store, ternary clamp,
 * pointer source for qcopy, f20 reuse as temp (t as separate temp is what fixed the f-regs).
 */
#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern void func_0030EE38(void *, void *, float);
extern void func_0030ED98(void *, void *, void *);
extern int func_002FED10(void *, void *, int, void *, int);
extern void func_0030EDC8(void *, void *, void *);
extern float func_0030EEF8(void *);
extern void func_0030EEE0(void *, void *, void *);
extern float func_0030FE40(float, float);
extern float func_0030FE88(float, float);
extern u8 D_L04_001BFAE0[];

void func_L04_003FA350(u8 *a0, float *a1, float *a2) {
    Q16_B0e5d8f83 v[2];
    float f20;
    float t;
    qcopy(&v[1], a0 + 0xC0);
    func_0030EE38(&v[0], &v[1], 17.0f);
    func_0030ED98(&v[0], &v[0], a0 + 0x10);
    if (func_002FED10(a0 + 0x10, &v[0], 0, a0, 0) != 0) {
        func_0030EDC8(&v[1], a0 + 0x10, D_L04_001BFAE0);
        f20 = func_0030EEF8(&v[1]);
        func_0030EEE0(&v[0], &v[1], D_L04_001BFAE0 + 0x20);
        t = (f20 - 2.0f) * 0.06666667f;
        if (t < 0.0f) {
            t = 0.0f;
        }
        if (((float *)&v[0])[2] > 0.0f) {
            *a1 = func_0030FE40(*a1, (1.0f - t) * 0.037815474f);
        } else {
            *a1 = func_0030FE88(*a1, (1.0f - t) * 0.037815474f);
        }
    }
    func_0030EE38(&v[1], a0 + 0xE0, -3.0f);
    func_0030ED98(&v[0], &v[1], a0 + 0x10);
    if (func_002FED10(a0 + 0x10, &v[0], 0, a0, 0) != 0) {
        func_0030EDC8(&v[1], a0 + 0x10, D_L04_001BFAE0);
        f20 = func_0030EEF8(&v[1]);
        if (f20 <= 1.0f) {
            if (*a2 > 0.0f) {
                *a2 = 0.0f;
            }
            *a2 = (1.0f - f20) * -1.5707964f;
        } else {
            t = f20 - 1.0f;
            t *= 0.5f;
            *a2 = t * 0.3f;
        }
    } else {
        *a2 = 0.3f;
    }
}
