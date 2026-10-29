/* func_00298298 - 29 October 2026 standalone USA v1.01 replay: 216/232 bytes,
   0/28. The output retains the source's state transitions but differs from
   retail in register allocation, branch-likely layout and loop-head delay
   slot constants.
   Near miss: the boot place (and all 27 level
   places) differ in the register allocation and in two dead constants.

   The retail body (0x298298, 232 bytes):

     0x298298  lui   $a1, 0x1A
     0x29829c  lw    $a1, 0x7424($a1)      ; flags = D_001A7424
     0x2982a0  lui   $v1, 0x14
     0x2982a4  addiu $v0, $zero, -0x5
     0x2982a8  addiu $a0, $zero, -0x3
     0x2982ac  addiu $a2, $v1, -0x6C20     ; state = &D_001393E0
     0x2982b0  and   $v0, $a1, $v0         ; v0 = flags & ~4
     0x2982b4  and   $a0, $v0, $a0         ; a0 = (flags & ~4) & ~2
     0x2982b8  lw    $v1, 0x17C($a2)       ; state->field17c
     0x2982bc  bnez  $v1, 0x2982d0
     0x2982c0  sw    $a0, -0x7BCC($gp)     ; D_001A7434 = mask
     0x2982c4  addiu $v0, $zero, 3
     0x2982c8  jr    $ra
     0x2982cc  sw    $v0, -0x7BD0($gp)     ; D_001A7420 = 3
     0x2982d0  andi  $v0, $a1, 0x80        ; loop head
     0x2982d4  bnez  $v0, 0x2982e8
     0x2982d8  addiu $v0, $zero, -0x81     ; dead ~0x80, delay slot
     0x2982dc  lw    $v0, 0x16C($a2)       ; state->field16c
     0x2982e0  beqz  $v0, 0x298304
     0x2982e4  addiu $v0, $zero, -0x81     ; dead ~0x80, delay slot
     0x2982e8  addiu $v1, $zero, 0x15      ; state 21
     0x2982ec  and   $v0, $a0, $v1         ; mask & 21
     0x2982f0  lui   $at, 0x1A
     0x2982f4  sw    $v1, 0x7420($at)      ; D_001A7420 = 21
     0x2982f8  ori   $v0, $v0, 0x40
     0x2982fc  jr    $ra
     0x298300  sw    $v0, -0x7BCC($gp)     ; D_001A7434
     0x298304  andi  $v0, $a1, 0x100
     0x298308  beql  $v0, $zero, 0x29832c
     0x29830c  lw    $v0, 0x10($a2)        ; state->field10, annulled if taken
     0x298310  xori  $v0, $a0, 0x100
     0x298314  addiu $v1, $zero, 0x14      ; state 20
     0x298318  ori   $v0, $v0, 0x40
     0x29831c  lui   $at, 0x1A
     0x298320  sw    $v1, 0x7420($at)
     0x298324  jr    $ra
     0x298328  sw    $v0, -0x7BCC($gp)
     0x29832c  beqz  $v0, 0x298358
     0x298330  lw    $v1, -0x6368($gp)     ; D_001A8C88
     0x298334  bnez  $v1, 0x2982d0         ; loop back
     0x298338  sw    $zero, 0x17C($a2)
     0x29833c  lui   $v0, 0x1B
     0x298340  lw    $v0, -0x7374($v0)     ; D_0018C8C
     0x298344  bnez  $v0, 0x2982d0         ; loop back
     0x298348  addiu $v0, $zero, 3
     0x29834c  ori   $v0, $a0, 1           ; mask | 1
     0x298350  b     0x298368
     0x298354  addiu $v1, $zero, 2        ; state 2
     0x298358  andi  $v0, $a1, 0x200
     0x29835c  beqz  $v0, 0x298378
     0x298360  xori  $v0, $a0, 0x200
     0x298364  addiu $v1, $zero, 0x19      ; state 25
     0x298368  lui   $at, 0x1A
     0x29836c  sw    $v0, 0x7424($at)      ; D_001A7424
     0x298370  lui   $at, 0x1A
     0x298374  sw    $v1, 0x7420($at)      ; D_001A7420
     0x298378  jr    $ra
     0x29837c  nop

   What this draft reproduces: the whole control flow, both `||` short-circuit
   tests, the two mask statements (`flags & ~4` then `& ~2`, which must be two
   separate statements or the compiler folds them into one AND), the state
   numbers 21 / 20 / 25 / 2 / 3, the loop back edges and the tail that writes
   D_001A7424 and D_001A7420.

   What still differs:

   1. The two dead `addiu $v0,$zero,-0x81` (the constant ~0x80) in the delay
      slots of the two branches at the loop head.  The retail's compiler had the
      constant in a register and the delay-slot filler copied it into both
      slots; this cc1 never materialises it, because the source spelling that
      leaves such a constant behind is not known.  Measured: `(flags & ~0x80)
      != flags` materialises the constant but compiles to `and`/`bne` instead of
      `andi`/`bnez`, `(flags & ~0x80) == flags` is folded to `andi` but drops the
      constant, and `!(flags & ~0x80) == flags` keeps the constant but is not
      folded either.
   2. The register allocation: the retail keeps the flags in $a1, the
      intermediate `flags & ~4` in $v0, the mask in $a0 and the address of
      D_001393E0 in $a2, and it materialises the two mask constants *before*
      that address; this draft keeps the flags in $a2, the intermediate and the
      mask in $a0 and the address in $v1.
   3. The merge of the "state 21" and "state 20" tails, which this cc1
      cross-jumps into one block where the retail keeps them apart, and the
      plain `beqz` where the retail uses the branch-likely `beql` with the
      load of `state->field10` in the (annulled) delay slot.

   What would unblock it: the source spelling of the loop head's first test
   (see 1), and a spelling of the two mask statements that keeps the constant
   ~0x80 alive inside the loop.  Everything else in the body is reproduced. */

extern int D_001A7424[] __attribute__((sda));
extern int D_001A7420[] __attribute__((sda));
extern int D_001A7434[] __attribute__((sda));
extern int D_001A8C88[] __attribute__((sda));
extern int D_0018C8C __attribute__((sda));

typedef struct {
    char reserved00[0x10];
    int field10;
    char reserved14[0x150];
    int field164;
    int field168;
    int field16c;
    char reserved170[0xc];
    int field17c;
} SharedState;

extern SharedState D_001393E0;

void func_00298298(void)
{
    int flags = D_001A7424[0];
    int cleared = flags & ~4;
    int mask = cleared & ~2;
    int v0, v1;

    if (D_001393E0.field17c == 0) {
        D_001A7434[0] = mask;
        D_001A7420[0] = 3;
        return;
    }
loop:
    if ((flags & 0x80) || D_001393E0.field16c != 0) {
        int v = mask & 21;
        D_001A7420[0] = 21;
        D_001A7434[0] = v | 0x40;
        return;
    }
    if (flags & 0x100) {
        int w = (mask ^ 0x100) | 0x40;
        D_001A7420[0] = 20;
        D_001A7434[0] = w;
        return;
    }
    if (D_001393E0.field10 != 0) {
        if (D_001A8C88[0] != 0)
            goto loop;
        D_001393E0.field17c = 0;
        if (D_0018C8C != 0)
            goto loop;
        v0 = mask | 1;
        v1 = 2;
    } else if (flags & 0x200) {
        v0 = mask ^ 0x200;
        v1 = 25;
    } else {
        return;
    }
    D_001A7424[0] = v0;
    D_001A7420[0] = v1;
}
