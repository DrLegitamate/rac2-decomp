#include "common.h"
/* Retail reloads both the pose table and its index after every call. */
extern unsigned char * volatile D_L01_001B264C[] __attribute__((sda));
extern float func_00283180(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA150(float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002AD6F0(void *, void *, void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern unsigned char D_00188660[] __attribute__((nosda));
void func_L01_003EC0C0(unsigned char *m)
{
    float position[4], rotation[4], delta[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    float blend;
    qcopy(position, m + 0x10);
    qcopy(rotation, m + 0xf0);
    switch (m[0x20]) {
    case 0:
        *(int *)(p + 0x90) = -1;
        *(int *)(p + 0x88) = 0;
        *(int *)(p + 0x5c) |= 1;
        qcopy(p + 0x60, m + 0x10);
        qcopy(p + 0x70, m + 0xf0);
        func_002A7750(m, 1, -1);
        break;
    case 1:
        if (m[0xbc]) {
            *(int *)(p + 0x90) = func_002E5CF8(0, 4, m);
            func_002A7750(m, 2, -1);
        }
        m[0xa8] = 255;
        break;
    case 2:
        *(float *)(p + 0x88) += 1.0f / *(float *)(p + 0x84);
        if (*(float *)(p + 0x88) > 1.0f) *(float *)(p + 0x88) = 1.0f;
        blend = (1.0f - func_00283180(*(float *)(p + 0x88) * 3.1415927f)) * 0.5f;
        {
            int index = *(volatile int *)(p + 0x80);
            unsigned char *target = D_L01_001B264C[0];
            func_00282CF0(delta, target + index * 128 + 0x30, p + 0x60);
        }
        func_00282D30(delta, delta, blend);
        func_00282CC0(m + 0x10, p + 0x60, delta);
        {
            int index = *(volatile int *)(p + 0x80);
            unsigned char *target = D_L01_001B264C[0];
            *(float *)(m + 0xf8) = func_002AA150(*(float *)(p + 0x78), *(float *)(target + index * 128 + 0x78), blend);
        }
        {
            unsigned char *target = D_L01_001B264C[0];
        *(float *)(m + 0xf4) = func_002AA150(*(float *)(p + 0x74), *(float *)(target + *(volatile int *)(p + 0x80) * 128 + 0x74), blend);
        }
        {
            unsigned char *target = D_L01_001B264C[0];
        *(float *)(m + 0xf0) = func_002AA150(*(float *)(p + 0x70), *(float *)(target + *(volatile int *)(p + 0x80) * 128 + 0x70), blend);
        }
        if (*(float *)(p + 0x88) >= 1.0f) {
            int handle = *(int *)(p + 0x90);
            if (handle != -1) {
                unsigned char *record = D_00188660 + handle * 0x70;
                if (*(void **)(record + 0x88) == m && record[0x74])
                    func_002E59F8(handle);
                *(int *)(p + 0x90) = -1;
            }
            func_002E5CF8(1, 0, m);
            func_002A7750(m, 3, -1);
        }
        break;
    }
    if (m[0x20] < 3) {
        func_00282CF0(delta, m + 0x10, position);
        func_002AD6F0(p + 0x20, delta, rotation, m + 0xf0);
    }
}
