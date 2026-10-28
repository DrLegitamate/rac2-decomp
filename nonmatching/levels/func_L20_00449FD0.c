/* Near miss, worker w3 batch 3: 308/308 B, 0/1, two swaps. The f20/f21 inputs are now right (0x14 store before 0x1C before 0x18). Left: `lwc1 $f1,gp` vs `lw $s0,0x68($s1)` order, and `sw $s4,0x18` vs `swc1 $f20,0x1C` order. Profile -O2 -G8 -ffunction-sections. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B23F8 __attribute__((sda));

extern void *func_0029EFD0(int);
extern void func_002B37E8(u8 *, u8 *);
extern float func_002A7940(void);
extern void func_002833F0(void *, void *);
extern float func_002A7878(float a, float b);

char *func_L20_00449FD0(char *arg0, char *arg1, char *arg2, int arg3,
                        float f12, float f13) {
    char *obj;
    char *state;
    float radiusScale, baseRadius;

    obj = func_0029EFD0(0x12EE);
    if (obj != 0) {
        func_002B37E8((u8 *)obj, (u8 *)arg0);
        qcopy((obj + 0x10), arg1);
        *(float *)(obj + 0xF0) = func_002A7940();
        *(float *)(obj + 0xF4) = func_002A7940();
        func_002833F0(obj + 0xC0, obj + 0xF0);
        *(u8 *)(obj + 0x20) = 1;
        *(u16 *)(obj + 0x34) |= 0x100;
        radiusScale = D_L20_001B23F8;
        baseRadius = *(float *)(*(char **)(obj + 0x24) + 0x24);
        state = *(char **)(obj + 0x68);
        *(float *)(obj + 0x2C) = baseRadius * radiusScale;
        qcopy(state, arg2);
        *(float *)(state + 0x14) = f12 * 0.016666668f;
        *(float *)(state + 0x1C) = f13;
        *(int *)(state + 0x18) = (int)arg3;
        *(int *)(state + 0x20) = 0x3C;
        *(float *)(state + 0x10) =
            func_002A7878(10.0f, 20.0f) * 0.00027777778f;
    }
    return obj;
}
