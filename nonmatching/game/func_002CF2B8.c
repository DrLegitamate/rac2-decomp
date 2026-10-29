#include "common.h"

/* Near miss: a corrected 32-bit style argument gives 132 bytes against
 * retail's 136, 0/28 USA v1.01 placements. The first mismatches include the
 * swapped float constant registers and the call argument setup schedule.
 *
 * Retail keeps the 256.0f in `$f2` and the 0.5f in `$f1`
 * (`mtc1 $at,$f2` ; `mtc1 $at,$f1`), this cc1 keeps them the other way
 * round (`$f1` and `$f2`); the order of the two constants in the source does
 * not change it.
 *
 * Retail's style is one 32-bit argument in `$a2`; the matched callee declares
 * it as `unsigned long`, which is 32 bits in this target. With `u32`, cc1
 * places the text pointer in `$a3`, the style in `$a2` and the computed y in
 * `$a1`, but schedules the x constant in the `jal` delay slot. Retail sets up
 * x before the call. A prior 64-bit `u64` prototype was incorrect.
 *
 * The float is read from a per-program address (0x001B23A4 in the boot,
 * 0x001B2704 in level 00), so it is a `ref_` symbol; with `-G8` the load is
 * the symbolic `l.s $f0,sym` that retail's `lui $at`+`lwc1` pair comes from,
 * and with `-G0` the address is materialised in `$v0` instead.
 *
 * The unit needs `-G8` for the symbolic load.
 *
 * A separate `scaled = 256.0f * ref; s0 = (s32)(scaled + 0.5f);` local in an
 * isolated `-G8` unit leaves the output unchanged at 132/136, 0/28; the two
 * constants stay swapped and the call-argument schedule still differs.
 *
 * A 29 October isolated `-O2 -G8 -ffunction-sections -fno-schedule-insns`
 * unit also remains 132/136 bytes and 0/28. It retains the `$f1`/`$f2`
 * swap, the expanded style constant and the x constant in the call delay
 * slot; this scheduling flag does not improve the match.
 *
 * Isolated `-fno-gcse` and `-ffast-math` probes on 29 October remain
 * byte-identical at 132/136 and 0/28. An isolated `-fno-schedule-insns2`
 * probe also stays 132/136 and 0/28; it moves the per-program float load
 * before the 256.0f constant and changes the call setup order, but the
 * constants remain assigned to the opposite FPRs from retail. These flags
 * do not recover a match.
 */

extern void func_0027C540(long);

extern void func_0027C660(void);

extern void func_L00_0030D608(void);

extern s32 func_00288FB8(s32);

extern s32 func_0027FAA8(s32, s32, u32, s32, s32);

extern float ref_L00_002CF2B8_01;

int func_002CF2B8(void)
{
    s32 s0;

    func_0027C540(0);
    func_L00_0030D608();
    s0 = (s32)(0.5f + 256.0f * ref_L00_002CF2B8_01);
    func_0027FAA8(0x1A5, s0, 0x80F0F0F0u, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
