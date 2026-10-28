/* Historical G0 attempt, superseded by the matching G8 source in
 * src/levels/14_aranos_prison/L14_00426F28-g8.c. Retained only to explain
 * the scheduling and source-type differences documented below.
 */
/* USA v1.01 game -O2 -G0: 740/744 bytes. The signed remainder guard
 * precedes div rather than following it; counter update is one word shorter.
 * FP result preservation and the final comparison register also differ.
 * SDATA views preserve the measured GP identities; no forced registers.
 * Next: compare faithful G8 scheduling, then inspect the counter field type.
 */
#include "common.h"
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern float func_00283198(float);
extern void func_002A7750(void *, int, int);
extern void func_002E59F8(int);
extern char D_00188660[];
extern unsigned char D_0018C0D4;
extern char D_L14_001B17E0[], D_L14_001B1800[];
extern int D_L14_001B20C8;
extern int D_L14_001B17C0 SDATA(D_L14_001B17C0);
extern float D_L14_001B17C4 SDATA(D_L14_001B17C4);
extern float D_L14_001B17C8 SDATA(D_L14_001B17C8);
extern float D_L14_001B17D0 SDATA(D_L14_001B17D0);
extern float D_L14_001B17D4 MACRO_ADDR;
extern int func_002A9640(void *, int, int), func_002B38B8(void *);
extern void func_L14_004272D8(void *);
extern void func_L00_0030DD70(void *, int);
extern float func_00283CE0(int);
extern void func_002AA2E8(void *, float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L14_00427250(void *);
extern void func_0029F338(void *);

void func_L14_00426F28(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    float angle, denominator;
    int period, ticks, counter;
    switch ((unsigned char)object[0x20]) {
    case 0:
        func_002A7750(object, 1, -1);
        *(int *)(state + 8) = -1;
        break;
    case 1:
        if (D_0018C0D4 != 1) break;
        if ((unsigned char)object[0x31]) func_L14_004272D8(object);
        if (func_002A9640(object, 0x10000, 0) || func_002B38B8(object)) {
            func_L00_0030DD70(D_L14_001B17E0, 240);
            func_002A7750(object, 2, -1);
        }
        if (((PrisonSoundAnchor *)(D_00188660 + *(int *)(state + 8) * 112))->owner != object || !((PrisonSoundAnchor *)(D_00188660 + *(int *)(state + 8) * 112))->active)
            *(int *)(state + 8) = prisonStartSound(0, 4, object);
        break;
    case 2:
        ticks = D_L14_001B20C8;
        period = D_L14_001B17C0;
        angle = func_00283CE0(ticks % period);
        denominator = func_00283CE0(period);
        angle *= 6.2831855f;
        angle /= denominator;
        angle = func_00283198(angle - 3.1415927f);
        func_002AA2E8(state, D_L14_001B17C4 * angle + D_L14_001B17C8, D_L14_001B17D0 * 0.016666668f);
        func_L00_002E6CF0(func_L14_00427250, object);
        counter = *(unsigned short *)(object + 0x96);
        *(unsigned short *)(object + 0x96) = counter + 1;
        if ((unsigned int)counter >= 181) *(int *)(state + 4) = 1;
        if (*(int *)(state + 8) != -1 && ((PrisonSoundAnchor *)(D_00188660 + *(int *)(state + 8) * 112))->owner == object && ((PrisonSoundAnchor *)(D_00188660 + *(int *)(state + 8) * 112))->active)
            func_002E59F8(*(int *)(state + 8));
        *(int *)(state + 8) = -1;
        if (!D_0018C0D4) {
            func_L00_0030DD70(D_L14_001B1800, 240);
            *(int *)(object + 0x98) = 0;
            *(unsigned short *)(object + 0x34) = (*(unsigned short *)(object + 0x34) | 0x41) & 0xefff;
            func_002A7750(object, 3, -1);
        }
        break;
    case 3:
        func_L00_002E6CF0(func_L14_00427250, object);
        func_002AA2E8(state, 0.0f, D_L14_001B17D4 * 0.016666668f);
        if (*(float *)state == 0.0f) func_0029F338(object);
        break;
    }
}
