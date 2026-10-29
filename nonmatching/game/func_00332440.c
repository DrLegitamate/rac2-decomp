/* func_00332440 - near miss (328 bytes against the retail's 324).
 *
 * The body is decoded and the instruction sequence is nearly the retail's; what is
 * left is the register allocation of the six values that live across the calls.
 *
 * The retail keeps:   $s0 = a1        $s1 = a2        $s2 = sp+0x10
 *                     $s3 = state     $s4 = object    $s5 = a0
 * and it REUSES $s0 and $s1 for object+0xD0 and object+0xC0 once a1 and a2 are dead
 * (`addiu $s0,$s4,0xD0` and `addiu $s1,$s4,0xC0`).
 *
 * This source keeps seven values alive instead of six (it needs $s6), so its
 * prologue saves one register too many and its parameter copies are made in the
 * order a2, a1, a0 where the retail makes them in the order a1, a2, a0.  The
 * remaining difference is that one instruction (4 bytes).
 *
 * What was tried: the source shape above, with the two 16-byte locals at sp+0x00
 * and sp+0x10 (the retail's `lq`/`sq` copies go through a register with a zero
 * displacement, which plain `mode(TI)` assignments give - no -frac2-qcopy needed),
 * the call arguments prepared as the retail does, and the three 0.0f stores before
 * the last call.
 *
 * What would unblock it: the source order that makes this cc1 copy the parameters
 * in the order a1, a2, a0 and reuse $s0/$s1 for the two derived pointers.
 * A 28 Oct trial introduced locals for a1, a2 and a0 in that order; it remained
 * 328/324 bytes, 0/28, with the same extra saved-register pressure.
 */

typedef int TI128 __attribute__((mode(TI)));

typedef float f32;

extern int func_002FED90(void *, int, f32, f32, f32);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_002AFFD8(void *, void *, int);
extern int func_0029EFD0(int);

void *func_00332440(void *a0, void *a1, void *a2)
{
    TI128 localA;
    TI128 localB;
    void *object;
    void *state;
    int result;

    func_002AFFD8(a1, &localA, 1);
    object = (void *)func_0029EFD0(0xEAA);
    if (object == 0)
        return 0;
    state = *(void **)((char *)object + 0x68);
    *(int *)((char *)state + 0x10) = 0x50;
    *(unsigned char *)((char *)object + 0x30) = 0xFF;
    *(short *)((char *)object + 0x32) = 0xFF;
    *(unsigned char *)((char *)object + 0x20) = 0;
    localA = *(TI128 *)a1;
    *(TI128 *)state = *(TI128 *)a2;
    *(int *)((char *)state + 0x18) = 0;
    *(int *)((char *)state + 0x14) = 0;
    func_00282F20(&localB, a2, 1.0f);
    *(TI128 *)((char *)object + 0xC0) = localB;
    func_00282DD8((char *)object + 0xD0, (char *)object + 0xC0, &localA);
    func_00282F20((char *)object + 0xD0, (char *)object + 0xD0, 1.0f);
    func_00282DD8((char *)object + 0xD0, (char *)object + 0xD0, (char *)object + 0xC0);
    *(f32 *)((char *)object + 0xCC) = 0.0f;
    *(f32 *)((char *)object + 0xEC) = 0.0f;
    *(f32 *)((char *)object + 0xDC) = 0.0f;
    result = func_002FED90(object, 0, 1.0f, 1.0f, 1.0f);
    *(int *)((char *)state + 0x20) = (int)a0;
    *(int *)((char *)state + 0x1C) = result;
    return object;
}
