/* 28 October 2026: superseded by src/levels/20_yeedil/L20_00443A10-g8.c,
 * locally exact in US, US2 and PAL. The typed 128-byte heading record view,
 * updating the existing heading variable and loading the final table pointer
 * before the output stores close the historical residuals below. Actual
 * float helper return banks were verified; strict linked qualification is
 * pending with the maintainer.
 */

/* func_L20_00443A10 (332 bytes, level 20): near miss - the SIZE is exact and only three
 * register allocations differ.
 *
 * WHAT CHANGED SINCE THE WAVE-3 NOTE (worker 03, wave 4):
 *  - The unit is a -G8 sibling of its own, src/levels/20_yeedil/L20_00443A10-g8.c, and the
 *    flags are `-O2 -G8 -ffunction-sections` - WITHOUT -mno-split-addresses.  The wave-3
 *    note said the unit needed -mno-split-addresses; it does not: with the flag the
 *    address of the boot table D_189E20 comes out as one `la` (lui+addiu adjacent) where
 *    the retail separates the two around the `sd $s0,0($sp)`.  Without the flag the split
 *    form is right.
 *  - The level table D_L20_001B308C needs the absolute form with the base in the same
 *    register as the destination (`lui $v1,%hi(D); lw $v1,%lo($v1)($v1)`), and that comes
 *    from the PLAIN declaration in a -G8 unit (the wave-3 note used `nosda`, which in a -G8
 *    unit materialises the address in a register of its own and grows the frame to 0x40).
 *    D_L20_001B308C is at gp+0x409C, too far for the $gp form.
 *  - The blend is NOT `c = func_00283BE0(a, b); if (0.0f < c) ...`: the retail copies the
 *    blend's result into a separate variable (the comparison uses the raw $f0), and the
 *    candidate now has the retail's 83 instructions in the blend area.
 *
 * The candidate (in its own -G8 unit, -O2 -G8 -ffunction-sections):
 *
#include "include_asm.h"

typedef float f32;

extern float D_189E20[];

extern char *D_L20_001B308C;

extern float D_L20_001B2098 __attribute__((sda));

extern float func_00283248(float, float);

extern float func_00283BE0(float, float);

extern float func_00283B98(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_00282CC0(char *, char *, char *);

void func_L20_00443A10(char *arg0, char *arg1) {
    char *s0 = arg0;
    char *s1 = arg1;
    char *state = *(char **)(s0 + 0x68);
    float *v = (float *)D_189E20;
    float a, b, c, d;
    int idx;

    a = func_00283248(v[0x20] - *(float *)(s0 + 0x10),
                      v[0x21] - *(float *)(s0 + 0x14));
    idx = *(int *)(state + 0x230);
    b = func_00283248(
        *(float *)((char *)D_L20_001B308C + (idx << 7) + 0x30) -
            *(float *)(s0 + 0x10),
        *(float *)((char *)D_L20_001B308C + (idx << 7) + 0x34) -
            *(float *)(s0 + 0x14));
    if (0.0f < func_00283BE0(a, b)) {
        d = func_00283BE0(b, 1.5707964f);
    } else {
        d = func_00283B98(b, 1.5707964f);
    }
    *(float *)s1 = func_00283180(d) * D_L20_001B2098;
    *(float *)(s1 + 4) = func_00283198(d) * D_L20_001B2098;
    *(int *)(s1 + 8) = 0;
    func_00282CC0(s1, s1, (char *)((char *)D_L20_001B308C +
                                   (*(int *)(state + 0x230) << 7) + 0x30));
}

 *
 * The three residues, all of them a register allocation:
 *  1. The table index and the table base: the retail keeps the index in $v0 and the base in
 *     $v1 (`lw $v0,0x230($s2)` / `lui $v1,%hi(D_1B308C)`), this cc1 the other way round
 *     ($v1 for the index, $v0 for the base).  Four instructions.
 *  2. The result of the second blend: the retail keeps it in $f21 (the register of `b`,
 *     which dies at the branch's argument setup), this cc1 in $f20 (the register of `a`).
 *     Four instructions (the two `mov.s $f2x,$f0` and the two `mov.s $f12,$f2x`).
 *  3. The tail: the retail loads the base of the last call's third argument early (before
 *     the `daddu $a1` and the `mul.s`) and stores the zero at 0x8 after the `mul.s`, this
 *     cc1 loads the base late and stores the zero first.  Six instructions, the same
 *     instructions in a different order.
 *
 * Measured and NOT enough for the residues: the index read into a named variable (with
 * and without the shift at the assignment), the four ways of declaring the four float
 * variables, the blend's result in a variable of its own, the blend's result compared as
 * the call's own expression, the branch's result in a variable of its own, the state
 * pointer read through the argument, the table base through a named variable.
 */
