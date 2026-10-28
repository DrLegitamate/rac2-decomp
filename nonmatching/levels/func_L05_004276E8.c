/* Retained reconstruction, USA v1.01.
 * 644/640 bytes with game -O2 -G8. The damage packet is reconstructed, but 2.0f is hoisted across the particle loop where retail rematerializes it; loop-bound and effect-scale lifetimes also change FPR allocation. A named bound and fno-rerun-loop-opt tie or worsen the result.
 * No strict linked match.
 */
#include "common.h"

typedef struct {
    float direction[4];
    void *attacker;
    int flags;
    u8 kind, mode;
    u16 object_class;
    float damage;
    int enabled;
} Impact;
extern float D_L05_001B1530 SDATA(D_L05_001B1530);
extern float D_L05_001B1534 SDATA(D_L05_001B1534);
extern float D_L05_001B1538 SDATA(D_L05_001B1538);
extern float D_L05_001B153C SDATA(D_L05_001B153C);
extern unsigned char *D_L05_001BFB18;
extern void func_00282F20(void *, void *, float);
extern void func_00277F48(void *, int, int, void *, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002A7820(int, int);
extern unsigned char *func_002BDCE8(void *, int, void *, int, int, float, float, float, float);
extern int func_002A77E0(int);

void func_L05_004276E8(unsigned char *object, unsigned char *state, float *position)
{
    Impact impact;
    float origin[4], velocity[4];
    float size, angle, index;
    float scale;
    int i;
    unsigned char *particle, *details;
    impact.flags = 0x810000;
    impact.attacker = object;
    if (*(int *)(state + 0x24) != 0)
        impact.damage = D_L05_001B153C;
    else
        impact.damage = D_L05_001B1538;
    impact.enabled = 1;
    qcopy(impact.direction, state);
    func_00282F20(impact.direction, impact.direction, 1.0f);
    impact.direction[3] = 5627.9248046875f;
    impact.kind = 3;
    impact.mode = 2;
    impact.object_class = *(u16 *)(object + 0xAA);
    if (*(int *)(state + 0x24) != 0)
        size = D_L05_001B1534;
    else
        size = D_L05_001B1530;
    func_00277F48(position, 1, *(int *)(state + 0x20), &impact, size);
    if (D_L05_001BFB18 != 0 && *(short *)(D_L05_001BFB18 + 0xAA) == 0x956) {
        scale = 3.0f;
        qcopy(origin, object + 0x10);
        for (i = 0; (float)i < 20.0f; i++) {
            index = (float)i;
            position[0] = origin[0] + func_002A78D8(index, 2.0f);
            position[1] = origin[1] + func_002A78D8(index, 2.0f);
            position[2] = origin[2] + func_002A78D8(index, 2.0f);
            angle = func_002A7940();
            func_002AF000(velocity, 0.05000000447034836f, angle, func_002A7940());
            particle = func_002BDCE8(position, func_002A7820(-3, 3), velocity,
                                      0x7FFFFFFF, 0, index, 1.0f, 1.0f, scale * 210000.0f);
            if (particle != 0) {
                *(short *)(particle + 0xA) = 120;
                details = particle + 0x20;
                particle[8] = func_002A77E0(255);
                particle[3] = 0x44;
                *(int *)(details + 4) = 2;
                details[0xA] = 127;
                details[0xB] = particle[0xA];
            }
        }
    }
}
