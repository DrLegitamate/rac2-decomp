/* Retained reconstruction, USA v1.01.
 * Game -O2 -G0 -g: 656/656 bytes; math and color packing match through +0x16C, then the three measured volatile source loads precede the local stores instead of interleaving. No synthetic volatile local was introduced. No-schedule-insns regresses the earlier math.
 * No strict linked match.
 */
#include "common.h"

/* The three velocity fields are read separately in order, interleaved with
 * the destination stores. Keep that measured access sequence. */
typedef struct {
    volatile float x, y, z;
} ParticleVelocity;

extern int func_00282948(short *);
extern int func_00282978(short *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CC0(float *, float *, float *);
extern void func_002B9180(void *);
extern void func_00300190(void *, void *);

void func_L00_0033EE38(unsigned char *particle)
{
    unsigned char *definition = particle + 0x20;
    float movement[4];
    ParticleVelocity *velocity;
    float scale, blend;
    int alpha;
    int remaining;
    unsigned int opacity;
    int original_opacity;

    particle[8] += definition[0xA];
    if (func_00282948((short *)(particle + 0x38))) {
        remaining = *(short *)(definition + 8) - *(short *)(particle + 0xA);
        if (remaining < *(short *)(definition + 0x1E)) {
            blend = (float)remaining * 0.2f;
            *(float *)(particle + 0xC) = *(float *)(definition + 4) +
                ((*(float *)(particle + 0x20) + *(float *)(definition + 4)) * 0.5f -
                 *(float *)(definition + 4)) * blend;
            opacity = definition[0xB];
            original_opacity = opacity;
            opacity >>= 1;
            alpha = func_00283CF0((float)original_opacity + (float)(int)(opacity - original_opacity) * blend);
        } else {
            blend = (float)*(short *)(particle + 0xA) /
                    func_00283CE0(*(short *)(definition + 8) - 6);
            *(float *)(particle + 0xC) = *(float *)(particle + 0x20) +
                ((*(float *)(particle + 0x20) + *(float *)(definition + 4)) * 0.5f -
                 *(float *)(particle + 0x20)) * blend;
            alpha = func_00283CF0((float)(definition[0xB] / 2) * blend);
        }
        velocity = (ParticleVelocity *)(definition + 0xC);
        *(unsigned int *)(particle + 4) = (alpha << 24) |
                                           (*(unsigned int *)(particle + 4) & 0xFFFFFF);
        movement[0] = velocity->x;
        movement[1] = velocity->y;
        movement[2] = velocity->z;
        movement[3] = 0.0f;
        func_00282CC0((float *)(particle + 0x10), (float *)(particle + 0x10), movement);
        if (*(float *)(particle + 0x10) < 2.0f || *(float *)(particle + 0x10) > 1021.0f ||
            *(float *)(particle + 0x14) < 2.0f || *(float *)(particle + 0x14) > 1021.0f ||
            *(float *)(particle + 0x18) < 2.0f || *(float *)(particle + 0x18) > 1021.0f ||
            func_00282978((short *)(particle + 0xA))) {
            func_002B9180(particle);
            return;
        }
    }
    if (*(float *)(particle + 0x1C) != 0.0f) {
        if (*(float *)(particle + 0x1C) == 2.0f)
            func_00300190(particle + 0x10, particle + 0x10);
        *(float *)(particle + 0x1C) = 2.0f;
    }
}
