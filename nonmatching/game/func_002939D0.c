#include "include_asm.h"

extern int D_0014B540[];

extern int D_001A7288;

extern s32 func_002B7C10(s32 a0, s32 a1, s32 a2);

/* Current-master check for func_002939D0 (28 October 2026): 116 bytes vs 128,
 * 0/28 USA v1.01 placements. The old “three words left” summary is stale.
 *
 * The whole body is recovered: the 0x1057-granular arena address
 *
 *   (0x1FF7FF0 - ((field_0x34C << 11) + 0x1057) & 0xFFFFF000) & 0xFFFFFFF0
 *
 * is stored in D_001A7288, 0x60 is written through it and func_002B7C10 is called with
 * D_001A7288 + *D_001A7288 and two table fields. The final `& 0xFFFFFFF0` in
 * this source is redundant: the preceding arithmetic already produces a
 * 16-byte-aligned value, and retail has no separate final alignment
 * instruction. Rewriting the redundant mask as `(addr >> 4) << 4` emits an
 * extra `and`, remains 116 bytes and 0/28, and does not match. The nested
 * expression without that extra instruction remains the closer candidate;
 * its allocation and store order still differ from retail.
 */
int func_002939D0(void) {
    int *b = D_0014B540;
    unsigned int v = b[211];
    unsigned int addr = (0x1FF7FF0 - (((v << 11) + 0x1057) & 0xFFFFF000u)) & 0xFFFFFFF0u;
    D_001A7288 = (int)addr;
    *(unsigned int *)addr = 0x60;
    func_002B7C10(D_001A7288 + *(int *)D_001A7288, b[210] + b[203], b[211]);
    return 1;
}
