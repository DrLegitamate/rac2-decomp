/* func_002914B8 (388 B, 28 places), best retained direct-field-pointer form:
   380/388 bytes, 0/28 USA v1.01 places in -O2 -G16 -Wa,-G16 -ffunction-sections.
   A 29 October replay confirmed 380/388; moving both pointer increments to the
   for-update clause produced the same bytes and diff.
   The earlier struct-pointer candidate was 388/388 and 0/28. The listener part
   matches; in the channel loop retail walks two pointers straight at the pos
   fields (+0x20 stride 0x30, +0x10 stride 0x20, state at -0x10). The pointer
   form reduces code by eight bytes but still differs in loop/register allocation.
   Per-program callee ref_L00_002FD068_00. */
#include "common.h"

typedef int TI __attribute__((mode(TI)));

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
} Emit2914B8;

typedef struct {
    u8 pad00[0x10];
    s32 state;
    u8 pad14[0xC];
    f32 pos[4];
} Chan2914B8;

typedef struct {
    u8 pad000[0x340];
    f32 pos[4];
    f32 dir[4];
} Snd2914B8;

extern TI D_001A9190 __attribute__((sda));
extern Snd2914B8 D_001C2740;
extern f32 D_001B5358[];
extern Emit2914B8 D_001C2B40[8];
extern Chan2914B8 D_001C2C40[8];

extern float func_00282C48(float);
extern float func_00282E48(void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern void func_00291640(int);
extern void ref_L00_002FD068_00(int);

void func_002914B8(void) {
    f32 *em = (f32 *)((u8 *)D_001C2B40 + 0x10);
    f32 *ch = (f32 *)((u8 *)D_001C2C40 + 0x20);
    f32 ang;
    s32 i;

    qcopy(D_001C2740.pos, &D_001A9190);
    ang = func_00283B98(D_001B5358[0], -0.8f);
    D_001C2740.dir[0] = func_00283180(ang) * 0.866f;
    D_001C2740.dir[1] = func_00283198(ang) * 0.866f;
    D_001C2740.dir[2] = -0.5f;
    D_001C2740.dir[3] = 0.0f;
    for (i = 0; i < 8; i++) {
        s32 *state = (s32 *)((u8 *)ch - 0x10);
        if (*state != 0) {
            if (1.0f < func_00282E48(em, ch) || 1.0f < func_00282C48(em[3] - ch[3])) {
                qcopy(ch, em);
                if (*state == 1) {
                    func_00291640(i);
                    *state = 2;
                } else if (*state == 2) {
                    ref_L00_002FD068_00(i);
                }
            }
        }
        ch += 12;
        em += 8;
    }
}
