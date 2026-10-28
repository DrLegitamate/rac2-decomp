#include "common.h"

extern int D_L18_001AFBB0;
typedef struct { char pad00[0x1E0]; short locked; char pad1E2[0x2294-0x1E2]; int action; } HeroState;
extern HeroState D_00189E20;
extern float D_L18_001B1284 __attribute__((sda));
extern float D_L18_001B1280 __attribute__((sda));
extern float D_L18_001B126C __attribute__((sda));
extern unsigned short D_L18_001B1240 __attribute__((sda));
extern char D_L18_001B1308[];
extern float func_00282E80(void *, void *);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_L18_00426F28(void *, int, int, float);
extern void func_002A7750(void *, int, int);
extern void func_0026FEB8(void *, int);

int func_L18_00428138(char *object)
{
    char *state = *(char **)(object + 0x68);
    float range;
    if (D_L18_001AFBB0 || D_00189E20.locked ||
        D_00189E20.action == 0x6F)
        return 0;
    range = D_L18_001B1284;
    switch (*(short *)(object + 0xAA)) {
    case 0xEC0:
        if (func_00282E80(object + 0x10, state + 0x220) < D_L18_001B126C &&
            !*(short *)(state + 0x396) && !D_L18_001AFBB0 &&
            D_00189E20.action != 0x6F) {
            func_002B60B0(object, *(float *)(state + 0x3CC) * 0.00027777778f,
                         *(float *)(state + 0x3C8) * 0.016666668f,
                         *(float *)(state + 0x3DC) * 0.0000048481374f,
                         *(float *)(state + 0x3D8) * 0.00029088825f);
            *(unsigned short *)(state + 0x392) = D_L18_001B1240;
            func_L18_00426F28(object, 10, 0, 10.0f);
            func_002A7750(object, 6, -1);
            return 1;
        }
        break;
    case 0xED4:
        range = D_L18_001B1280;
    case 0xEE1:
        if (func_00282E80(object + 0x10, state + 0x220) < range &&
            !*(short *)(state + 0x396) && !D_L18_001AFBB0 &&
            D_00189E20.action != 0x6F) {
            func_L18_00426F28(object, 10, 0, 10.0f);
            func_002A7750(object, 6, -1);
            return 1;
        }
        break;
    default:
        func_0026FEB8(D_L18_001B1308, *(short *)(object + 0xAA));
        break;
    }
    return 0;
}
