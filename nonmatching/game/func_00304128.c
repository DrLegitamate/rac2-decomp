/* Current-master USA v1.01 replay: 228/228 bytes, 0/28; first mismatch +0x44.
 * func_00304128 - 228 bytes, 28 places (the boot and every level), retail at
   0x00304128: addiu $sp,$sp,-0x40 ; sd $s1,0x28($sp) ; sd $ra,0x30($sp) ;
   daddu $s1,$a0,$zero ; sd $s0,0x20($sp) ; lw $s0,0x68($s1) ; lw $v0,0x4C($s0) ;
   andi $v0,$v0,0x8 ; bnel $v0,$zero,+0x2C ; ld $s0,0x20($sp) ; jal func_282948 ;
   addiu $a0,$s0,0x8C ; beqz $v0,+0x27 ; daddu $a0,$s1,$zero ; jal func_303568 ;
   daddu $a1,$sp,$zero ; addiu $s1,$sp,0x10 ; lui $v1,0x1B ; addiu $v1,$v1,-0x7430 ;
   lq $v0,0x0($v1) ; sq $v0,0x0($s1) ; lwc1 $f0,0x8($s0) ; daddu $a0,$sp,$zero ;
   lui $at,0x4080 ; mtc1 $at,$f12 ; jal func_303DA8 ; swc1 $f0,0x18($sp) ;
   lui $at,0x3F80 ; mtc1 $at,$f1 ; nop ; c.lt.s $f1,$f0 ; nop ; bc1f +0x11 ;
   lui $a3,0x80 ; lwc1 $f0,0x78($s0) ; lui $at,0x484D ; ori $at,$at,0x1400 ;
   mtc1 $at,$f12 ; daddu $a1,$s1,$zero ; lw $a2,0x80($s0) ; daddu $a0,$sp,$zero ;
   mul.s $f12,$f0,$f12 ; lw $t0,0x74($s0) ; lw $t1,0x7C($s0) ; ori $a3,$a3,0x8080 ;
   mtc1 $zero,$f13 ; daddu $t2,$zero,$zero ; lwc1 $f14,0x88($s0) ; jal func_2C7BB8 ;
   addiu $t3,$zero,0x3 ; lw $v0,0x84($s0) ; sw $v0,0x8C($s0) ; ld $s0,0x20($sp) ;
   ld $s1,0x28($sp) ; ld $ra,0x30($sp) ; jr $ra ; addiu $sp,$sp,0x40.

   Measured near miss: the candidate is the right size (228 bytes) and matches
   the prologue, the epilogue, both early exits, the branch to the vector
   helper, the float comparison (c.lt.s $f1,$f0 with the constant in $f1), the
   constant 210000.0f (0x484D1400), the fourth argument 0x00808080 and the
   store of the object's field 0x84 into its field 0x8C.  Thirteen instructions
   are still in the wrong place or use the wrong register:

   1. The 16-byte copy.  The retail reads the constant at 0x001B8BD0 into $v0
      and stores it through $s1 (the address of the second buffer):
      `lui $v1,0x1B ; addiu $v1,$v1,-0x7430 ; lq $v0,0x0($v1) ; sq $v0,0x0($s1)`.
      This compiler gives the address register $v0 and the data register $v1
      (`lui $v0,%hi ; addiu $v0,$v0,%lo ; lq $v1,0x0($v0) ; sq $v1,0x10($sp)`),
      and it stores through $sp instead of through $s1.  The retail's order -
      the data in $v0 - is what the compiler produces when the source of the
      copy is a frame slot (see the matched func_L00_003ACC88 in
      src/levels/shared/L00_003A8E28-g8.c, whose `lq $v0,0x10($sp)` reads a
      local), so the original source probably copied out of a local as well.
      Every spelling tried (a pointer variable, the symbol inline, the copy
      through a pointer to the destination, a union, a struct with a float
      member, an extra temporary) gives the same register order.

   2. The float written into the second buffer.  The retail stores it with the
      frame pointer (`swc1 $f0,0x18($sp)`), this compiler with the register
      that holds the buffer's address (`swc1 $f0,0x8($s1)`).  The same
      difference shows in the matched func_L00_003ACC88, where the retail uses
      `swc1 $f0,0x10($sp)` for a float written into a local array.

   3. The order of the argument setup of func_2C7BB8: the retail takes the
      base of the 0x00808080 constant first (`lui $a3,0x80` right after the
      branch) and finishes it (`ori $a3,$a3,0x8080`) after the two loads of
      the object's fields 0x74 and 0x7C; this compiler takes the base later
      and finishes it earlier.  The same shift moves the loads of the fields
      0x74 and 0x7C and the loads of the float 0x88 past the `mtc1 $zero,$f13`.

   A 29 October 2026 trial of both reviewed helpers, `qcopy` and `qcopy_nc`,
   preserves the same 228-byte output and 0/28 result. Both emit the desired
   `lq $v0`/`sq $v0` pair, but the destination pointer is still assigned before
   the load and the unrelated call arguments retain the same scheduling.

   What was tried: the source of the copy as a pointer variable and inline; the
   copy written as a direct assignment through pointers; the destination
      through a pointer variable; the buffer as a union and as a struct with a
      float member; the float written through a char pointer; the copy before
      and after the call to func_303568; the pointer assigned before the call
      (that makes it live across the call and moves it into $s0); the flags
      "-frac2-qcopy", "-frac2-zero-ti-barrier", "-mno-split-addresses",
      "-fno-schedule-insns", "-fno-schedule-insns2" and both at once.

   What would unblock it: a source whose copy reads out of a frame slot (so
   the data register is $v0) and whose float member is written through the
   frame pointer, or a compiler fix that gives the data of a 16-byte load the
   lower register when its source is a symbol.

   The measured values: the constant the buffer is copied from is at
   0x001B8BD0 in the boot, which is in the memory a level replaces, so the
   name is `ref_00304128_00` and its value is read from the retail bytes at
   each place; the float constants are 4.0f (0x40800000), 1.0f (0x3F800000)
   and 210000.0f (0x484D1400); the fourth argument of func_2C7BB8 is
   0x00808080 (`lui $a3,0x80 ; ori $a3,$a3,0x8080`), not 0x80808080. */

#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

extern int func_282948(void *);
extern void func_303568(void *, void *);
extern float func_303DA8(void *, float);
extern void func_2C7BB8(void *, void *, int, int, float, float, float, int, int, int, int);

/* The address the buffer is copied from; its value differs from program to program. */
extern char ref_00304128_00[];

/* Moves the object when its owner says so, and marks it when it has moved far enough. */
void func_00304128(void *obj)
{
    void *s0 = *(void **)((char *)obj + 0x68);
    TI128 buf1;
    TI128 buf2;
    float f;

    if (!(*(int *)((char *)s0 + 0x4C) & 8)) {
        if (func_282948((char *)s0 + 0x8C) != 0) {
            func_303568(obj, &buf1);
            buf2 = *(TI128 *)ref_00304128_00;
            ((float *)&buf2)[2] = *(float *)((char *)s0 + 8);
            f = func_303DA8(&buf1, 4.0f);
            if (1.0f < f)
                func_2C7BB8(&buf1, &buf2, *(int *)((char *)s0 + 0x80), 0x00808080,
                        *(float *)((char *)s0 + 0x78) * 210000.0f, 0.0f,
                        *(float *)((char *)s0 + 0x88),
                        *(int *)((char *)s0 + 0x74), *(int *)((char *)s0 + 0x7C), 0, 3);
            *(int *)((char *)s0 + 0x8C) = *(int *)((char *)s0 + 0x84);
        }
    }
}
