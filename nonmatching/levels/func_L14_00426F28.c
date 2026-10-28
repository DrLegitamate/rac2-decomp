/* Game -O2 -G8: 744/744 bytes, 0/1 USA placement.
 * The text helper returns int, the query returns its hit pointer, and the
 * approach helper returns float. With these actual contracts, only the
 * flags temporary at +0x248..+0x268 uses v1 rather than v0. Uint/ushort
 * snapshots tie; a uint64 snapshot grows to 752 bytes. A void text-helper
 * declaration matched but is not the actual source contract and was rejected.
 * Next: an evidenced object-field scope or allocation-lifetime change.
 */
#include "common.h"
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern float func_00283198(float);
extern void func_002A7750(void *, int, int);
extern void func_002E59F8(int);
extern char D_00188660[];
extern unsigned char D_0018C0D4 NOT_SDA;
extern char D_L14_001B17E0[], D_L14_001B1800[];
extern int D_L14_001B20C8;
extern int D_L14_001B17C0 SDATA(D_L14_001B17C0);
extern float D_L14_001B17C4 SDATA(D_L14_001B17C4);
extern float D_L14_001B17C8 SDATA(D_L14_001B17C8);
extern float D_L14_001B17D0 SDATA(D_L14_001B17D0);
extern float D_L14_001B17D4 MACRO_ADDR;
extern void *func_002A9640(void *, int, int);
extern int func_002B38B8(void *);
extern void func_L14_004272D8(void *);
extern int func_L00_0030DD70(void *, int);
extern float func_00283CE0(int);
extern float func_002AA2E8(float *, float, float);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L14_00427250(void *);
extern void func_0029F338(void *);

void func_L14_00426F28(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    float angle, denominator;
    int period, ticks;
    unsigned int counter, previous;
    unsigned short flags;
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
        func_002AA2E8((float *)state, D_L14_001B17C4 * angle + D_L14_001B17C8, D_L14_001B17D0 * 0.016666668f);
        func_L00_002E6CF0(func_L14_00427250, object);
        counter = *(unsigned short *)(object + 0x96);
        previous = counter++;
        *(unsigned short *)(object + 0x96) = counter;
        if (previous >= 181) *(int *)(state + 4) = 1;
        if (*(int *)(state + 8) != -1 && ((PrisonSoundAnchor *)(D_00188660 + *(int *)(state + 8) * 112))->owner == object && ((PrisonSoundAnchor *)(D_00188660 + *(int *)(state + 8) * 112))->active)
            func_002E59F8(*(int *)(state + 8));
        *(int *)(state + 8) = -1;
        if (!D_0018C0D4) {
            func_L00_0030DD70(D_L14_001B1800, 240);
            flags = *(unsigned short *)(object + 0x34);
            *(int *)(object + 0x98) = 0;
            flags |= 0x41;
            flags &= 0xefff;
            *(unsigned short *)(object + 0x34) = flags;
            func_002A7750(object, 3, -1);
        }
        break;
    case 3:
        func_L00_002E6CF0(func_L14_00427250, object);
        func_002AA2E8((float *)state, 0.0f, D_L14_001B17D4 * 0.016666668f);
        if (*(float *)state == 0.0f) func_0029F338(object);
        break;
    }
}
