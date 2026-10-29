#include "common.h"

/* Near miss: current-master USA v1.01 -G8 check is 136 bytes against 140 and
 * 0/28 placements. The float computation and calls are recovered, but cc1
 * swaps the float constant registers, builds the style argument in several
 * instructions instead of retail's lui/ori pair, and schedules the x argument
 * in the jal delay slot. Reversing the add operands preserves 136 bytes; using
 * a separate scaled local grows the function to 156 bytes.
 *
 * Retail keeps the 293.0f in `$f2` and the 0.5f in `$f1`
 * (`mtc1 $at,$f2` ; `mtc1 $at,$f1`), this cc1 keeps them the other way
 * round (`$f1` and `$f2`). Both addition operand orders give the same 136-byte
 * result. Reversing the multiplication operands (`ref * 293.0f`) is also
 * byte-identical at 136/140 and 0/28. A separate scaled local is 156 bytes.
 * A 29 October isolated `-O2 -G8 -ffunction-sections -ffast-math` probe also
 * remains 136/140 and 0/28. It retains the same `$f1`/`$f2` swap, expanded
 * style constant and call-argument setup differences; fast-math does not help.
 * An isolated `-fno-schedule-insns` unit also remains 136/140 and 0/28. The
 * float-register swap and expanded style constant persist, and the call
 * argument setup and call/epilogue schedule diverge further from retail.
 * An isolated `-fno-schedule-insns2` unit also remains 136/140 and 0/28;
 * the later scheduler pass does not recover the four missing bytes.
 *
 * Retail also sets up the arguments of the `func_0027FAA8` call as `$a1`,
 * `$a3`, `$a2` and `$t0`; this cc1 sets up `$a3`, `$a2` and `$a1`.
 *
 * The float is read from a per-program address (0x001B23A4 in the boot,
 * 0x001B2704 in level 00), so it is a `ref_` symbol; with `-G8` the load is
 * the symbolic `l.s $f0,sym` that retail's `lui $at`+`lwc1` pair comes from,
 * and with `-G0` the address is materialised in `$v0` instead.
 *
 * The unit needs `-G8` for the symbolic load. The matched callee takes a
 * 32-bit target `unsigned long` style argument; do not declare it as u64.
 */

extern void func_0027C540(long);

extern void func_0027C660(void);

extern void func_L00_0030D598(void);

extern s32 func_00288FB8(s32);

extern s32 func_0027FAA8(s32, s32, u32, s32, s32);

extern float ref_L00_002CDA20_01;

int func_002CDA20(void)
{
    s32 s0;

    func_0027C540(0);
    func_L00_0030D598();
    s0 = (s32)(0.5f + 293.0f * ref_L00_002CDA20_01);
    func_0027FAA8(0x1A5, s0, 0x80F0F0F0u, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
