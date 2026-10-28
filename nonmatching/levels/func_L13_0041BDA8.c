/* Batch 3 (2026-10-28) handoff notes:
draft.c: new file src/levels/13_boldan/L13_0041BDA8.c (default flags), marker removed from L13_00306F38.c. Callee names made canonical (func_002ACBC8 = retail func_32A4D0, func_00282F20 = retail func_2F8A20).
224 B vs 220, 42 masked diff lines. for (i = 7; i >= 0; i--) is the closest loop form (tested: --i>=0, do/while (i-- > 0), do/while(--i != 0), for i<8 with ids++ in header, res pointer for D_00189E20).
Differences: retail builds D_00189E20 as a full address before the loop (lui v0,0x19; addiu s5,v0,-0x61E0) and stores 10.0f at 0x2FC(s5); ours folds +0x2FC into a lui-only base (swc1 0x2FC($s3)). Retail loop is entered by fall-through, the counter decrement sits in the body and bgez tests at the bottom; ours enters with b into the middle and uses bltzl in the body; ours also uses a seventh saved reg (s6 = -1) where retail uses s4 for -1.

UPDATE (later attempt): draft.c now has the loop in retail's shape: `i = 7; do { ... ids++; } while (--i >= 0);` (bgez at bottom, no entry jump) and D_L13_001B2A0C declared `__attribute__((sda))` (macro form, not hoisted: 6 saved regs like retail). 212 B vs 220. Still different: retail copies the loaded state pointer `lw a1,0x68(a0)` ... `daddu s0,a1,zero` before the loop, holds D_00189E20 as full address in s5 (`addiu s5,v0,-0x61E0`, store 0x2FC(s5)), and s3 = lui 0x19 for the 9EA0 pieces; ours folds the 0x2FC store into a lui-only base.
*/

#include "common.h"



extern u8 D_00189EA0[];
extern u8 D_00189E20[];
extern s32 D_L13_001B2A0C __attribute__((sda));
extern s32 func_002ACBC8(u8 *, s32);
extern void func_00282F20(u8 *, u8 *, f32);

void func_L13_0041BDA8(u8 *a0) {
    s32 *ids;
    s32 i;

    if (a0[0x20] == 0) {
        a0[0x20] = 1;
        a0[0x30] = 0xFF;
    }
    ids = *(s32 **)(a0 + 0x68);
    i = 7;
    do {
        if (*ids == -1)
            break;
        if (func_002ACBC8(D_00189EA0, *ids) == 0)
            break;
        func_00282F20(D_00189EA0 + 0x270, (u8 *)(D_L13_001B2A0C + (*ids << 7)), -1.0f);
        *(f32 *)(D_00189E20 + 0x2FC) = 10.0f;
        ids++;
    } while (--i >= 0);
}
