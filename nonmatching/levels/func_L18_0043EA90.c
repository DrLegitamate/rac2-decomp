/* 28 October 2026: 852/852 bytes, US placements 18 and 20.
 * -O2 -G8 -ffunction-sections. The count/state pointers swap s0/s1;
 * the dynamic frame and unrolled effect sequence agree. Declaration
 * order, aligned point type and a truthful FP-first F130 declaration tie.
 * Regalloc confirms state: 12 refs/99 live length/15 call crossings;
 * count: 6 refs/66 live length/9 crossings. Diagnostic objects equal.
 * Reopen with evidence of the original state/count lifetimes.
 * No strict match is claimed. */
#include "common.h"

extern int D_L18_001B1C60 __attribute__((sda));
extern float D_L18_001B1C64 __attribute__((sda));
extern float D_L18_001B1C78 __attribute__((sda));
extern float D_L18_001B1C7C __attribute__((sda));
extern float D_L18_001B1C80 __attribute__((sda));
extern float D_L18_001B1C84 __attribute__((sda));
extern int D_L18_001B1C88 __attribute__((sda));
extern int D_L18_001B1C8C __attribute__((sda));
extern float D_L18_001B1C90 __attribute__((sda));
extern int D_L18_001B1C98 __attribute__((sda));
extern int D_L18_001B1C9C __attribute__((sda));
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern void func_L18_0043F130(float, void *, int, void *);
extern void func_L18_0043F428(void *, int, int, int, int, float, float);
extern void func_L11_00458DF0(void *, int, int, float, float, int, int);

void func_L18_0043EA90(char *object)
{
    char *state = *(char **)(object + 0x68);
    int count = D_L18_001B1C60;
    typedef struct { float values[4]; } Point __attribute__((aligned(16)));
    Point points[count];
    float step = D_L18_001B1C64;
    int life;
    float first, second, large, small;
    float angle;

    life = func_002A7820(48, 128);
    first = (1.0f - *(float *)(state + 0x158)) * func_002A7878(D_L18_001B1C78, D_L18_001B1C7C);
    second = (1.0f - *(float *)(state + 0x158)) * func_002A7878(D_L18_001B1C80, D_L18_001B1C84);
    func_L18_0043F130(step, points, count, state);
    func_L18_0043F428(points, count, life, D_L18_001B1C88, D_L18_001B1C8C, first, second);
    life = func_002A7820(48, 128);
    first = (1.0f - *(float *)(state + 0x158)) * func_002A7878(D_L18_001B1C78, D_L18_001B1C7C);
    second = (1.0f - *(float *)(state + 0x158)) * func_002A7878(D_L18_001B1C80, D_L18_001B1C84);
    func_L18_0043F130(step, points, count, state + 0xA0);
    func_L18_0043F428(points, count, life, D_L18_001B1C88, D_L18_001B1C8C, first, second);
    small = D_L18_001B1C90 * (1.0f - *(float *)(state + 0x158));
    large = small * 0.5f;
    life = func_002A7820(80, 96);
    angle = func_002A7940();
    func_L11_00458DF0(state, D_L18_001B1C98, life, large, angle, 49, 2);
    small *= 0.7f;
    life = func_002A7820(8, 22);
    angle = func_002A7940();
    func_L11_00458DF0(state, D_L18_001B1C9C, life, small, angle, 11, 2);
    life = func_002A7820(80, 96);
    angle = func_002A7940();
    func_L11_00458DF0(state + 0x10, D_L18_001B1C98, life, large, angle, 49, 2);
    life = func_002A7820(8, 22);
    angle = func_002A7940();
    func_L11_00458DF0(state + 0x10, D_L18_001B1C9C, life, small, angle, 11, 2);
    life = func_002A7820(80, 96);
    angle = func_002A7940();
    func_L11_00458DF0(state + 0xA0, D_L18_001B1C98, life, large, angle, 49, 2);
    life = func_002A7820(8, 22);
    angle = func_002A7940();
    func_L11_00458DF0(state + 0xA0, D_L18_001B1C9C, life, small, angle, 11, 2);
    life = func_002A7820(80, 96);
    angle = func_002A7940();
    func_L11_00458DF0(state + 0xB0, D_L18_001B1C98, life, large, angle, 49, 2);
    life = func_002A7820(8, 22);
    angle = func_002A7940();
    func_L11_00458DF0(state + 0xB0, D_L18_001B1C9C, life, small, angle, 11, 2);
}
