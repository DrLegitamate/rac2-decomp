/* func_002FE8D8 - 248 bytes, boot + 27 levels, USA v1.01.
   Replay in src/game/002FC8D0.c with explicit helper declarations (29 October
   2026) produces 240 bytes, 0/28 places. The earlier 248-byte result was not reproducible;
   this candidate is eight bytes short and differs in resident address setup,
   branches and call scheduling. The earlier direct reconstruction was 284
   bytes. Marker remains; no match is claimed. */
/* First C reconstruction from the USA v1.01 retail listing, 28 October 2026.
 * Profile -O2 -G0 -ffunction-sections: 284 bytes, 0/28 placements. The output
 * vector selection and helper calls are represented, but the branch tree,
 * global address lifetimes, and register allocation differ throughout. The
 * 36-byte excess prevents relocation-qualified placement checks. Reopen with
 * a verified model of the resident vector globals and a source shape that
 * keeps the retail branches and copy path. No match is claimed.
 */
typedef int F2E8D8Vector __attribute__((mode(TI)));
typedef union {
    F2E8D8Vector quad;
    float f[4];
} F2E8D8Vec4;

extern char D_00189E20[];
extern int D_001A8CA4;
extern char D_001A8CB0[];
extern int D_001A8CA0;
extern void func_00282C98(void *);

void func_002FE8D8(void *object, float *out)
{
    if (*(short *)(D_00189E20 + 0x348) != 0 && D_001A8CA4 == 0) {
        *(F2E8D8Vector *)out = *(F2E8D8Vector *)((char *)*(void **)(D_00189E20 + 0x2290) + 0xE0);
        return;
    }
    if (D_001A8CA4 != 0) {
        func_00282CF0(out, D_001A8CB0, object);
        out[2] = 0.0f;
        func_00282F20(out, out, 1.0f);
    } else if (D_001A8CA0 != 0) {
        float sign = (*(float *)(D_00189E20 + 0xBC) > 0.0f) ? -1.0f : 1.0f;
        func_00282CF0(out, D_00189E20 + 0xB0, object);
        func_00282F20(out, out, sign);
    } else {
        func_00282C98(out);
    }
}
