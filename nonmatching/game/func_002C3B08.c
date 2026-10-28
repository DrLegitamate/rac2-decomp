/* 28 October 2026: 628/624 bytes in every US placement with the existing
 * -O2 -G0 -ffunction-sections -g profile. Plain TI transfers close the
 * retail object-relative quadword stores; qcopy reaches 632 bytes. Raw
 * and typed particle layouts tie at 628: object/current/motion use s1/s2/s0
 * instead of s2/s0/s1, with one repeated collision-argument move. The
 * remaining body and decay constants agree after that displacement.
 * Reopen with allocator evidence for the three pointer lifetimes.
 * Source is not linked and has not passed a strict build. */
#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00282C88(void *);
extern int func_00282978(void *);
extern void func_002B9180(void *);
extern int func_002AAE98(float, float, float, float);

extern char D_001BAFA0[];

typedef struct { int tag; unsigned int color; unsigned char age; char reserved[3]; float life; float position[4]; float motion[8]; } Particle;

void func_002C3B08(Particle *object)
{
    float position[4] __attribute__((aligned(16)));
    float *current;
    float *motion;
    typedef int Quad __attribute__((mode(TI)));
    if (!object) return;
    object->life += -100.0f;
    current = object->position;
    motion = object->motion;
    func_00282CC0(position, current, motion);
    if (motion[0] != 0.0f || motion[1] != 0.0f || motion[2] != 0.0f) {
        if (func_002761F8(current, position, 2, object, 0)) {
            *(Quad *)object->position = *(Quad *)D_001BAFA0;
            func_00282C88(motion);
            object->life += object->life;
        } else {
            *(Quad *)object->position = *(Quad *)position;
            if (motion[3] != 0.0f) motion[2] += motion[3];
            else motion[2] += -0.0063f;
        }
    }
    if (motion[7] <= 0.0f || func_00282978((char *)object + 0xA) ||
        object->life < 0.0f ||
        position[0] < 0.01f || position[1] < 0.01f || position[2] < 0.01f) {
        func_002B9180(object);
        return;
    }
    motion[4] += -0.01f;
    if (motion[4] < 0.0f) motion[4] = 0.0f;
    motion[5] += -0.03001f;
    if (motion[5] < 0.0f) motion[5] = 0.0f;
    motion[6] += -0.05f;
    if (motion[6] < 0.0f) motion[6] = 0.0f;
    if (motion[7] < 0.0f) motion[7] = 0.0f;
    object->color = func_002AAE98(motion[4], motion[5], motion[6], motion[7]);
    object->age--;
}
