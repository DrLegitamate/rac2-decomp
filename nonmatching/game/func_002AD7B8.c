#include "include_asm.h"

/* The retail body marks a level as available: it returns when the byte table at
   0x001A7BC8 already holds the flag, sets that flag for the levels from 0x15 on,
   and for level 24 appends the level to the table of 28 words at 0x0000D948 after
   the entries that are in use.

   The frame, the calls, the second loop and the final store match; the first loop
   does not: the retail keeps an empty loop of 28 iterations whose test is
   `slti $v0,$v1,0x1C` / `bnez` with the increment in the delay slot, which is the
   shape of `while (i++ < 28)`. The retained source uses
   `while (delay++ < 28) {}`: it preserves retail's increasing counter and
   places the increment in the branch delay slot. The current-master USA v1.01
   check is 164 bytes, 0/28; the counter register and later branch/register
   allocation still differ. A separate delay variable produces the target
   counter register but adds a copy before the compare. `while (delay < 28)
   delay++` becomes a countdown, and this cc1 rejects `-fno-ivopts`. The loop
   has no source-level side effect beyond its finite delay; do not add a fake
   dependency. */
typedef unsigned char u8;

extern u8 D_001A7BC8[];
extern int D_0000D948[];

void func_002AD7B8(int a0)
{
    int i;
    int delay = 0;
    int count = 0;

    if (D_001A7BC8[a0] != 0)
        return;
    while (delay++ < 28) { }
    if (a0 >= 0x15)
        D_001A7BC8[a0] = 1;
    if (a0 != 24)
        return;
    for (i = 0; i < 28; i++)
        if (D_0000D948[i] != 0)
            count++;
    D_0000D948[count] = a0;
}
