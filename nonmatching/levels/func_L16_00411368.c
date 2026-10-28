/* Batch 3 (2026-10-28) handoff notes:
func_L16_00411368 (276 B): 60 masked lines, but only the FP registers/constant placement differ (see nonmatching/levels/func_L16_00411368.c notes).
Retail keeps the accumulator in $f20 and loads 120.0f twice (mtc1 into $f12 for the call, again into $f0 before div.s). cse merges the two literals into one pseudo that lives across the call (so it takes a saved FPU reg and the accumulator lands in $f21).
This session: literals in both places (no f12 local) gives the same code. Not tried (no route found): getting the second 120.0f to be a different value for cse (int vs float forms fold at tree level).
*/

/* in src/levels/16_snivelak/L16_00403900.c, default flags; size is right (276 B). Callees: func_00283CF0 (s32 (float)), func_00283198 (float (float)),
   func_002AA548 (void (void *, void *, float, float, float, float)), func_L16_00412F48 (now exact, in L16_00412F48-g8.c). */
void func_L16_00411368(u8 *arg)
{
    u8 *s0;
    u8 *s1;
    float f20;
    s32 v0;

    s0 = arg;
    s1 = *(u8 **)(arg + 0x68);
    f20 = 10.0f;
    if (s0[0x20] == 0xD || s0[0x20] == 0xF || s0[0x20] == 0xE || s0[0x20] == 0x11)
        f20 = 25.0f;
    v0 = func_00283CF0(120.0f);
    f20 = f20 + func_00283198((float)(D_L16_001B2648 % v0) / 120.0f * 6.2831855f - 3.1415927f);
    func_002AA548(s0 + 0x18, s1 + 0x268, *(float *)(s1 + 0x264) + f20,
                  0.0083333338f, 0.0027777778f, 0.16666667f);
    func_L16_00412F48(s0);
}
