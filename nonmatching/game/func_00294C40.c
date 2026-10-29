#include "include_asm.h"

extern int func_00282A18(int);

extern int D_001A72D0;

extern int D_001B15FC;

extern char D_001B9340[];

/* Near miss for func_00294C40 (boot 0x00294C40, 320 bytes, 28 places: boot and 27
 * levels).  Best local check: 292 bytes, `func_00294C40: 0 of 28 places match`.
 *
 * Retail body: builds a 16-byte texture record in the 64-entry table
 * D_001B9340 (index D_001B15FC), appends nothing when full, and returns a packed
 * 64-bit descriptor.  n0 = func_00282A18(object[8]) (log2 width), n1 =
 * func_00282A18(object[0xC]) (log2 height), old = the VRAM cursor D_001A72D0.
 * The descriptor is
 *   ((u64)(old >> 8) << 37) | ((u64)((old + 0x400) >> 8)) |
 *   ((u64)n1 << 30) | ((u64)n0 << 26) | 0x130 |
 *   ((u64)(1 << max(n0 - 6, 0)) << 14) | (1ULL << 34) | (1ULL << 63)
 * and the cursor becomes old + 0x400 + (1 << (n0 + n1)).  The record is
 * +0 object+0x20, +4 0, +6 old>>8, +8 object+0x420, +0xC n0, +0xD n1,
 * +0xE (old+0x400)>>8.
 *
 * This draft recovers all of that; the first observed difference is the stack
 * frame: 292 bytes with a 0x30 frame and values in $s1/$s2, against retail's
 * 320 bytes, 0x70 frame and a single saved $s0.  Retail keeps its five locals in
 * memory: ptr[2] at sp+0/sp+4, off (0x400) at sp+0x14, n[2] at sp+0x4C/0x50, and
 * reloads n0/n1 with lbu for the record bytes.  This draft already declares
 * ptr[2] and n[2] as arrays (which moved the frame from 0x20 to 0x30 and put n at
 * sp+0x10/0x14) but the 0x38-byte gap to retail's n slots is unexplained: the
 * offsets imply another 0x38 bytes of locals that no retail instruction touches.
 *
 * Current-master aggregate experiment: one local struct with ptr[2] at +0/+4,
 * off at +0x14 and n[2] at +0x4C/+0x50 compiled to 300 bytes, 0 of 28 places.
 * It grew the 292-byte baseline but changed the record stores and still did not
 * reach retail's 320-byte body. The unexplained frame gap alone is therefore not
 * enough; reopen only with a source-shape hypothesis that also accounts for the
 * remaining descriptor and record instruction differences.
 */
long long func_00294C40(char *object)
{
    int off = 0x400;
    char *ptr[2];
    int n[2];
    int old;
    int count;
    int shift;
    int size;
    unsigned long long tag;
    char *rec;

    ptr[0] = object + 0x20;
    n[0] = func_00282A18(*(int *)(object + 8));
    n[1] = func_00282A18(*(int *)(object + 0xC));
    old = D_001A72D0;
    count = D_001B15FC;
    shift = n[0] - 6;
    if (shift < 0)
        shift = 0;
    size = 1 << (n[0] + n[1]);
    tag = ((unsigned long long)(old >> 8) << 37) |
          ((unsigned long long)((old + 0x400) >> 8)) |
          ((unsigned long long)n[1] << 30) |
          ((unsigned long long)n[0] << 26) | 0x130 |
          ((unsigned long long)(1 << shift) << 14) |
          (1ULL << 34) | (1ULL << 63);
    D_001A72D0 = old + 0x400 + size;
    ptr[1] = object + off + 0x20;
    if (count < 0x40) {
        rec = D_001B9340 + count * 16;
        *(int *)(rec + 0) = (int)ptr[0];
        *(unsigned short *)(rec + 4) = 0;
        *(unsigned short *)(rec + 6) = (unsigned short)(old >> 8);
        *(int *)(rec + 8) = (int)ptr[1];
        *(unsigned char *)(rec + 0xC) = n[0];
        *(unsigned char *)(rec + 0xD) = n[1];
        *(unsigned short *)(rec + 0xE) = (unsigned short)((old + 0x400) >> 8);
        D_001B15FC = count + 1;
    }
    return tag;
}
