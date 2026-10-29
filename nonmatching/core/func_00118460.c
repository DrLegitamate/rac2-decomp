/* func_00118460 - retained C near miss, not linked. A 29 October 2026
 * pointer-induction variant is 100/112 bytes, 0/1 boot places under the
 * isolated game profile `-O2 -G2 -ffunction-sections`. Current replay in this
 * source unit still differs at +0x08: cc1 uses `$a0` instead of retail's
 * `$v1`, emits `bne` plus a separate `bgtz` loop back edge instead of retail's
 * `beql`/store delay slot, and has a different tail. The equality-branch
 * rewrite below measured byte-identically to this candidate. The earlier
 * index-recomputed form was 116/112 and matched the
 * entry test and initial zero store through +0x1C, but peeled the loop. A
 * direct-return pointer-loop trial also emitted the same branch-likely slot
 * but was only 96 bytes. A separate index-decrement loop with an early return
 * compiled to 104/112 bytes and changed the entry branch target, so it was
 * discarded. A 29 October condition-led carry loop (`while (count > 0 &&
 * *--p == '9')`) did produce retail's `beql` with the zero store in its delay
 * slot, but grew to 136/112 bytes and remained 0/1 because the separate count
 * and character checks expanded the loop. The replay from the original SDK translation unit (`sdk -O2
 * -G2`) also matches 0/1 and differs from retail; the target was then moved
 * temporarily into its own unit for the documented game-profile measurements.
 * No sibling-call interpretation is involved: the
 * early return target is the function's own final block.
 */
int func_00118460(char *buf, int len) {
    char *p;
    int c;

    if (len <= 0) goto fail;
    len--;
    p = buf;
    p += len;
    c = *p;
    if (c < '5') goto fail;
    *p = '0';
    while (len > 0) {
        len--;
        p--;
        c = *p;
        if (c != '9') goto increment;
        *p = '0';
    }
    return 0;

increment:
    *p = *p + 1;
    return *p;

fail:
    return 1;
}
