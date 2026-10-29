/* OF2 (2026-10-26): 172 of 172 bytes in a -frac2-qcopy unit ("-O2 -G0 -ffunction-sections
   -frac2-qcopy", src/game/00305438-qcopy.c): retail's two copies both go through $v0 with
   the addresses in registers ($a1 = &e->b as its own giv, $a3 = &local hoisted), which is
   the qcopy form, not a compiled TI move. With the indexed loop below (fill and return
   inside), everything matches except the loop entry: retail enters with `b` to the
   rotated test (the first `i < 100` is evaluated), ours has the exit test duplicated by
   jump.c and folded (0 < 100), so the body comes first and the test sits at the bottom.
   Pointer walks, && tests and int-cast compares were worse. A separate explicit
   goto test with distinct table/write cursors grew to 188 bytes and a 0x50-byte
   frame (0/28); the indexed qcopy candidate remains better. What stops retail's
   duplicate_loop_exit_test is the open question.

   29 October 2026: an alternate qcopy-profile goto loop with an entry jump to
   the test, a backward jump to the body, and separate `entry`/`payload`
   pointers compiled to 196 bytes and 0/28 USA v1.01 placements. The compiler
   preserved the entry jump but allocated a 0x30-byte frame, saved six
   registers, and retained both pointer increments and an indexed counter.
   This is worse than the retained 172-byte candidate and does not recover the
   retail's rotated test and register allocation. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 a; TI128 b; float f20; void *owner; int pad28, pad2C; } Slot;
extern void func_0029FCC0(void *a, int b, void *c);
extern Slot ref_00305438_00[];
void func_00305438(void *obj, void *other)
{
    char *s0 = *(char **)((char *)obj + 0x68);
    TI128 local;
    int i;
    func_0029FCC0(obj, 1, &local);
    for (i = 0; i < 100; i++) {
        Slot *e = &ref_00305438_00[i];
        if (e->owner == 0) {
            *(int *)(s0 + 0x64) += 1;
            e->owner = obj;
            e->f20 = 120.0f;
            e->b = *(TI128 *)other;
            e->a = local;
            return;
        }
    }
}

#if 0
/* func_00305438 - 172 bytes, 28 places (the boot and every level), retail at
   0x00305438: addiu $sp,$sp,-0x30 ; sd $s1,0x18($sp) ; daddu $a2,$sp,$zero ;
   sd $s2,0x20($sp) ; daddu $s1,$a0,$zero ; sd $ra,0x28($sp) ; daddu $s2,$a1,$zero ;
   sd $s0,0x10($sp) ; addiu $a1,$zero,0x1 ; jal func_29FCC0 ; lw $s0,0x68($s1) ;
   lui $v0,0x22 ; lui $at,0x42F0 ; mtc1 $at,$f0 ; addiu $v0,$v0,0x6AE0 ;
   daddu $a3,$sp,$zero ; daddu $v1,$v0,$zero ; addiu $a1,$v0,0x10 ;
   b +0xC ; addiu $a2,$v1,0x12C0 ; addiu $v1,$a0,0x30 ; addiu $a1,$a1,0x30 ;
   slt $v0,$v1,$a2 ; beql $v0,$zero,+0x38 ; ld $s0,0x10($sp) ; lw $v0,0x24($v1) ;
   bnez $v0,-0x1C ; daddu $a0,$v1,$zero ; lw $v0,0x64($s0) ; addiu $v0,$v0,0x1 ;
   sw $v0,0x64($s0) ; sw $s1,0x24($v1) ; swc1 $f0,0x20($v1) ; lq $v0,0x0($s2) ;
   sq $v0,0x0($a1) ; lq $v0,0x0($a3) ; sq $v0,0x0($v1) ; ld $s0,0x10($sp) ;
   ld $s1,0x18($sp) ; ld $s2,0x20($sp) ; ld $ra,0x28($sp) ; jr $ra ;
   addiu $sp,$sp,0x30.

   Measured near miss: 160 of 172 bytes with the default profile
   ("-O2 -G0 -ffunction-sections").  The frame, the call to func_29FCC0 with
   its arguments, the constant 120.0f (0x42F00000), the table, the loop's test,
   the counter, the two 16-byte copies and the epilogue all match.

   What is left is the loop's shape and three instructions with it:

   1. The retail's loop is rotated so that both increments stand before the
      test (`addiu $v1,$a0,0x30 ; addiu $a1,$a1,0x30 ; slt ; beql ; lw ;
      bnez ; daddu $a0,$v1,$zero`), the entry branch skipping them.  This cc1
      splits the two increments around the test
      (`addiu $a0,$a0,0x30 ; slt ; beqz ; lw ; bnel ; addiu $v1,$v1,0x30`) and
      keeps the increment of the first pointer in the branch's delay slot.  The
      source was written both ways (the increments in either order, with
      `+=` and with an explicit cast); the shape does not change.

   2. The retail compares the table pointer with a *signed* 32-bit test
      (`slt $v0,$v1,$a2`), so the source compares `(int)v1 < (int)limit`; a
      pointer comparison gives this cc1's `sltu`, and a `long` comparison
      costs the sign-extension pairs (`dsll32`/`dsra32`) this cc1 emits for
      every long-to-pointer conversion.

   3. The retail keeps a copy of the table symbol in `$v1`
      (`daddu $v1,$v0,$zero`), the address of the 16-byte local in `$a3`
      (`daddu $a3,$sp,$zero`) and reloads `$s0` in the delay slot of the
      branch (`ld $s0,0x10($sp)`); this candidate has none of the three.

   The table is at 0x00226AE0 in the boot (the retail's `lui $v0,0x22 ;
   addiu $v0,$v0,0x6AE0`), which is in the memory a level replaces, so the
   name is `ref_00305438_00` and its value is read from the retail bytes at
   each place.  The table's entries are 0x30 bytes apart and the free one is
   found by the field at +0x24; the second pointer walks the same table at
   +0x10. */

#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_29FCC0(void *a, int b, void *c);

/* The table the free entry is looked for in; its value differs from program
   to program. */
extern char ref_00305438_00[];

/* Looks for a free entry in the table, fills it with the owner's data and
   counts the owners. */
void func_00305438(void *obj, void *other)
{
    void *s1 = obj;
    void *s2 = other;
    void *s0 = *(void **)((char *)obj + 0x68);
    TI128 local;
    int *v1;
    int *p;
    int *limit;

    func_29FCC0(obj, 1, &local);
    v1 = (int *)ref_00305438_00;
    p = (int *)((char *)v1 + 0x10);
    limit = (int *)((char *)v1 + 0x12C0);
    while ((int)v1 < (int)limit && *(int *)((char *)v1 + 0x24) != 0) {
        v1 = (int *)((char *)v1 + 0x30);
        p = (int *)((char *)p + 0x30);
    }
    *(int *)((char *)v1 + 0x24) = s1;
    *(float *)((char *)v1 + 0x20) = 120.0f;
    *(TI128 *)v1 = local;
    *(TI128 *)p = *(TI128 *)s2;
    *(int *)((char *)s0 + 0x64) += 1;
}

#endif
