/* Current final accounting: 372/372 bytes; us0/21 and us2 0/21, exit1; PAL absent, exit1, not a match. Profile: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier. Full retained body was checked in its temporary unit; markers and trial profiles were restored afterward. No strict build or native-behavior claim. */

/* 25 October 2026 diagnostic follow-up; retained near miss, not linked.
 * The current paired allocator/scheduler diagnostic objects are identical to their
 * normal baseline. The last stack-snapshot argument still comes from the permanent
 * soft frame pointer, whereas the target argument is a dying pseudo. This explains
 * the measured three-move scheduling tie; no pressure override was applied.
 * Callee review:52A0 does not directly read its two scratch-pointer slots;5678 ignores its
 * fourth pointer;5828 conditionally reads the complete16-byte saved position.
 * The recorded caller slots/storage remain intact. Canonical282C88 returns void;
 * its ignored return declaration below is aligned with the current C definition.
 * Reopen on independent source-lifetime or general stack-base pressure evidence,
 * with matched controls. Repeating helper/alias/flag forms is not new evidence.
 * None of these observations establishes original-source identity or C impossibility.
 */

/* 25 October 2026 approved-helper experiment; original C below is preserved.
 * Trial profile: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier
 * Trial checks: us: 0/21; us2: 0/21; pal: absent.
 * 372/372 bytes, still three argument-move words differ at +0x124. The actual qcopy helper is byte-neutral relative to the old qualified TI-copy/barrier source; it does not change the soft-frame-pointer scheduling tie.
 * Reopen: New evidence for genuine stack-work pointer lifetimes or the argument-move scheduling policy; do not repeat unchanged pointer aliases or flag sweeps.
 * No exact, linked or native-runtime credit is claimed.
 */

/* func_002B50E0 (boot function, 372 bytes; 20 levels, 21 places in all): NEAR MISS, measured
 * 22 October 2026.  Built alone (src/game/002B50E0.c) with
 * `-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier` it is retail's 372 bytes and
 * 0 of 21 places match, first difference at +0x124: the barrier puts the copy and the loads
 * after it in retail's order, and 3 words are left, the argument moves of the func_002B5828
 * call:
 *     retail: daddu $a2,$s3 ; daddu $a3,$sp ; daddu $a0,$s2 ; jal ; daddu $a1,$s1 (slot)
 *     here:   daddu $a2,$s3 ; daddu $a0,$s2 ; daddu $a1,$s1 ; jal ; daddu $a3,$sp (slot)
 *
 * Cause, measured with -fsched-verbose-5 (sched1, block of the five calls): the four moves
 * ($a0 = self, $a1 = data, $a2 = target, $a3 = &work[0]) become ready together after the
 * func_002B5678 call, with the same priority (6), the same class and 3 dependents each.  Before
 * reload the ranking then uses INSN_REG_WEIGHT: `target` dies at its move (weight 0), so $a2 goes
 * first; the other three have weight 1 and fall to luid order, $a0, $a1, $a3.  sched2 keeps that
 * order (all ties again), and reorg puts the last move in the slot.  Retail's order needs the $a3
 * move to tie with the $a2 one, i.e. its source a pseudo that dies there; but &work[0] is the
 * soft frame pointer itself (`$7=$1` in the dump), which never dies, and CSE turns any pointer
 * copy of it back into $1.  No source shape found: `work` for `&work[0]`, `float work[12]` with
 * casts (both unchanged), three separate TI locals (380 bytes); earlier `(void *)work`, a pointer
 * variable (388 bytes), a TI/float union; -fno-schedule-insns is worse (30 words).
 *
 * The rest is retail's: the prologue, self in $s2, target in $s3, data in $s1, the stack slots,
 * the `$gp` / absolute mix of D_001B1688 (the `sda` declaration) and the register-address copy
 * (`addiu $v1,$s2,0x10` / `lq $v0,0($v1)` / `sq $v0,0($sp)`).
 * A new aligned 48-byte character-buffer probe, with the position copied through an aligned
 * `TI128 *` and helper slots at offsets 0/16/32, still differs first at +0x124 in the same
 * three argument moves (0/21 under this profile). This storage spelling does not change the
 * permanent soft-frame-pointer tie; no trial source or cflags entry remains.
 */
extern int D_001B1688 __attribute__((sda));
extern char *func_002B5D28(void *);
extern void func_002B5CD8(void *, void *);
extern void func_002B5BC0(void *, void *, float);
extern void func_00282C88(void *);
extern void func_002B52A0(void *, void *, void *, void *, void *, float);
extern void func_002B5678(void *, void *, void *, void *);
extern void func_002B5828(void *, void *, void *, void *);
extern void func_002B5EF8(void *, void *, float);
extern void func_002B62A0(void);

typedef int PoseVector128 __attribute__((mode(TI)));

int func_002B50E0(void *self, void *target, float amount)
{
    char *data = func_002B5D28(self);
    PoseVector128 work[3];

    if (data == 0)
        return 8;
    if (D_001B1688 != *(int *)(data + 0xBC)) {
        *(int *)(data + 0x98) = *(int *)(data + 0x94);
        *(int *)(data + 0x94) = 0;
        if (!(*(int *)(data + 0x38) & 0x100))
            func_002B5CD8(self, data);
        {
            PoseVector128 *src = (PoseVector128 *)((char *)self + 0x10);
            work[0] = *src;
        }
        if (D_001B1688 - *(int *)(data + 0xBC) >= 2 || *(int *)(data + 0xBC) == 0) {
            func_002B5BC0(self, data, 0.0f);
            *(unsigned char *)(data + 0xEA) = 0xFF;
            *(int *)(data + 0x9C) &= ~2;
            *(float *)(data + 0xB4) = 0.0f;
            *(int *)(data + 0x80) = 0;
            func_00282C88(data + 0xA0);
        }
        *(int *)(data + 0xBC) = D_001B1688;
        func_002B52A0(self, data, target, &work[1], &work[2], amount);
        func_002B5678(self, data, &work[0], &work[2]);
        func_002B5828(self, data, target, &work[0]);
        func_002B5EF8(self, data, amount);
        func_002B62A0();
    }
    return *(int *)(data + 0x94);
}
