/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections (in place in src/levels/11_joba/L11_0043E1A0.c).
 * Retail: 392 bytes; compiled: 392 bytes.
 * Coverage: us: 0/1 (tools/check.py, 28 October 2026, master 85614b41).
 * History: this replaces the wave-8 draft (commit 431ac503, recoverable with
 * `git show 431ac503:nonmatching/levels/func_L11_00440C90.c`). That draft now compiles
 * 68 lines off at +0x24, and its 0xDF9 path attaches OTHER and returns 1 where retail
 * returns 0 when func_L02_003D77F8 refuses it.
 * Residual (10 lines): the slot base (state + 0x120) and OTHER swap saved registers -
 * retail keeps OTHER in $s1 and the base in $s2 - and the two `addu` operand orders
 * follow. Control flow, the per-case 1.0 weight, the shared store and the separate
 * `return 0` block all match.
 * Measured: an early `return 0` per test instead of one guarded block (388 bytes, the
 * return block moves); the 1.0 store without a per-case variable (352); the base as
 * `u8 **` indexed or `u8 *` with `* 4` (same 10 lines); assigning the base late,
 * declaring the weight first, copying OTHER to a local (same); no base variable (90).
 * Reopen: a spelling that gives OTHER the lower saved register.
 */
#include "common.h"

extern s32 func_L02_003D77B8(u8 *);
extern s32 func_L02_003D77F8(u8 *);
extern void func_L02_003D7868(u8 *, u8 *);

/* Adds OTHER to the group in the state's current slot (+0x120, indexed by +0x18C) when that
   group exists and accepts it: the class of OTHER is counted (0xD98 +0x100, 0xDCF +0x104,
   0xDF4 +0x108, 0xDF7 +0x10C, 0xDF9 +0x110 unless the group refuses it, 0xD37 +0x114) and
   its state's +0x20 set to 1.0. Returns 1 when added, else 0. */
s32 func_L11_00440C90(u8 *obj, u8 *other)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 *slots = state + 0x120;
    f32 weight;

    if (*(u8 **)(slots + *(s32 *)(state + 0x18C) * 4) != 0 &&
        func_L02_003D77B8(*(u8 **)(slots + *(s32 *)(state + 0x18C) * 4)) != 0) {
        switch (*(s16 *)(other + 0xAA)) {
        case 0xD98:
            *(s32 *)(state + 0x100) += 1;
            weight = 1.0f;
            break;
        case 0xDCF:
            *(s32 *)(state + 0x104) += 1;
            weight = 1.0f;
            break;
        case 0xDF4:
            *(s32 *)(state + 0x108) += 1;
            weight = 1.0f;
            break;
        case 0xDF7:
            *(s32 *)(state + 0x10C) += 1;
            weight = 1.0f;
            break;
        case 0xDF9:
            if (func_L02_003D77F8(*(u8 **)(slots + *(s32 *)(state + 0x18C) * 4)) != 0)
                return 0;
            *(s32 *)(state + 0x110) += 1;
            weight = 1.0f;
            break;
        case 0xD37:
            *(s32 *)(state + 0x114) += 1;
            weight = 1.0f;
            break;
        default:
            goto add;
        }
        *(f32 *)(*(u8 **)(other + 0x68) + 0x20) = weight;
    add:
        func_L02_003D7868(*(u8 **)(state + *(s32 *)(state + 0x18C) * 4 + 0x120), other);
        return 1;
    }
    return 0;
}
