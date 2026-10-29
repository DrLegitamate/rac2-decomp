/* Standalone semantic reconstruction. Integration into the actual shared
   unit src/game/002880E0.c under -O2 -G0 produces 272 bytes, 0/28 places;
   the 224-byte record copy becomes an ld/sd loop. A temporary -frac2-qcopy
   profile on that whole unit left the emitted code unchanged. Two qcopy_nc
   calls per 0x20-byte loop iteration also produce 272 bytes, 0/28; the
   measured qcopy form at 260 bytes remains the closest integrated attempt. */

#include "include_asm.h"

typedef unsigned char u8;

/* One slot of the entry table (stride 0xE0): its kind byte and the links to
   its parent (+0x4C) and first child (+0x4A). */
typedef struct {
    char pad0[4];
    u8 kind;
    char pad1[0x45];
    short child;
    short parent;
    char pad2[0x92];
} Entry_00288870 __attribute__((aligned(16)));

extern Entry_00288870 D_00239BA0[];

/* Walks to the root of the chain index is in, then depth links down it, and
   copies that entry to dst when its kind byte equals depth.  Returns 1 when
   copied. */
int func_00288870(Entry_00288870 *dst, int index, int depth)
{
    int ret = 0;
    int i;
    int n;

    if (depth < 0xFF) {
        i = index;
        while (D_00239BA0[i].parent != 0)
            i = D_00239BA0[i].parent;
        n = 0;
        if (depth > 0) {
            if (D_00239BA0[i].child != 0) {
                do {
                    i = D_00239BA0[i].child;
                    n++;
                } while (n < depth && D_00239BA0[i].child != 0);
            }
        }
        if (D_00239BA0[i].kind == depth) {
            *dst = D_00239BA0[i];
            ret = 1;
        }
    }
    return ret;
}
