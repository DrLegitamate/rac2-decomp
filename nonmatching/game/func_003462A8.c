#include "include_asm.h"

/* Near miss for func_003462A8 (boot 0x003462A8, level 00 0x0043BBD8, 27 levels).
 *
 * The third of the family that fills func_00337210's 23-word descriptor
 * (func_00344F98 in src/game/00344848.c is the template, and its siblings
 * func_003464D0 and func_003463C8 now match in src/game/00345358-g8.c).
 *
 * Retail body (boot):
 *   addiu $sp, $sp, -0xB0            the frame is 0xB0, six saved registers
 *   addiu $a0, $sp, 0x10             the descriptor sits at sp+0x10
 *   lui   $v1, 0x1B
 *   addiu $t1, $v1, -0x1F50          0x1AE0B0, the eight bytes copied
 *   ldl   $a2, 0x7($t1)              the copy is a plain 8-byte struct copy
 *   ldr   $a2, 0x0($t1)              (ldl/ldr/sdl/sdr, not ld/sd)
 *   sdl   $a2, 0x7($sp)              into the local at sp+0x00
 *   sdr   $a2, 0x0($sp)
 *   ...
 *   sw    $s4, 0x54($a0)             f[21] = 1, a dead store retail keeps
 *   ...
 *   sw    $a1, 0x64($sp)             f[21] = the mode test
 *   sw    $zero, 0x60($sp)           f[20] = 0, a dead store retail keeps
 *   sw    $sp, 0x60($sp)             f[20] = the address of the local at sp+0x00
 *   sw    $s4, 0x68($sp)             f[22] = 1, in the call's delay slot
 *
 * What this candidate gets wrong:
 *   - The original initializer compiled to 296 bytes against retail's 288:
 *     the eight-byte copy kept its value in a callee-saved register ($s5/$s6)
 *     where retail uses $a2, so the frame was 0xC0 and $s6/$s7 were saved as
 *     well. Moving the copy to just before f[20] is assigned shortened its
 *     lifetime and measured 276 bytes, 0/28; the frame fell to 0xA0 and the
 *     remaining saved-register and descriptor-store order still differ.
 *     Loading through an explicit pointer did not improve that result. The
 *     original initializer with -mno-split-addresses gives `lui $at` +
 *     `ldl`/`ldr` through $at, while retail uses `lui $v1` + `addiu $t1` +
 *     `ldl`/`ldr` through $t1.
 *   - Making the descriptor array volatile and casting it to the helper's
 *     existing `int *` interface measured 252 bytes, 0/28, with a 0x80 frame;
 *     it does not reproduce retail's allocation or store order.
 *   - the two dead stores retail keeps (f[21] = 1 through the descriptor
 *     pointer $a0, and f[20] = 0 before f[20] = &local) are removed by this
 *     cc1, because it can see that both words are written again.
 *   - the store order of the remaining words matches the retail order, the
 *     23 slots are the right ones, and the source order that produced it is
 *     the one the two matched siblings use.
 *
 * The data the descriptor points at (boot addresses): f[0] = 0x259CE0,
 * f[1] = 0x1AE440, f[2] = 0x1AE444, f[5] = 0x1AE448, f[6] = 0x1AE450,
 * f[7] = 0x1AE458, f[8] = 0x1AE460, f[9] = 0x1AE468, the eight bytes at
 * 0x1AE0B0.
 */
typedef struct { unsigned int lo; unsigned int hi; } Word2_462A8;

extern void func_00337210(int *);

extern char D_00259CE0[];

extern Word2_462A8 D_001AE0B0 __attribute__((nosda));

extern int D_001AE440 __attribute__((sda));

extern int D_001AE444 __attribute__((sda));

extern int D_001AE448 __attribute__((sda));

extern int D_001AE450 __attribute__((sda));

extern int D_001AE458 __attribute__((sda));

extern int D_001AE460 __attribute__((sda));

extern int D_001AE468 __attribute__((sda));

void func_003462A8(char *o)
{
    Word2_462A8 q;
    int f[23];

    f[20] = 0;
    f[21] = 1;
    f[19] = *(int *)(o + 0x494);
    f[21] = (*(int *)(o + 0x498) == 0);
    f[3] = *(int *)(o + 0x48C);
    f[4] = *(int *)(o + 0x490);
    f[16] = (int)(o + 0x448);
    f[9] = (int)&D_001AE468;
    f[1] = D_001AE440;
    f[2] = D_001AE444;
    f[0] = (int)D_00259CE0;
    f[17] = (int)(o + 0x210);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x258);
    f[18] = *(int *)(o + 0x400);
    f[8] = (int)&D_001AE460;
    f[7] = (int)&D_001AE458;
    f[6] = (int)&D_001AE450;
    f[5] = (int)&D_001AE448;
    f[14] = 0;
    f[11] = 0;
    f[13] = 0;
    q = D_001AE0B0;
    f[20] = (int)&q;
    f[22] = 1;
    func_00337210(f);
}
