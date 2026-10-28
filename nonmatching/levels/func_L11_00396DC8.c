/* Retained exact-C attempt: 672/672 bytes.
 * Profile: -O2 -G8 -ffunction-sections.
 * US and US2 0/1; PAL absent. The spawn, complete vector copies, randomization and lifetime setup agree through the class-selection tail. Selector/stride GPRs and scale load scheduling differ; the class stride is 0xE0.
 * Local checks only; no strict linked match. Reopen with independent
 * source, allocation or assembler evidence for the stated difference.
 */
#include "common.h"
extern char *func_0029EFD0(int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern int func_001163B0(void);
extern int func_00283CF0(float);
extern int func_002A7820(int, int);
extern void func_002A0F48(void *);
extern void func_002AB650(void *);
extern int D_001AEC3C __attribute__((sda));
extern float D_001AEC38 __attribute__((sda));
extern unsigned char D_00139578 NOT_SDA;
typedef struct { unsigned char pad00[4]; unsigned char flag; unsigned char pad05[219]; } ClassEntry;
extern ClassEntry D_00279BA0[];

char *func_L11_00396DC8(int unused, void *position, float *velocity)
{
    char *object = func_0029EFD0(0x1AC);
    if (object != 0) {
        char *state;
        int low, high;
        *(unsigned char *)(object + 0x30) = 0x40;
        *(unsigned short *)(object + 0x34) |= 0x1000;
        *(unsigned short *)(object + 0x32) = 0x20;
        *(unsigned char *)(object + 0x31) = 1;
        state = *(char **)(object + 0x68);
        *(unsigned char *)(object + 0x20) = 0;
        *(unsigned char *)(object + 0xBC) = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x18) += func_002A7878(0.2f, 0.7f);
        {
            float x = *(float *)(object + 0x10);
            float y = *(float *)(object + 0x14);
            *(float *)(object + 0x10) = x + velocity[0] * 3.0f;
            *(float *)(object + 0x14) = y + velocity[1] * 3.0f;
        }
        qcopy(state, velocity);
        *(float *)(object + 0xF4) = func_002A78D8(0.174532949924469f, 0.523598849773407f);
        *(float *)(object + 0xF0) = func_002A7878(0.174532949924469f, 0.7853982448577881f);
        *(float *)(state + 0x2C) = func_002A7878(200.0f,370.0f) * 0.0002908882452175021f;
        *(int *)(state + 0x24) = -1;
        if (func_001163B0() & 1) {
            *(int *)(state + 0x24) = 1;
            *(float *)(object + 0xF4) = -*(float *)(object + 0xF4);
        }
        *(float *)(object + 0xF8) = func_002A7940();
        *(float *)(state + 0x28) = -(func_002A7878(200.0f,550.0f)*0.0002908882452175021f);
        *(float *)(state + 0x10) = func_002A7940();
        {
            float phase = func_002A7940();
            float lifetime = (float)D_001AEC3C;
            *(float *)(state + 0x14) = phase;
            low = func_00283CF0(lifetime * 0.7f);
        }
        high = func_00283CF0((float)D_001AEC3C * 1.2f);
        *(int *)(state + 0x1C) = func_002A7820(low,high);
        {
            float scale = D_001AEC38;
            *(float *)(object + 0x2C) *= scale;
        }
        {
            ClassEntry *entry = D_00279BA0 + D_00139578;
            if (entry->flag)
                *(float *)(object + 0x2C) += *(float *)(object + 0x2C);
        }
        *(float *)(state + 0x20) = func_002A7878(-1.2f,-0.4f)*0.01666666753590107f;
        func_002A0F48(object);
        func_002AB650(object);
    }
    return object;
}
