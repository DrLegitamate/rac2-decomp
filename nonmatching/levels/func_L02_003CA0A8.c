/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 profile: -O2 -G8 -ffunction-sections -mno-split-addresses -fno-gcse.
 * 468/468 bytes; first mismatch +0x34 across 18 US places. Real GP aliases, absolute scalar views, packed pairs and aligned copies reconstruct the particle loop. Remaining initialization scheduling and pair-address allocation differ.
 * US object comparison only in this retry; no linked strict-build claim.
 * Reopen with a measured allocation, scheduling or source-interface witness.
 */
#include "common.h"
typedef unsigned int ParticleQuad __attribute__((mode(TI)));
struct ParticlePair { float low, high; } __attribute__((packed));
extern float D_L02_001AFFC0 SDATA(D_L02_001AFFC0);
extern float D_L02_001AFFC4 NOT_SDA;
extern int D_L02_001AFFC8 SDATA(D_L02_001AFFC8);
extern int D_L02_001AFFCC NOT_SDA;
extern int D_L02_001AFFD0 SDATA(D_L02_001AFFD0);
extern int D_L02_001AFFD4 NOT_SDA;
extern float D_L02_001AFFD8 SDATA(D_L02_001AFFD8);
extern float D_L02_001AFFDC NOT_SDA;
extern struct ParticlePair D_L02_001AFFE0;
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern int func_00283D38(int, int, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_002A77E0(int);
extern void func_002C3150(void *, void *, int, int, int, int, float);
extern void func_00282D30(void *, void *, float);
void func_L02_003CA0A8(unsigned char *m)
{
    float position[4];
    struct ParticlePair speed;
    struct ParticlePair step;
    float velocity[4];
    float angle;
    float zero;
    int remaining, color;
    int size;
    float radius;
    struct ParticlePair *turn;
    qcopy(position, m + 0x10);
    turn = &D_L02_001AFFE0;
    position[2] += 0.5f;
    step.low = D_L02_001AFFC0 * 0.016666668f;
    step.high = D_L02_001AFFC4 * 0.016666668f;
    angle = 0.0f;
    zero = 0.0f;
    speed = step;
    step = *turn;
    for (remaining = 31; remaining >= 0; remaining--) {
        size = func_002A7820(D_L02_001AFFC8, D_L02_001AFFCC);
        {
            float blend = func_002A7878(zero, 1.0f);
            size &= 255;
            color = func_00283D38(D_L02_001AFFD0, D_L02_001AFFD4, blend);
        }
        radius = func_002A7878(speed.low, speed.high);
        velocity[0] = func_00283180(angle) * radius;
        velocity[1] = func_00283198(angle) * radius;
        velocity[2] = zero;
        angle = func_00283B98(angle, func_002A7878(step.low, step.high));
        func_002C3150(position, velocity, color, size, (unsigned char)func_002A77E0(255), 0, D_L02_001AFFD8);
        func_00282D30(velocity, velocity, 0.8f);
        func_002C3150(position, velocity, color, size, (unsigned char)func_002A77E0(255), 0, D_L02_001AFFDC);
    }
}
