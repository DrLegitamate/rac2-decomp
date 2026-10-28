/* Batch 3 (2026-10-28) handoff notes:
Best C: draft.c (new file L00_00324D18.c, default -O2 -G0; names canonical: func_002AB1F0, func_002AF580). 6 diff lines: callee proto from L00_003C2FC8-g8.c (p,p,p,f,f,i,i,i,f,f,f,p,p) gives right t2-last arg order and right branch layout (positive condition returns reloaded object first), but save regs come out s0=b,s1=a,s2=c vs retail s0=c,s1=b,s2=a. Proto with c 7th int arg gets right save regs but t2 move before the f12..f16 moves. Tried c as int, ctx local, param order reversed, float block at every position of the arg list.

Differing lines:
  00324D28  daddu       $s0, $a1, $zero              | daddu       $s0, $a2, $zero
  00324D30  daddu       $s1, $a0, $zero              | daddu       $s1, $a1, $zero
  00324D38  daddu       $s2, $a2, $zero              | daddu       $s2, $a0, $zero
  00324DC4  daddu       $a0, $s1, $zero              | daddu       $a0, $s2, $zero
  00324DC8  daddu       $a1, $s0, $zero              | daddu       $a1, $s1, $zero
  00324DE0  daddu       $t2, $s2, $zero              | daddu       $t2, $s0, $zero
func_L00_00324D18: 0 of 27 places match (src/levels/shared/L00_00324D18.c)
masked diff lines: 6
*/

#include "common.h"


typedef struct { float x, y, z; } V3;
extern u8 D_00189E20[];
extern V3 D_L00_001AA300 __attribute__((aligned(1)));
extern float *func_002AB1F0(u8 *);
extern u8 *func_002AF580(void *, void *, void *, float, float, int, int, int, float, float, float, void *, void *);
u8 *func_L00_00324D18(void *a, void *b, void *c, float d, float e, float f, float g, float h)
{
    V3 point;
    float scratch[4];
    u8 *resident = D_00189E20;
    u8 *object = *(u8 **)(resident + 0x1450);
    float *health;
    if (object != 0 && object[0x20] != 0xfe && object[0x20] != 0xfd &&
        (health = func_002AB1F0(object)) != 0 && *health > 0.0f)
        return *(u8 **)(resident + 0x1450);
    point = D_L00_001AA300;
    return func_002AF580(a, b, scratch, d, e, 0, 0, 0, f, g, h, c, &point);
}
