/* Game -O2 -G8 with qcopy and qcopy-barrier: 632/632 bytes.
 * Sole instruction mismatch: +0xe4 is bnel versus retail bnez in the tier
 * clamp. Independent clamps shorten to 624 bytes; reversed source order
 * changes block order; -g leaves the same branch. The compiler does not
 * support -mno-branch-likely. GP and absolute owner views share canonical storage.
 * Next: an evidenced source layout for the non-annulled clamp slot.
 */
#include "common.h"
typedef int SiberiusQuad __attribute__((mode(TI)));
extern void func_002A7750(void *, int, int), func_00282A60(void *, int, int);
extern void func_00283098(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_002A0F48(void *);
extern float func_L07_003F90E8(int, int, float, float);
extern int func_00283CF0(float);
extern char D_L07_001FE3B8[], D_L07_001B9200[];
extern SiberiusQuad D_L07_001B1020[] SDATA(D_L07_001B1020);
extern float D_L07_001B1060[] SDATA(D_L07_001B1060);
extern unsigned char *D_L07_001B24B0 NOT_SDA;
extern unsigned char *siberiusOwnerGP __asm__("D_L07_001B24B0__gp") MACRO_ADDR;
#define CHILD(offset) (*(unsigned char **)(state + (offset)))
#define FLAGS(p) (*(unsigned short *)((p) + 0x34))

void func_L07_003F7968(unsigned char *object, unsigned char *target, int tier)
{
    char *state = *(char **)(object + 0x68);
    unsigned char *owner;
    float duration, low, high;
    int index;
    FLAGS(object) = (FLAGS(object) & 0xffbe) | 0x1000;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    FLAGS(object) &= 0xff7f;
    if (CHILD(0x410)) {
        FLAGS(CHILD(0x410)) &= 0xffbe;
        FLAGS(CHILD(0x410)) |= 0x1000;
        *(int *)(CHILD(0x410) + 0x98) = *(int *)(*(char **)(CHILD(0x410) + 0x24) + 0x10);
        FLAGS(CHILD(0x410)) &= 0xff7f;
    }
    if (CHILD(0x414)) {
        FLAGS(CHILD(0x414)) &= 0xffbe;
        FLAGS(CHILD(0x414)) |= 0x1000;
        *(int *)(CHILD(0x414) + 0x98) = *(int *)(*(char **)(CHILD(0x414) + 0x24) + 0x10);
        FLAGS(CHILD(0x414)) &= 0xff7f;
    }
    if (target) {
        index = tier;
        if (index > 1) index = 1;
        else if (index < 0) index = 0;
        *(SiberiusQuad *)(state + 0x3e0) = D_L07_001B1020[index];
        CHILD(0x418) = target;
        func_002A7750(object, 3, 0);
        owner = siberiusOwnerGP;
    } else {
        CHILD(0x418) = 0;
        func_002A7750(object, 3, 1);
        owner = D_L07_001B24B0;
    }
    if (!owner) {
        D_L07_001B24B0 = object;
        func_00282A60(D_L07_001FE3B8, 0, 0xe0);
    }
    duration = (float)*(short *)(state + 0x24);
    low = duration - duration * ((float)(tier + 1) * 0.16694492101669312f);
    high = duration - duration * ((float)tier * 0.16694492101669312f);
    state[0x2e] = 1;
    *(float *)(state + 0x430) = low;
    *(float *)(state + 0x20) = high;
    if (low < 0.0f) *(float *)(state + 0x430) = 0.0f;
    *(float *)(object + 0xf4) = *(float *)(object + 0xf0) = 0.0f;
    func_00283098(object + 0x10, D_L07_001B1060, D_L07_001B9200 + 0x230);
    func_00282CC0(object + 0x10, object + 0x10, D_L07_001B9200);
    func_002A0F48(object);
    qzero(state + 0x3f0);
    if (tier >= 0) {
        *(int *)(state + 0x420) = tier;
        *(int *)(state + 0x458) = func_00283CF0(func_L07_003F90E8(3, 7, 4.0f, 1.0f));
    }
}
#undef CHILD
#undef FLAGS
