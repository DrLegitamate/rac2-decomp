/* func_00297670 - 192 bytes, 28 places (the boot and every level), retail at
   0x00297670: the resident table's slot lookup: it reads the table at
   0x1C4FA0, asks the engine for the table's count (through $gp) and keeps
   the slot's counter at the table at 0x1A79F0 up to date.

   Historical near-miss measurement: 208 bytes against 192. Current USA v1.01
   probe on 29 October 2026, using the retained source as a standalone -G8
   unit: 212 bytes and 0/28 placements. The current diff confirms that cc1
   saves $s2 and uses it for the count, where retail has no $s2 save and keeps
   the count in $s0. It also delays the first table-base calculation until
   after the saves, unlike retail's `addiu $s1,$v1,0` in the prologue. The
   older note that the first fifteen instructions match does not describe this
   current probe.

   What is measured:

   - The two guards and the engine's call are right.  The retail's
     `beqz $v0` (the table's field at +0x10) jumps straight to the
     epilogue, with the copy of the argument in the branch's delay slot; this
     attempt branches around a block that sets the return value to zero
     first.

   - The two globals that stand for one address (0x1A79F0) are read in two
     forms: the retail reads it through $gp (`lw $a0,-0x7600($gp)`) once
     and absolutely (`lui $a0,0x1A ; lw $a0,0x79F0($a0)`) once.  Two names
     for the address - one `sda`, one `nosda` - give both forms in a `-G8`
     unit, and the unit needs `-G8` because of the $gp access.

   - The count has to be read before the second guard, so that the retail's
     `daddu $s0,$v0,$zero` (the copy in the call's delay slot) can keep it
     in a callee-saved register; reading it again after the calls gives
     this cc1's reload instead.

   - The order of the two loads that set up the last call's third and
     fourth arguments differs (the retail loads the fourth first).

   - The final comparison is the retail's `slt $v0,$v0,$s0` followed by
     `bnel $v0,$zero` with the store in the delay slot: the "then" block
     goes into the delay slot and the branch jumps over it, so the
     comparison's result is materialised and tested against zero.

   What was tried: the count read before and after the calls, the two
   arguments of the last call swapped, the comparison written as a variable
   and as an expression, and the flags `-mno-split-addresses`,
   `-fno-schedule-insns`, `-fno-schedule-insns2`, `-fno-gcse` and
   `-fno-strength-reduce`.

   The C below needs the `-G8` profile (the store to the count table goes
   through $gp) and the two names for 0x1A79F0: config/cflags.txt must give
   its unit "-O2 -G8 -ffunction-sections", and the unit must hold no other
   body.  */

#include "include_asm.h"

/* The two names stand for the same address: the table's own count is read
   through $gp, the absolute form is used once. */
extern int *D_001A79F0_3 __attribute__((sda));

extern int *D_001A79F0_4 __attribute__((nosda));

extern int D_001C4FA0[];

extern char D_001399B8[];

extern int func_282A60(int, int, int);

extern int func_283EF0(int, int, int, int);

extern int func_297BB0(int);

extern int func_294E48(int);

/* The table's slot for the given index, with the count the engine keeps. */
int func_00297670(int index)
{
    int *table = D_001C4FA0;
    int *entry;
    int count;
    int less;

    if (table[4] == 0)
        return table[4];
    if (table[10] == 0)
        return func_282A60(index, 0, 0x800);
    count = table[142];
    if (count < 0)
        return func_282A60(index, 0, 0x800);
    func_294E48(D_001A79F0_3);
    func_283EF0(index, 0x800, table[5], table[3]);
    if (count != -1) {
        func_297BB0(index);
        entry = (int *)((char *)D_001399B8 + D_001A79F0_4[0] * 4);
        less = *entry < count;
        if (less)
            *entry = count;
        return less;
    }
    return 0;
}
