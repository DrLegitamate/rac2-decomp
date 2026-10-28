/* Game -O2 -G8 with qcopy and qcopy-barrier: 640/640 bytes, 0/1 USA.
 * The barrier resolves copy/call scheduling. Remaining child-flag integer
 * temporaries and the angular position/velocity FP pair allocate differently.
 * Three faithful arithmetic wordings and G0 produce the same remaining tie.
 * Next: inspect the original private-state and child record types.
 */
#include "common.h"
typedef int PrisonStateQuad __attribute__((mode(TI)));
extern void func_002A7750(void *, int, int);
extern void *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern int func_002B3868(void *), func_002B38B8(void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_L00_003294F0(void *, int);
extern int func_002E5CF8(int, int, void *);
extern void func_L14_003CB608(void *), func_L14_003CB868(void *), func_L14_003CB4D8(void *);
extern char D_L14_001A8F20[];
extern void *D_0018A15C NOT_SDA;
extern unsigned short D_0018CDD8 NOT_SDA;
extern float D_L14_001AFEF8 SDATA(D_L14_001AFEF8);
extern float D_L14_001AFEFC SDATA(D_L14_001AFEFC);
extern float D_L14_001AFF00 SDATA(D_L14_001AFF00);
extern float D_L14_001AFF04 SDATA(D_L14_001AFF04);
extern float D_L14_001AFF08 SDATA(D_L14_001AFF08);
extern float D_L14_001AFF0C SDATA(D_L14_001AFF0C);

void func_L14_003CB258(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    unsigned char *child;
    float velocity, angle, ceiling, bounce;
    unsigned int flags, parent_id;
    switch (object[0x20]) {
    case 0:
        func_002A7750(object, 1, -1);
        *(int *)(state + 0x5c) |= 1;
        *(PrisonStateQuad *)(state + 0x70) = *(PrisonStateQuad *)(object + 0x10);
        *(float *)(state + 0x78) += D_L14_001AFF0C;
        child = func_0029EFD0(0xf4d);
        if (child) {
            func_002B37E8(child, object);
            flags = *(unsigned short *)(child + 0x34);
            parent_id = *(unsigned short *)(object + 0x32);
            *(unsigned short *)(child + 0x7c) = 0x8001;
            *(unsigned short *)(child + 0x32) = parent_id;
            *(unsigned short *)(child + 0x34) = flags | 2;
            *(int *)(child + 0x9c) = 0x80000001;
            child[0x30] = 0;
            *(int *)(object + 0x9c) = 6;
        }
        break;
    case 1:
        if (func_002B3868(object)) func_002AD6F0(state + 0x20, D_L14_001A8F20, object + 0xf0, object + 0xf0);
        if (D_0018A15C == object) func_L14_003CB608(object);
        if (func_002B38B8(object)) {
            func_002A7750(object, 2, -1);
            func_L00_003294F0(object, 0);
            func_L14_003CB868(object);
        }
        break;
    case 2:
        if (func_002B3868(object)) *(float *)(state + 0x84) = D_L14_001AFEFC * 0.0002908882452175021f;
        velocity = *(float *)(state + 0x84);
        velocity -= D_L14_001AFEF8 * 4.848137450608192e-06f;
        ceiling = D_L14_001AFF04 * 0.01745329424738884f;
        *(float *)(state + 0x84) = velocity;
        *(float *)(state + 0x80) += velocity;
        if (*(float *)(state + 0x80) > ceiling) {
            bounce = D_L14_001AFF00;
            *(float *)(state + 0x80) = ceiling;
            *(float *)(state + 0x84) = velocity * bounce;
            func_002E5CF8(0, 0, object);
        } else if (*(float *)(state + 0x80) < 0.0f) {
            bounce = D_L14_001AFF00;
            *(float *)(state + 0x80) = 0.0f;
            *(float *)(state + 0x84) = velocity * bounce;
            func_002E5CF8(0, 0, object);
            if (*(float *)(state + 0x84) <= D_L14_001AFF08 * 0.0002908882452175021f)
                func_002A7750(object, 1, -1);
        }
        D_0018CDD8 = 0xffff;
        func_L14_003CB4D8(object);
        break;
    }
}
