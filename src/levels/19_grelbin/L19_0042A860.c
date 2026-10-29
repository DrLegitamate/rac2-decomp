#include "common.h"

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L19Thing {
    u8 pad[0xAA];
    s16 kind;
} L19Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L19Group {
    u8 pad0[0x44];
    s16 count;
    u8 pad1[0x18C - 0x46];
    L19Thing *items[1];     /* bounded by count */
} L19Group;

extern L19Group D_L19_001BD740;
extern s32 D_L19_001A8F00[] __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u8 D_L19_001B22E0[] __attribute__((sda));
extern f32 D_L19_001B2300[] __attribute__((sda));

extern void func_0029F978(u8 *, u32, u8 *);

INCLUDE_ASM("asm/levels", func_L19_0042A8B8);

/* func_L19_0042A9A0 is in L19_0042A9A0.c. */

void func_L19_0042AF70(L19Thing *a0)
{
    L19Thing *e;
    s32 i;

    if (D_L19_001A8F00[0] != 2)
        return;
    if (D_001A7A40[0] == 0)
        return;
    for (i = 0; i < D_L19_001BD740.count; i++) {
        e = D_L19_001BD740.items[i];
        if (e->kind != a0->kind)
            continue;
        if (D_L19_001B22E0[1] != 0)
            continue;
        func_0029F978((u8 *)e, 0, D_L19_001B22E0);
        D_L19_001B2300[0] = 1.9f;
        D_L19_001B2300[1] = 1.9f;
        D_L19_001B2300[2] = 1.9f;
    }
}

INCLUDE_ASM("asm/levels", func_L19_0042B058);
