/* Batch 3 (2026-10-28) handoff notes:
func_L01_003D25B8 (260 B): needs L01_003D25B8-g8.c (-G8) and `extern f32 D_L01_001B0540 __attribute__((sda));` (scalar) so lwc1 is $gp. draft.c is that file (canonical callee names: func_0029EFD0, func_002E5CF8, func_002A0F48, func_002AB650). 11 masked lines; the prologue through the three qcopies matches exactly (statement order from a hill-climb).
Left, three groups:
 1. retail loads `lwc1 $f1,0x1550($gp)` before `lw $v0,0x24($s0)`; ours after.
 2. retail updates q in place: `sll $v0,$s3,2; addiu $v1,$zero,-1; addu $t0,$t0,$v0; ...; lw $v0,0x10($t0)` (q first operand, lw issued early); ours `addu $v0,$v0,$t0` (shift first), lw later.
 3. consequence of 2: retail `sw $zero,0x78($a3)` sits in the jal delay slot after `sw $v0,0x74`; ours stores 0x78 before 0x74.
Tried: q + idx*4 + 0x10 in 6 spellings incl. (s32)q + (idx<<2), a named `off = idx * 4`, p/q declaration order and init, idx u32/int, local scale, 3 hill-climbs from random starts (best 11, others 16+).
*/

#include "common.h"

extern u8 *func_0029EFD0(s32 a0);
extern s32 func_002E5CF8(s32 a0, s32 a1, void *a2);
extern void func_002A0F48(void *a0);
extern void func_002AB650(void *a0);
extern f32 D_L01_001B0540 __attribute__((sda));

/* Spawns the object a3 names and starts it with the vectors a1 and a2. */
u8 *func_L01_003D25B8(u8 *a0, void *a1, void *a2, u32 a3, s32 idx)
{
    u8 *s0 = func_0029EFD0(a3);
    u8 *p;
    u8 *q;

    if (s0 != 0) {
        q = *(u8 **)(a0 + 0x68);
        p = *(u8 **)(s0 + 0x68);
        s0[0x30] = 0xFF;
        s0[0x31] = 1;
        *(u16 *)(s0 + 0x32) = 0xFF;
        s0[0x20] = 0;
        s0[0xBC] = 0;
        *(u8 **)(p + 0x70) = a0;
        *(u16 *)(p + 0x7C) = idx;
        *(f32 *)(s0 + 0x2C) = *(f32 *)(*(u8 **)(s0 + 0x24) + 0x24) * D_L01_001B0540;
        qcopy(s0 + 0x10, a1);
        qcopy(s0 + 0xF0, a2);
        qcopy(p + 0x60, a1);
        *(s16 *)(p + 0x7E) = -1;
        *(s32 *)(p + 0x74) = *(s32 *)(q + idx * 4 + 0x10);
        *(s32 *)(p + 0x78) = 0;
        func_002E5CF8(2, 0, s0);
        func_002A0F48(s0);
        func_002AB650(s0);
    }
    return s0;
}
