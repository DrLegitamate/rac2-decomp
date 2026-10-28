/* Batch 3 (2026-10-28) handoff notes:
draft.c: new file src/levels/13_boldan/L13_003EFD58.c (default flags), marker removed from L13_00306F38.c. Plain switch (no computed goto), canonical callee names. Size 364/364.
Left: the default (sel >= 5) arm. Retail jumps with the switch's own beqz straight to the shared `sh $v0,0x96($s0)` where $v0 is the sltiu result (0); ours emits `daddu $v0,$zero,$zero` first (val = 0 in default) - 1 extra insn at +0x1c and everything after is shifted (34 masked lines are all that shift).
An old draft got 360 B by writing `val = (s32)(sel < 5)` and a computed goto into the jump table; that is not honest C. Tried here: default: val = 0 with one shared store, switch with default: *(u16*)(a0+0x96)=0 (separate sh zero).
*/

#include "common.h"

extern f32 func_00283B98(f32, f32);
extern s32 func_002B3868(u8 *);
extern void func_002E5CF8(s32, s32, u8 *);
extern void func_002AAA00(f32 *, u8 *, f32, f32, f32, f32, s32);
extern void func_002A7750(u8 *, s32, s32);

void func_L13_003EFD58(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    u16 v;
    s32 val;
    s32 arg;

    switch (a0[0x20]) {
    case 0:
        a0[0x30] = 0xFF;
        *(f32 *)(s1 + 8) = *(f32 *)(a0 + 0xF0);
        *(f32 *)s1 = func_00283B98(*(f32 *)(a0 + 0xF0), 0.78539824f);
        a0[0x20] = 1;
        *(u16 *)(a0 + 0x96) = 0;
        return;
    case 1:
        if (func_002B3868(a0))
            func_002E5CF8(0, 0, a0);
        func_002AAA00((f32 *)(a0 + 0xF0), s1 + 4, *(f32 *)s1, 0.00087266474f, 0.00087266474f,
                      0.10471977f, 0);
        v = *(u16 *)(a0 + 0x96);
        if (v < 0x79) {
            val = v + 1;
            break;
        }
        arg = 3;
        goto call;
    case 3:
        if (func_002B3868(a0))
            func_002E5CF8(0, 0, a0);
        func_002AAA00((f32 *)(a0 + 0xF0), s1 + 4, *(f32 *)(s1 + 8), 0.00087266474f,
                      0.00087266474f, 0.10471977f, 0);
        v = *(u16 *)(a0 + 0x96);
        if (v < 0x79) {
            val = v + 1;
            break;
        }
        arg = 1;
    call:
        func_002A7750(a0, arg, -1);
        *(u16 *)(a0 + 0x96) = 0;
        return;
    case 2:
    case 4:
        return;
    default:
        val = 0;
        break;
    }
    *(u16 *)(a0 + 0x96) = val;
}
