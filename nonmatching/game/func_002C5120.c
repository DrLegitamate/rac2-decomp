/* 28 October 2026: 716/732 bytes under this unit's -O2 -G0 -g profile.
 * Raw and typed follower state views tie. The retained C uses one fewer
 * saved pointer, a 0x60 rather than 0x70 frame, and a different opacity
 * interpolation expression schedule. No strict match is claimed.
 * Reopen with pointer-lifetime and allocator evidence. */
#include "common.h"
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern int func_00282978(void *);
extern void func_002B9180(void *);

extern void func_00300190(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float D_001AA3C0 __attribute__((sda));
extern char D_0018A0E0[];

typedef struct { float start, end; short duration; unsigned char spin, opacity; float speed[3]; char *owner; } FollowerMotion;

void func_002C5120(char *object)
{
    float velocity[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float side[4] __attribute__((aligned(16)));
    FollowerMotion *motion = (FollowerMotion *)(object + 0x20);
    float *speed;
    int elapsed;
    float ratio, alpha;
    *(unsigned char *)(object + 8) += motion->spin;
    elapsed = motion->duration - *(short *)(object + 0xA);
    if (elapsed < 6) {
        float target = motion->end;
        ratio = (float)elapsed * 0.2f;
        *(float *)(object + 0xC) = target + ((motion->start + target) * 0.5f - target) * ratio;
        alpha = motion->opacity;
        alpha += ((motion->opacity >> 1) - motion->opacity) * ratio;
    } else {
        float duration = func_00283CE0(motion->duration - 6);
        float start = motion->start;
        ratio = (float)*(short *)(object + 0xA) / duration;
        *(float *)(object + 0xC) = start + ((start + motion->end) * 0.5f - start) * ratio;
        alpha = (float)(motion->opacity >> 1) * ratio;
    }
    *(int *)(object + 4) = (*(int *)(object + 4) & 0xFFFFFF) | (func_00283CF0(alpha) << 24);
    speed = motion->speed;
    velocity[0] = speed[0];
    velocity[1] = speed[1];
    velocity[2] = speed[2];
    velocity[3] = 0.0f;
    func_00282CC0(object + 0x10, object + 0x10, velocity);
    func_00300190(object + 0x10, object + 0x10);
    if (motion->owner) {
        func_00282CF0(difference, motion->owner + 0x10, object + 0x10);
        if (difference[0] <= 2.0f && difference[1] <= 2.0f) {
            func_00282DD8(side, difference, D_0018A0E0);
            func_00282F20(side, side, D_001AA3C0);
            func_00282CC0(object + 0x10, object + 0x10, side);
            if (difference[0] <= 0.5f && difference[1] <= 0.5f) {
                func_00282F20(velocity, difference, 0.03f);
            } else {
                float magnitude = func_00282DF0(velocity);
                func_00282F20(velocity, difference, magnitude);
            }
        }
    }
    velocity[2] += 0.02f;
    speed[0] = velocity[0];
    speed[1] = velocity[1];
    speed[2] = velocity[2];
    if (func_00282978(object + 0xA)) func_002B9180(object);
}
