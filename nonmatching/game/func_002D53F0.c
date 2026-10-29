/* Near miss: the current-master USA v1.01 replay with the callee's 32-bit style
 * argument compiles to 136/140 bytes and 0/28 placements. The earlier 140-byte
 * candidate used common.h's 64-bit u64, while the matched callee's local alias
 * is unsigned long (32 bits in this target). The float constants remain
 * reversed between $f1/$f2, and the style constant expands to a different
 * sequence. The old 140-byte result is superseded; the callee ABI correction
 * is retained here. */
#include "common.h"

extern float D_001B23A4 MACRO_ADDR;
extern void func_0027C540(long);
extern void func_0029C530(void);
extern unsigned char *func_00288FB8(int);
extern void func_0027C660(void);
extern int func_0027FAA8(int, int, u32, unsigned char *, int);

int func_002D53F0(void)
{
    int y;

    func_0027C540(0);
    func_0029C530();
    y = (int)(D_001B23A4 * 329.0f + 0.5f);
    func_0027FAA8(0x1A6, y, 0x80F0F0F0u, func_00288FB8(0x2D4F), -1);
    func_0027C660();
    return 0;
}
