/* func_002A0048 - USA v1.01, 2026-10-28.
 *
 * Semantic reconstruction checked with `python3 tools/check.py func_002A0048
 * --diff`: 268 bytes versus retail's 308, no matching placements. This improves
 * on the initial 228-byte candidate by restoring the helper's queue-pointer
 * argument, both pointer returns, and volatile pointer-object accesses. Those
 * accesses are supported by the repeated retail reloads; func_002FC280 uses
 * the same measured volatile-pointer pattern for D_001B22A8.
 *
 * What remains: the compiler retains each global's absolute address in a saved
 * register and loads the pointer through it, while retail rematerializes the
 * global address before each access. That accounts for much of the remaining
 * size difference and has no source-level remedy established yet. Marker
 * remains; this is a near miss, not a match.
 */
typedef unsigned int u32;

extern int D_001B1B7C;
extern u32 * volatile D_001B1B80;
extern u32 * volatile D_001B22A8;
extern u32 D_001EF2E0[];

extern void func_002DFD88(u32 *);
extern void func_002DFBB0(u32 *);

int func_002A0048(void)
{
    u32 *saved;

    if (D_001B1B7C == 0) {
        D_001B1B80[0] = 0x10000000;
        D_001B1B80[1] = 0;
        D_001B1B80[2] = 0;
        D_001B1B80[3] = 0;
        return (int)D_001B1B80;
    }

    saved = D_001B22A8;
    D_001B22A8 = saved + 4;
    D_001B1B80[0] = 0x20000000;
    D_001B1B80[1] = (u32)D_001B22A8;
    D_001B1B80[2] = 0;
    D_001B1B80[3] = 0;
    func_002DFD88(D_001B1B80);
    func_002DFBB0(D_001EF2E0);
    D_001B22A8[0] = 0x20000000;
    D_001B22A8[1] = (u32)(D_001B1B80 + 4);
    D_001B22A8[2] = 0;
    D_001B22A8[3] = 0;
    D_001B22A8 = D_001B22A8 + 4;
    saved[0] = 0x20000000;
    saved[3] = 0;
    saved[1] = (u32)D_001B22A8;
    saved[2] = 0;
    return (int)D_001B22A8;
}
