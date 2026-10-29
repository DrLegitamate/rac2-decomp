/* Near miss: the candidate is 336 bytes against the retail's 344 (two words short).
 *
 * What matches: the two calls and their argument setup (`daddu $a0,$s0,$zero`), the
 * level lookup, the second loop's shape (the bounds test, the table access through
 * `$gp`, the two calls), the update block's arms (`subu`/`negu`/`movn`) and the whole
 * epilogue.
 *
 * What differs:
 *  - the prologue keeps the `%hi` of D_001A7AFD in a register of its own
 *    (`lui $v1,%hi` + `lbu $a0,%lo($v1)`), the retail materialises the address in the
 *    load's own register (`lui $a0,0x1A` + `lbu $a0,0x7AFD($a0)`);
 *  - the scan loop's exit is a plain `beq` where the retail has a `beql` with the
 *    `delta = 1` in its (annulled) delay slot, and the `level < 0x1C` test is a `beql`
 *    where the retail has a `beqz` with `index = 0` in its delay slot - the scheduler
 *    puts the two assignments in the other delay slots;
 *  - the update block lacks the retail's `slti $a0,$s1,1` and its
 *    `daddu $s1,$v0,$zero` (the retail's delta variable is kept in a 64-bit register,
 *    so the negation is copied into it with a zero extension; this candidate keeps the
 *    delta in 32 bits and negates it in place).
 *
 * Tried: the delta as `unsigned int` (332 bytes, the condition changes to `slt`), the
 * comparison with a cast to `int` (a 32-bit compare with -1, as the retail has), the
 * constants (`notfound`, `limit`, `one`) declared inside the loop's scope, the two
 * names of the level table (`D_001AA4F0` bare and `D_001AA4F0_1` through `$gp`), the
 * lookup's result compared through a function pointer cast (a 64-bit argument, which
 * makes the update block match but the -1 compare 64-bit again). On current master,
 * counted-index `for` and pre-incremented `do` forms of the scan both retain 336 bytes.
 * Declaring `delta` as `long long` gives 352 bytes; narrowing the update expression
 * back to `int` before assigning to it gives 372. All three forms match 0/28.
 */
extern int *D_001AA4F0;
extern int *D_001AA4F0_1 __attribute__((sda));

extern int D_001C4FA0[];

extern unsigned char D_001A7AFD;

extern int func_00295828(int id);
extern int func_00295870(int);

/* looks the level up in the map's table and then walks the levels next to it */
int func_002958B8(void)
{
    int flag = D_001A7AFD ? 0x100 : 0;
    unsigned int id = D_001C4FA0[0x230 / 4] + flag;
    int level;
    int *p;
    int index;
    int delta;
    int notfound;
    int limit;
    int one;
    int offset;
    int entry;

    if ((int)func_00295828(id) == -1) {
        if (func_00295870(id) != 0)
            return id;
    }
    level = D_001C4FA0[0x230 / 4];
    if (level < 0x1C) {
        index = 0;
        p = D_001AA4F0;
        while (*p != level) {
            p++;
            index++;
        }
    }
    delta = 1;
    notfound = -1;
    limit = 4;
    one = 1;
    offset = index + delta;
    do {
        if (offset < 0)
            continue;
        if (offset >= 0x1C)
            continue;
        entry = D_001AA4F0_1[offset];
        if (entry == 0)
            continue;
        id = entry + flag;
        if ((int)func_00295828(id) == notfound) {
            if (func_00295870(id) != 0)
                return id;
        }
        delta = (delta >= one) ? -delta : (one - delta);
        offset = index + delta;
    } while (delta != limit);
    return -1;
}
