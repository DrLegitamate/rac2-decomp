#include "common.h"

extern float func_00283B98(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_L04_003A21F8(char *, s32);

extern char D_L18_002A9C40[];

extern float D_L18_001B97C0[];

extern float func_002A7878(float, float);

extern void func_0029FCC0(void *, int, void *);

extern void func_00282CF0(float *, const float *, const float *);

extern void func_00282F20(char *, char *, float);

extern void func_00282CC0(char *, char *, char *);

extern int func_002A7820(int, int);

extern float func_002A7940(void);

extern int D_L18_001C9D40;

extern void func_L02_003FFC48(void *, int, int, int, int, float, float);

extern s32 func_002E59B0(void *, s32);

extern s32 func_002E5CF8(s32, s32, void *);

extern void *func_002A9640(void *, s32, s32);

extern float func_002A96A0(void *, void *);

extern void func_002AB800(void *, void *);

extern void func_002AB8C0(void *, void *);

extern int func_002A7750(void *, int, int);


extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern int func_001163B0(void);
extern void func_00282D30(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern u8 *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);

typedef int TI128 __attribute__((mode(TI)));

void func_L18_00435CC8(void) {
    func_L04_003A21F8(D_L18_002A9C40, 0x12);
}

void func_L18_00434128(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    for (i = 0; i < 2; i++) {
        u8 *p = &state[i * 0xA0 + 0x610];
        s32 j;
        for (j = 1; j >= 0; j--) {
            float x;
            *(float *)(p + 0x40) = func_00283B98(*(float *)(p + 0x40), *(float *)(p + 0x60));
            *(float *)(p + 0x44) = func_00283B98(*(float *)(p + 0x44), *(float *)(p + 0x64));
            *(float *)(p + 0x48) = func_00283B98(*(float *)(p + 0x48), *(float *)(p + 0x68));
            x = func_00283180(*(float *)(p + 0x40));
            *(float *)(p + 0x20) = x * *(float *)(p + 0x80);
            *(float *)(p + 0x24) = func_00283198(*(float *)(p + 0x44)) * *(float *)(p + 0x84);
            *(float *)(p + 0x28) = -func_00283198(*(float *)(p + 0x48)) * *(float *)(p + 0x88);
            p += 0x10;
        }
    }
}

INCLUDE_ASM("asm/levels", func_L18_00433460);

INCLUDE_ASM("asm/levels", func_L18_00433B70);

INCLUDE_ASM("asm/levels", func_L18_00434510);

void func_L18_00434A98(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    func_00282CF0(direction, D_L18_001B97C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(0.05f, 3.0f) * (1.0f / 60.0f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity, velocity, 1.5f);
            particle = func_002C2210(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            func_00282CF0(extra, D_L18_001B97C0, point);
            func_00282F20((char *)extra, (char *)extra, speed);
            func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
            particle = func_002C2210(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

INCLUDE_ASM("asm/levels", func_L18_00434FC0);

void func_L18_004350E0(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    func_00282CF0(direction, D_L18_001B97C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(0.05f, 3.0f) * (1.0f / 60.0f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity, velocity, 1.5f);
            particle = func_002C2210(point, 60, size * 0.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 60, size * 0.035f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            func_00282CF0(extra, D_L18_001B97C0, point);
            func_00282F20((char *)extra, (char *)extra, speed);
            func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
            particle = func_002C2210(point, 40, size * 0.15f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 40, size * 0.105000004f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

INCLUDE_ASM("asm/levels", func_L18_004354F8);


INCLUDE_ASM("asm/levels", func_L18_00435B10);

INCLUDE_ASM("asm/levels", func_L18_00436B80);

INCLUDE_ASM("asm/levels", func_L18_00437190);


INCLUDE_ASM("asm/levels", func_L18_00439960);

extern int D_L18_001C9D40;

extern float func_00283B98(float, float);

extern s32 func_002E59B0(void *, s32);

extern s32 func_002E5CF8(s32, s32, void *);

extern void *func_002A9640(void *, s32, s32);

extern float func_002A96A0(void *, void *);

extern void func_002AB800(void *, void *);

extern void func_002AB8C0(void *, void *);

extern int func_002A7750(void *, int, int);

INCLUDE_ASM("asm/levels", func_L18_00439FC8);

INCLUDE_ASM("asm/levels", func_L18_0043C258);

/* func_L18_0043C778 is defined in L18_0043C778-g64.c. */

/* func_L18_0043CAF8 is defined in L18_0043CAF8-g8.c. */

/* func_L18_0043F130 is defined in L18_0043F130-qcopy-barrier.c. */

void func_L18_0043F308(float *out, float *b, float *c, float *a, float *d, float t)
{
    float t2, t3, p, q, r;

    if (t == 0.0f) {
        qcopy(out, b);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, c);
        return;
    }
    t2 = t * t;
    t3 = t2 * t;

    p = (d[0] - c[0]) - (a[0] - b[0]);
    q = (a[0] - b[0]) - p;
    r = c[0] - a[0];
    out[0] = p * t3 + q * t2 + r * t + b[0];

    p = (d[1] - c[1]) - (a[1] - b[1]);
    q = (a[1] - b[1]) - p;
    r = c[1] - a[1];
    out[1] = p * t3 + q * t2 + r * t + b[1];

    p = (d[2] - c[2]) - (a[2] - b[2]);
    q = (a[2] - b[2]) - p;
    r = c[2] - a[2];
    out[2] = p * t3 + q * t2 + r * t + b[2];
    out[3] = 0.0f;
}



INCLUDE_ASM("asm/levels", func_L18_0043FC70);

INCLUDE_ASM("asm/levels", func_L18_00440718);

/* func_L18_00441050 is defined in L18_00441050-g8.c. */

INCLUDE_ASM("asm/levels", func_L18_00441438);

INCLUDE_ASM("asm/levels", func_L18_00447128);
