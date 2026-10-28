/* Game -O2 -G0: 668/664 bytes, 0/1 USA place. Accurate callee
 * contracts retain the object-word return from func_002ED688 and the
 * float-only func_L05_0037AC80 call. The source snapshot and five-vector
 * scratch layout reproduce their transfers. Remaining collision-call slot,
 * persistent stack-pointer allocation, and particle constant scheduling differ.
 * Typed shock fields, scalar/aggregate scratch, truthful particle ABI bank
 * interleaving, countdown/upcount loops and no-gcse/no-rerun-loop-opt were tried.
 * Next: inspect original collision interfaces and the particle loop lifetimes.
 */
#include "common.h"
typedef struct { int value[2]; } FeltzinColours;
typedef struct { char pad[0x160]; float amount; int gap164; int timer, counter; } FeltzinShock;
extern FeltzinColours D_L05_001B1308[];
extern int func_002ED688(void *);
extern void func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, float), func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L05_0037AC80(float), func_0029FCC0(void *, int, void *);
extern int func_002A7820(int, int), func_001163B0(void), func_00283CF0(float);
extern float func_002A7878(float, float), func_00283CE0(int);
extern char *func_002BDCE8(void *, int, void *, int, float, float, float, float, int);
extern char *D_L05_001BFB18;
extern char D_L05_001B9580[];

void func_L05_0041CB68(char *object)
{
    struct {
        float delta[4], original[4], velocity[4], probe[4], point[4];
        FeltzinColours colours;
    } scratch;
    char *state = *(char **)(object + 0x68);
    char *source, *target, *particle, *effect;
    int i, count, pick;
    float speed;
    unsigned char colour;
    source = (char *)func_002ED688(object);
    if (!source || !(target = *(char **)(source + 0x120)) || *(int *)(state + 0x268)) return;
    func_00282CF0(scratch.delta, target + 0x10, object + 0x10);
    /* Retail keeps a complete position snapshot even though later operations use the object. */
    qcopy(scratch.original, object + 0x10);
    func_00282F20(scratch.velocity, scratch.delta, 0.5833333730697632f);
    func_00282F20(scratch.probe, scratch.delta, 5.0f);
    func_00282CC0(scratch.probe, scratch.probe, object + 0x10);
    if (func_002761F8(object + 0x10, scratch.probe, 0, object, 0) && D_L05_001BFB18 && *(short *)(D_L05_001BFB18 + 0xaa) == 0xfbf) {
        ((FeltzinShock *)D_L05_001B9580)->amount = 0.05f;
        ((FeltzinShock *)D_L05_001B9580)->timer = 30;
        ((FeltzinShock *)D_L05_001B9580)->counter = 0;
        func_L05_0037AC80(1.0f);
    }
    func_0029FCC0(object, 0, scratch.point);
    for (i = 2; i >= 0; i--) {
        count = func_002A7820(1, 5);
        particle = func_002BDCE8(scratch.point, count, scratch.velocity, 0x5a182, 0.0f, 1.0f, 1.01f,
                                func_002A7878(0.25f, 1.0f) * 210000.0f, 1);
        scratch.colours = D_L05_001B1308[0];
        if (particle) {
            effect = particle + 0x20;
            pick = func_001163B0() % 2;
            colour = scratch.colours.value[pick];
            *(short *)(particle + 0xa) = 35;
            particle[3] = colour;
            particle[9] = func_00283CF0(4.0f) + 64;
            speed = func_00283CE0(5);
            *(int *)(effect + 4) = 3;
            *(float *)(effect + 0x1c) = speed;
            effect[0xa] = func_002A7820(64, 128);
            effect[0xb] = particle[0xa];
        }
    }
    *(int *)(state + 0x268) = 4;
}
