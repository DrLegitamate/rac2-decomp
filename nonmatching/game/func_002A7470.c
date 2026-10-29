/* func_002A7470 - 364 bytes, 28 places (boot + 27 levels). Rechecked 28 October 2026: 364/364
 * bytes, 0/28 USA v1.01 places, with -O2 -G8 -ffunction-sections -frac2-qcopy. M35: size exact;
 * -ffunction-sections in its own unit; the slot copy is qcopy() into the
 * per-program table, the tail reads the animation byte at 0x11. Only the head is
 * off: retail keeps animation*4 in $a0 and the frame count in $a0 (this cc1: $v1/$v0),
 * 6 instructions, register allocation only. A 28 Oct probe used the already-
 * written object[0x43] for the final table lookup to shorten the argument's
 * live range across calls; it grew to 368/364 bytes and remained 0/28. A 29 Oct local `animation + 0x12` index for the first lookup measured 368/364.
 * A typed `entries = table + 0x48; entries[animation][0x10]` view stayed 364/364
 * but retained the register mismatch; computing `last_frame` before the bound
 * test also stayed nonmatching and changed its instruction order. All probes were
 * 0/28. Keep this 364-byte form. */
#include "common.h"

typedef int TI128_002A7470 __attribute__((mode(TI)));

typedef struct {
    char pad[0x48];
    unsigned char *anims[1];
} Model_002A7470;

extern void func_002A7398(unsigned char *, int, int);
extern int func_0029FA88(void *);
extern void func_002A2450(void *, int);
extern void func_0029F390(void *);
extern float func_00283CE0(int);
extern TI128_002A7470 ref_L00_002A7470_00[];

void func_002A7470(unsigned char *object, int animation, int frame, int rate)
{
    int frame_count;
    int last_frame;
    int slot;
    float reciprocal;
    int use_frame;

    frame_count = (*(unsigned char ***)(object + 0x24))[animation + 0x12][0x10];
    use_frame = frame < frame_count;
    last_frame = frame_count - 1;
    if (use_frame)
        last_frame = frame;

    if (rate <= 0) {
        func_002A7398(object, animation, last_frame);
        return;
    }

    if (0.025f < *(float *)(object + 0x44) ||
        *(unsigned int *)(object + 0x50) != 0 ||
        *(unsigned int *)(object + 0x54) != 0) {
        slot = func_0029FA88(object);
        if (slot >= 0) {
            func_002A2450(object, slot | 0x300);
            qcopy(&ref_L00_002A7470_00[slot], object + 0x80);
            if (object[0x42] != 0xFF)
                object[0xA9] = object[0x42];
            object[0x42] = 0xFF;
            object[0x40] = slot;
        }
    }

    object[0x41] = last_frame;
    object[0x43] = animation;
    func_0029F390(object);
    *(float *)(object + 0x48) = 1.0f;
    reciprocal = 1.0f / func_00283CE0(rate);
    *(unsigned int *)(object + 0x44) = 0;
    object[0x60] &= 0xFD;
    *(float *)(object + 0x4C) = reciprocal;
    object[0x6C] = (*(Model_002A7470 **)(object + 0x24))->anims[animation][0x11];
}
