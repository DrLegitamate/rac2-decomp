/* Semantically equivalent explicit search-loop near miss.
 *
 * The original nested-condition candidate was 132 bytes, matching retail's
 * 132-byte extent, but 0/28 places. A temporary single-loop/goto form compiled
 * to 120 bytes, 0/28 USA v1.01 places. It better exposes the shared loop exit,
 * but differs in table-base setup, cursor/index allocation, branch layout and
 * return-value scheduling. A structured `for (;;)` with `break` for the same
 * terminators measures 144 bytes and 0/28; it adds cursor/index work and is
 * farther from the 132-byte target. Keep the 120-byte form as the closer near
 * miss and the assembly marker until a strict check passes.
 */
extern int ref_L00_002F7320_00[];

int func_002F7320(int value, int key, int field)
{
    int *base = ref_L00_002F7320_00;
    int *cursor;
    int count = 0;
    int entry;
    int result = 0;

    if (base[0] == 0)
        goto done;
    if (key == base[0])
        goto found;
    cursor = base + 4;
loop:
    entry = *cursor;
    if (entry == 0)
        goto done;
    count++;
    if (count >= 56)
        goto found;
    if (key == entry)
        goto found;
    cursor += 4;
    goto loop;
found:
    if (base[count * 4] != 0)
        result = base[count * 4 + field + 1] == value;
done:
    return result;
}
