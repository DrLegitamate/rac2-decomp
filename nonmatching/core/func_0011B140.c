/* Current semantic C probe, not linked. Rechecked 28 October 2026 in the
 * marker's unit: 184/164 bytes, 0/1 USA v1.01 boot place. It uses two real
 * `__sync_synchronize()` barriers around the 0x1000F000 handshake, an unsigned
 * 64-bit result and volatile flag/MMIO accesses. The output contains both
 * required `sync` instructions, but saves each helper result in $s0,
 * materializes the MMIO address repeatedly and grows beyond the retail body.
 * A branch-shaped spelling that duplicates each real MMIO store in both
 * callback arms grew to 212 bytes (0/1): cc1 did not merge the stores and
 * placed both callbacks before the polling loop. See blocker 32 for the
 * measured diff. */
extern void func_0011AF90(void *, void *);
extern int func_0011F5E0(void);
extern void func_0011F628(void);

unsigned long long func_0011B140(void) {
    volatile int flag = 0;
    unsigned long long result;
    int r;

    func_0011AF90((void *)&flag, (void *)&result);
    r = func_0011F5E0();
    *(volatile unsigned int *)0x1000F000 = 4;
    __sync_synchronize();
    if (r != 0)
        func_0011F628();
    while ((*(volatile unsigned int *)0x1000F000 & 4) == 0 && flag == 0)
        ;
    r = func_0011F5E0();
    *(volatile unsigned int *)0x1000F000 = 4;
    __sync_synchronize();
    if (r != 0)
        func_0011F628();
    return result;
}

/* Wave 24 (worker 05): the initial no-sync attempt measured 152 bytes against
   retail's 164. A later isolated probe using `__sync_synchronize()` confirmed
   that the compiler emits `sync`, but measured 184 bytes. The probe's external
   declarations were incomplete, so its body diff was inconclusive. The
   function remains unresolved. The measurements below describe the earlier
   attempt and are retained as historical evidence:

   What is measured and right:
   - the two stack objects are an int flag at 0x00 (retail `sw $zero,0x0($sp)`)
     and a 64-bit result at 0x08 (retail `ld $v0,0x8($sp)`), so the result is
     an unsigned long long: a signed one costs the sign extension
     (`dsll32`/`dsra32`) that retail does not have.
   - the flag is read inside the loop, so it is volatile (retail reloads
     `lw $v0,0x0($sp)` every pass); the loop is a do-while, the register's
     bit-2 test comes first and the flag's test is the back edge.
   - the two calls to func_0011F5E0 are two separate calls: the first one's
     result is tested right after the first store (retail `beqz $v0`), the
     second one's after the second store, so the value is not kept in a
     callee-saved register (that would add the $s0 save retail does not
     have).
   - the second store goes to the same address as the first one, 0x1000F000:
     retail's `lui $at,0x1001` + `sw $v1,-0x1000($at)` is %hi(0x1000F000) and
     %lo(0x1000F000); the address 0x10010000 would give an offset of 0.
   - the first address is used again in the loop, so it is materialised with
     lui+ori; the second one is used once, so it is lui+%lo.  */
extern int func_0011AF90(void *, void *);
extern int func_0011F5E0(void);
extern int func_0011F628(void);

unsigned long long func_0011B140_w24(void) {
    volatile int flag = 0;
    unsigned long long result;
    int v;

    func_0011AF90(&flag, &result);
    v = func_0011F5E0();
    *(volatile int *)0x1000F000 = 4;
    if (v != 0) {
        func_0011F628();
    }
    do {
        if ((*(volatile int *)0x1000F000 & 4) != 0) {
            break;
        }
    } while (flag == 0);
    v = func_0011F5E0();
    *(volatile int *)0x1000F000 = 4;
    if (v != 0) {
        func_0011F628();
    }
    return result;
}
