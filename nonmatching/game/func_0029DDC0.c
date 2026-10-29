/* func_0029DDC0 - current-master recheck, 28 October 2026: 104 bytes vs 120,
 * 0/28 USA v1.01 placements. Both resident byte symbols and the cross-program
 * halfword target are `nosda`, as retail uses absolute addressing. The checker
 * does not align the restructured stores with the target's retail relocation,
 * so their displayed candidate high halves are unresolved. The compiler
 * removes each `& 0xFF` after a byte
 * load, reshaping the retail branches and shortening the function by 16 bytes.
 * The original blocker measurements below are retained as history.
 *
 * The retail body (boot 0x0029DDC0, 120 bytes; the same code is in the 27 levels):
 *
 *   lui   $v0,0x1A ; lbu $v0,0x7BD5($v0)      ; g1 = the byte at 0x001A7BD5
 *   lui   $v1,0x1A ; lbu $v1,0x7B08($v1)      ; g2 = the byte at 0x001A7B08
 *   bnez  $v0, L1
 *     daddu $a0,$v0,$zero                    ; a copy of g1
 *   bnel  $v1,$zero, L3
 *     andi  $v0,$a0,0xFF                    ; the mask of the copy
 *   addiu $v0,$zero,0x28 ; lui $v1,%hi(S) ; sh $v0,%lo(S)($v1) ; jr $ra ; return 0
 *   L1: andi  $v0,$a0,0xFF
 *       beqz  $v0, L4
 *         andi  $v0,$v1,0xFF
 *       bnez  $v0, L5
 *       addiu $v0,$zero,0x29 ; lui $v1,%hi(S) ; sh $v0,%lo(S)($v1) ; jr $ra ; return 1
 *       ...
 *
 * The control flow is recovered (the byte at 0x001A7BD5 and the byte at 0x001A7B08
 * decide between storing 0x28, 0x29 and returning 0, 1 or 2), but the retail keeps
 * three `andi ...,0xFF` masks on byte values and a branch on the masked value that
 * this compiler folds away: it removes the mask whenever the value's range is
 * 0..255, which every spelling of a byte load has.
 *
 * Measured (work/cc.sh, the default profile and -O0/-O1 alike): the mask never
 * survives.  Fourteen spellings were measured:
 *   int a = *(unsigned char *)X; a &= 0xFF;
 *   int a = *(unsigned char *)X; int b = a; b &= 0xFF;   (and the unsigned int,
 *   unsigned short, long, signed char, volatile and pointer variants)
 *   int a = *(signed char *)X; a &= 0xFF;                (this target loads even a
 *   signed char with `lbu`, so the range is 0..255 as well)
 *   int a = *(unsigned char *)X; a = (unsigned char)a;
 *   int a = *(unsigned char *)X; a = a | 0; a &= 0xFF;
 *   int a = *(unsigned char *)X; a = a & 0x00FF;
 * Every one of them compiles to the `lbu` alone: the mask is gone before the
 * instruction selection, at -O0 as well, so the fold is in the front end.
 *
 * The retail's compiler does not fold it: the boot holds 205 `andi ...,0xFF`
 * instructions (work/andicount.py) and about 60 of them mask a byte load
 * (work/andifuncs.py follows the register back through the copies).  The 41
 * matched boot functions that do have an `andi 0xFF` all mask a value of unknown
 * range - an argument, a call's result - which this compiler reproduces; none
 * masks a byte value, and none could, since a body that needed the mask could
 * not have matched.  So the difference was never measured.
 *
 * What would unblock it: a compiler change that stops the front end from
 * removing a mask that covers the whole range of a narrower-typed operand (the
 * retail keeps the mask on an `int` whose value happens to come from a byte).
 *
 * The address of the halfword that is stored (0x00257A32 in the boot, 0x00280472
 * in level 00) differs from program to program, so it is named ref_L00_0030EE40_00.
 */
extern unsigned short ref_L00_0030EE40_00 __attribute__((nosda));
extern unsigned char D_001A7BD5 __attribute__((nosda));
extern unsigned char D_001A7B08 __attribute__((nosda));

int func_0029DDC0(void)
{
    int g1 = D_001A7BD5;
    int g2 = D_001A7B08;
    int a = g1;

    if (g1 != 0) {
        a &= 0xFF;
        if (a == 0) {
            ref_L00_0030EE40_00 = 0x29;
            return 2;
        }
        if (g2 != 0)
            return 0;
        ref_L00_0030EE40_00 = 0x29;
        return 1;
    }
    if (g2 != 0)
        return 0;
    ref_L00_0030EE40_00 = 0x28;
    return 0;
}
