/* Batch 3 (2026-10-28) handoff notes:
draft.c: new file src/levels/19_grelbin/L19_0042AF70.c with cflags line `-O2 -G0 -ffunction-sections -mno-split-addresses`; marker removed from L19_0042A860.c. 232/232 B, 8 masked lines. Names not yet made canonical (func_0029F978; data names ok).
-mno-split-addresses is the missing piece of the old draft (absolute lui/lbu and lui at/swc1 per use now match, no 264-byte hoisting). Same residual as func_L19_0042A8B8 (sibling, identical shape): retail forms the list address in a temp (lui v1; addiu v1,-0x28C0), reads the count at 0x44(v1) for the guard, then copies it (daddu s2,v1,zero) into the saved reg for the loop and uses s2+0x18C; ours puts the address straight in s2 (so the guard lh uses s2 and reorg cannot fill the beqz delay slot with lui). Fixing one fixes both.
Tried: p/q two pointers (240 B, double guard), struct-typed global with for loop (7 lines, still s2), block/list locals.
*/

#include "common.h"

extern s32 D_L19_001A8F00;
extern u8 D_001A7A40;
extern u8 D_L19_001B22E1;
extern u8 D_L19_001B22E0[];
extern f32 D_L19_001B2300;
extern f32 D_L19_001B2304;
extern f32 D_L19_001B2308;
extern u8 D_L19_001BD740[];
extern void func_0029F978(u8 *, u32, u8 *);

void func_L19_0042AF70(u8 *obj)
{
    u8 *block;
    u8 **entry;
    int i;
    if (D_L19_001A8F00 != 2) return;
    if (!D_001A7A40) return;
    block = D_L19_001BD740;
    if (*(s16 *)(block+0x44) <= 0) return;
    entry = (u8 **)(block+0x18c);
    i=0;
    do {
        u8 *object = *entry;
        if (*(s16 *)(object + 0xaa) == *(s16 *)(obj + 0xaa) && !D_L19_001B22E1) {
            func_0029F978(object, 0, D_L19_001B22E0);
            D_L19_001B2300 = 1.9f;
            D_L19_001B2304 = 1.9f;
            D_L19_001B2308 = 1.9f;
        }
        i++;
        entry++;
    } while (i < *(s16 *)(block+0x44));
}
