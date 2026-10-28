/* Near miss, not linked. Game -O2 -G8 -ffunction-sections.
 * 812/812 bytes; USA v1.01: 0/1; USA v2.00: 0/1; PAL: no row.
 * Recovered waypoint setup, event wakeup, bidirectional movement, looping sound
 * and the post-move collision query. Nine checker invocations; the last three
 * source forms tied. Typed actor stride and scoped pointer lifetimes improve
 * allocation; a truthful 16-byte vector address view fixes final call setup.
 * Remaining: trigger-table index allocation and the first movement call's
 * argument/saved-pointer captures. Reopen with a measured owner/lifetime model.
 */
#include "common.h"

typedef struct { u8 prefix[0x10]; float position[4]; } MovingObjectView;
typedef struct { u8 prefix[0x30]; float target[4]; } MovingStateView;

extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7750(void *, int, int);
extern float func_002AA458(void *, float, void *, float, void *, float);
extern float func_00282E48(void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L19_00420B48(void *);
extern void func_002A8C00(float, char *, int, int, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int D_001A79F0 SDATA(D_001A79F0);
extern unsigned char D_0019B2E8[][16] MACRO_ADDR;
typedef unsigned char ActorSlot[0x100];
extern ActorSlot *D_L19_001B2A1C SDATA(D_L19_001B2A1C);
extern char D_00188660[];
extern float D_L19_001A8F20[4] MACRO_ADDR;

void func_L19_00420818(char *object)
{
    float delta[4] __attribute__((aligned(16)));
    char query[0x30] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    float *position;
    float *target;
    char *sound;
    switch (*(u8 *)(object + 0x20)) {
    case 0: {
        char *initialPosition = object + 0x10;
        func_00282F20(delta, object + 0xC0, *(float *)(state + 4));
        func_00282CC0(state + 0x30, delta, initialPosition);
        *(float *)(state + 0x38) += *(float *)state;
        qcopy(state + 0x20, initialPosition);
        *(int *)(state + 0x40) = -1;
    }
    case 1: {
        int trigger = *(u8 *)(object + 0xB0);
        if ((trigger != 0xFF &&
             (((u8 *)D_0019B2E8)[trigger += D_001A79F0 << 4] & 0x80)) ||
            (*(int *)(state + 0x1C) != -1 &&
             D_L19_001B2A1C[*(int *)(state + 0x1C)][0x20]))
            func_002A7750(object, 2, -1);
        break;
    }
    case 2:
        func_002AA458(((MovingObjectView *)object)->position, *(float *)(state + 8) * 0.00027777778f,
                       ((MovingStateView *)state)->target, *(float *)(state + 8) * 0.00027777778f,
                       state + 0x14, *(float *)(state + 8) * 0.016666668f);
        position = ((MovingObjectView *)object)->position;
        target = ((MovingStateView *)state)->target;
        sound = D_00188660 + *(int *)(state + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != object || *(u8 *)(sound + 0x74) == 0)
            *(int *)(state + 0x40) = func_002E5CF8(0, 4, object);
        if (func_00282E48(position, target) < *(float *)(state + 8) * 0.016666668f)
            func_002A7750(object, 3, -1);
        break;
    case 3:
        sound = D_00188660 + *(int *)(state + 0x40) * 0x70;
        if (*(char **)(sound + 0x88) != object || *(u8 *)(sound + 0x74) == 0)
            *(int *)(state + 0x40) = func_002E5CF8(0, 4, object);
        position = ((MovingObjectView *)object)->position;
        target = (float *)(state + 0x20);
        func_002AA458(position, *(float *)(state + 8) * 0.00027777778f,
                       target, *(float *)(state + 8) * 0.00027777778f,
                       state + 0x14, *(float *)(state + 8) * 0.016666668f);
        if (func_00282E48(position, target) < *(float *)(state + 8) * 0.016666668f)
            func_002A7750(object, 2, -1);
        break;
    }
    if (*(u8 *)(object + 0x20) >= 2) {
        char *collisionPosition;
        func_L00_002E6CF0(func_L19_00420B48, object);
        collisionPosition = object + 0x10;
        func_002A8C00(4.0f, query, (int)object, 1, D_L19_001A8F20);
        *(u16 *)(query + 0x1A) = *(u16 *)(object + 0xAA);
        func_00282F20(delta, object + 0xE0, *(float *)(state + 0xC));
        func_00282CC0(delta, collisionPosition, delta);
        func_002761F8(collisionPosition, delta, 0, object, (int)query);
    }
}
