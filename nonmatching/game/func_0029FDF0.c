/* func_0029FDF0 - 240 bytes, boot + 27 levels, USA v1.01.
   Candidate: builds the two DMA tags, calls func_002A4AD8 and func_002FC748, then closes the chain. The cursor and tag-base globals need per-level ref symbols; D_001A72D0 needs -G8, so the candidate was compiled from a -g8.c unit.
   Check (fresh standalone replay, 2026-10-29): python3 tools/check.py func_0029FDF0 --diff; 176 bytes, expected 240, 0 of 28 places match. Retail uses a 0x20-byte frame; this candidate uses 0x30 bytes and coalesces pointer loads/stores. Direct-global cursor/tag access alternatives measured 196/240 and 180/240, also 0/28; neither improves on this candidate's prologue shape. */
extern int ref_L00_0029FDF0_00 __attribute__((section(".data")));
extern int ref_L00_0029FDF0_01 __attribute__((section(".data")));
extern int D_001A72D0 __attribute__((sda));
extern void func_002A4AD8(int);
extern void func_002FC748(void);
void func_0029FDF0(void) {
    int *first = (int *)ref_L00_0029FDF0_00;
    int *base = (int *)ref_L00_0029FDF0_01;
    int *cursor;
    ref_L00_0029FDF0_00 = (int)first + 0x10;
    base[0] = 0x20000000;
    base[1] = ref_L00_0029FDF0_00;
    base[2] = 0;
    base[3] = 0;
    func_002A4AD8(D_001A72D0);
    func_002FC748();
    cursor = (int *)ref_L00_0029FDF0_00;
    cursor[0] = 0x20000000;
    cursor[1] = ref_L00_0029FDF0_01 + 0x10;
    cursor[2] = 0;
    cursor[3] = 0;
    ref_L00_0029FDF0_00 += 0x10;
    first[0] = 0x20000000;
    first[3] = 0;
    first[1] = ref_L00_0029FDF0_00;
    first[2] = 0;
}
