/* Batch 3 (2026-10-28) handoff notes:
draft.c: new file src/levels/13_boldan/L13_003E8850.c, cflags line `-O2 -G0 -ffunction-sections` (default); marker removed from L13_00306F38.c. 432 B vs 440; 65 masked lines (mostly shift).
New vs the old draft: in case 1 the hero base must be a pointer (`hero = D_00189E20; hero[0x2294]; func(hero + 0x80, ...)`), which gives retail's `addiu v0,v0,-0x61E0` + `addiu a0,v0,0x80`. First 0x98 bytes then match.
Left: (1) the `&&` after func_002ACBC8 in case 1: retail is `beql v0,zero,common` with the common block's first `lw a1,0(s2)` in the slot, then `lui v0,0x1A; lbu v0,0x7A64(v0)`; ours is `beqz` with the sda-array byte load in the slot (assembler turns it into `lbu v0,0($gp)`); (2) same for the store `lui at; sb s1,0x7A64($at)`; (3) D_0018C750/D_0013F5B8 bases: retail keeps `lui v0,0x19; addiu v0,v0,-0x38B0` (base) and `lui v1,0x14; addiu s0,v1,-0x6A48`.
Tried: plain externs at G8 (shared lui in s0), MACRO_ADDR scalars, -mno-split-addresses (arrays become la macros, 460 B), sda scalars.
*/

#include "common.h"

extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern u8 D_0018C750[];
extern u8 D_0013F5B8[];
extern u32 D_001A7390[] __attribute__((sda));
extern u8 D_001A7A64[] __attribute__((sda));
extern s32 D_001A903C[] __attribute__((sda));
extern s32 D_0018CC18;
extern s32 func_002ACBC8(void *a0, s32 a1);
extern void func_002E5E58(s32 a0, s32 a1, s32 a2);
extern void func_002B0A18(s32 a0, s32 a1);
extern void func_00288E18(s32 a0, s32 a1);

void func_L13_003E8850(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    s16 h;
    u8 *hero;

    if (self[0x20] == 0) {
        self[0x30] = 0xFF;
        *(s16 *)(state + 0xC) = 0;
        self[0x20] = 1;
    }
    if (self[0x20] != 1)
        return;
    h = *(s16 *)(state + 0xE);
    switch (h) {
    case 0:
        if (func_002ACBC8(D_00189EA0, *(s32 *)(state + 4)) != 0 && *(s32 *)(D_00189EA0 + 0x221C) == 0xF)
            *(s16 *)(state + 0xE) = 1;
        break;
    case 1:
        hero = D_00189E20;
        if (*(s32 *)(hero + 0x2294) == 0x3E) {
            *(s16 *)(state + 0xE) = 0;
        } else if (func_002ACBC8(hero + 0x80, *(s32 *)(state + 8)) != 0 && D_001A7A64[0] == 0) {
            func_002E5E58(1, 0, 0);
            D_001A7A64[0] = 1;
            func_002B0A18(0x1233, -1);
            D_001A903C[0] = 1;
        }
        break;
    }
    if (func_002ACBC8(D_00189EA0, *(s32 *)state) == 0)
        return;
    if (*(u16 *)(D_0018C750 + 0x1BC) != 0 && !(D_001A7390[0] - *(u32 *)(D_0018C750 + 0x1C0) > 0x69780))
        return;
    if (D_0013F5B8[0x7E] < 2 && *(s16 *)(state + 0xC) == 0) {
        if (D_0018CC18 >= 0)
            func_00288E18(0x9E3, 0x3A);
        D_0013F5B8[0x7E] = D_0013F5B8[0x7E] + 1;
        *(s16 *)(state + 0xC) = 1;
    }
}
