/* Current-master best candidate, rechecked 28 October 2026 in the real
   -G8 marker unit: 60/60 bytes and 0/28 USA v1.01 placements. Expressing the
   three resident data reads through their boot addresses fixes the relocations
   and matches every word except +0x04: cc1 loads the first byte into $v0,
   retail loads it into $v1. The other branches, delay slots, two near-$gp
   loads, return values and tail match. A named-result form is 52 bytes; a
   conditional expression is 64 bytes. A shared `goto fail` form also
   reproduces the same 60-byte body and first-load register mismatch. A direct
   `&&` chain is 52 bytes, 0/28: it gets the first load into `$v1` and the
   second into `$v0`, but puts the third load in `$v1`, changes the branch
   layout and misses retail's return-value delay-slot move. The data addresses below are boot-resident and shared by all 28
   programs; no level address is hard-coded.

   A 29 October early-return form (`if (!first) return 0; if (!second) return
   0; return third != 0`) compiles to 48 bytes, 0/28 in the original unit. It
   preserves the read order but reverses the retail branch directions and
   creates separate zero-return paths; it is not closer.

   A 29 October isolated `-O2 -G8 -ffunction-sections -fno-schedule-insns`
   unit with the nested-return body remains 60/60 bytes and 0/28. It leaves
   the first byte load in `$v0` instead of retail's `$v1`; the later body is
   otherwise aligned. Disabling instruction scheduling does not change the
   unresolved allocation. */
#define D_001395C1 (*(unsigned char *)0x001395C1)
#define D_001A7B05 (*(unsigned char *)0x001A7B05)
#define D_001A7B0C (*(unsigned char *)0x001A7B0C)

int func_0029DC90(void)
{
    if (D_001395C1) {
        if (D_001A7B05) {
            if (D_001A7B0C)
                return 1;
        }
    }
    return 0;
}
