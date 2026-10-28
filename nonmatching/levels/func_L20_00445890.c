/* 28 October 2026: first full C attempt; retained 564/568 bytes at
 * -O2 -G8 -ffunction-sections. Six compiles. Naming the real missing
 * sentinel before the state change fixes object/loop-count allocation;
 * the remaining differences are the list-index GPR, tail color/store
 * merge and early high-bit constant slots. A 568-byte spelling still
 * had the object/count register swap. A switch is 596 bytes; explicit
 * packed-color temporaries and keep-block-order do not close the tail.
 * The GP alias and absolute view bind the same canonical object table.
 * Actual helper return contracts were checked from definitions or
 * retail return banks. No local/strict match. Original notes follow. */
/* func_L20_00445890 (568 bytes, level 20): NOT ATTEMPTED in this wave; the analysis is
 * recorded for the next attempt.
 *
 * The body is recovered from build/20_yeedil/asm/5B0B0.s:
 *  - the state is arg0[0x68]; if it is null the function returns;
 *  - `func_00283B98(state[0x20], 0.10471977f)` and `func_00283198(...)` with the state
 *    written back, then `* 4.0f - 3.0f`, then `* 128.0f` and func_00283CF0;
 *  - the result is clamped with `slti`/`movz` to 0x1F or 0x20 - the `movz` is what a
 *    ternary or a conditional assignment produces;
 *  - arg0[0x20] selects: 0 and 0xFE/0xFD go one way, 1 and 2 another (func_0029FCC0 and
 *    func_00282E80 with the boot table D_189EA0), 3 and 4 the third (func_002A0430);
 *  - the table at D_L20_001B2F9C is walked, a byte is set at +0xBC, and
 *    func_002A0F48 and func_L20_002C5A48 are called;
 *  - the return value is built with `or`/`sll` and stored at arg0[0x78].
 *
 * The walls: the `movz` clamp and the branch-likely loop (`beql`/`bgezl`), plus the exact
 * order of the two `or`/`sll` pairs at the end. The unit has to be the -G8 sibling (it
 * reads gp+0x3FAC).
 */

#include "common.h"

extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern void func_002A7750(unsigned char *, int, int);
extern void func_0029FCC0(char *, int, char *);
extern float func_00282E80(void *, void *);
extern void func_L00_003294F0(unsigned char *, int);
extern void func_002A0430(unsigned int);
extern void func_L20_002C5A48(int);
extern char *D_L20_001B2F9C;
extern char *yeedilObjectsGp SDATA(D_L20_001B2F9C);
extern struct {
    char reserved00[0x80];
    float position[4];
    char reserved90[0x33C - 0x90];
    unsigned char *owner;
    int active;
} D_00189E20;

typedef struct {
    int objects[4];
    int modes[4];
    float angle;
    int activated;
    unsigned int event;
    int callback;
} YeedilActivation;

void func_L20_00445890(unsigned char *object)
{
    float point[4] __attribute__((aligned(16)));
    YeedilActivation *state = *(YeedilActivation **)(object + 0x68);
    int color;
    if (!state) return;
    state->angle = func_00283B98(state->angle, 0.10471977f);
    color = func_00283CF0((func_00283198(state->angle) * 4.0f - 3.0f) * 128.0f);
    if (color > 128) color = 128;
    else if (color < 32) color = 32;
    if (object[0x20] == 0) {
        *(unsigned short *)(object + 0x34) |= 0x10;
        func_002A7750(object, 1, -1);
    } else if (object[0x20] == 1) {
        float distance;
        func_0029FCC0((char *)object, 0, (char *)point);
        distance = func_00282E80(D_00189E20.position, point);
        state->activated = 0;
        if (D_00189E20.owner == object && D_00189E20.active &&
            distance < *(float *)(object + 0x2C) * 0.5f / *(float *)(*(char **)(object + 0x24) + 0x24)) {
            int missing = -1;
            int enabled;
            int *entry;
            int remaining;
            func_002A7750(object, 2, missing);
            enabled = 1;
            entry = state->objects;
            for (remaining = 3; remaining >= 0; entry++, remaining--) {
                int index = *entry;
                if (index != missing) {
                    if (entry[4]) {
                        func_L00_003294F0((unsigned char *)(yeedilObjectsGp + (index << 8)), enabled);
                    } else {
                        *(unsigned char *)(D_L20_001B2F9C + (index << 8) + 0xBC) = enabled;
                    }
                }
            }
            func_002A0430(state->event);
            if (state->callback) func_L20_002C5A48(0);
        }
        *(unsigned int *)(object + 0x78) = color | 0x80000000;
    } else if (object[0x20] == 2) {
        if (!state->activated) state->activated = 1;
        {
            unsigned int green = (color << 8) | 0x80000000;
            unsigned int blue = color << 16;
            *(unsigned int *)(object + 0x78) = green | blue;
        }
    }
}
