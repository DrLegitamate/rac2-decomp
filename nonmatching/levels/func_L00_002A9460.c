/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections, as a sibling unit
 * src/levels/shared/L00_002A6420-q.c (it needs common.h for qcopy; the native unit
 * has its own typedefs). Remove the marker from L00_002A6420.c when trying it.
 * Retail: 412 bytes; compiled: 412 bytes.
 * Coverage: us: 0/27 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Re-aims the hero object at the camera state in D_00189E20: copies two vectors into
 * it, refreshes it, then (unless +0x1F0 is set or the object has no +0x98) places it
 * twice along the view at clamped distances.
 *
 * Control flow, calls, constants and the float code match. What differs (47 lines in
 * level 00) is the table base: retail loads %hi(D_00189E20) into $s1, uses
 * $s0 = base for the first half and forms g + 0x80 in $a1 for the first copy only;
 * after func_L00_002A76B8 it adds the low part to $s1 in the call's delay slot and
 * uses $s1 for the second half, with $s0 = base + 0x80 for both later copies. cc1
 * keeps one base in $s0 and base + 0x80 in $s1 for the whole function.
 * Retail also loads obj->+0x24->+6 into $v1 and never uses it (here a volatile read).
 * Tried without closing it: a second base variable for the second half, set at
 * four places; the symbol directly in either half; qcopy_nc for any of the copies.
 * Next: the 002E48E8 near miss has the same high-part split; a spelling that gives
 * the second half its own base pseudo.
 */
#include "common.h"

extern char D_00189E20[];

extern void func_L00_002A75D8(void);
extern void func_L00_002A76B8(void);
extern void func_00282AB0(void *, void *, int);
extern void func_002A0F48(void *);
extern void func_L00_002D3778(void *, void *, float);
extern void func_L00_00310748(void *, int, void *, float, float);
extern s32 func_L00_002ADF80(void);

void func_L00_002A9460(void)
{
    char *g = D_00189E20;
    f32 v[4] __attribute__((aligned(16)));
    f32 lim;
    f32 d;
    f32 a;
    u8 *obj;

    (*(u8 **)(g + 0x2290))[0xA8] = 0xFF;
    qcopy(*(u8 **)(g + 0x2290) + 0x10, g + 0x80);
    func_L00_002A75D8();
    qcopy(*(u8 **)(g + 0x2290) + 0xF0, g + 0x90);
    func_L00_002A76B8();
    func_00282AB0(*(u8 **)(g + 0x2290) + 0xC0, g, 0x30);
    func_002A0F48(*(void **)(g + 0x2290));
    obj = *(u8 **)(g + 0x2290);
    *(volatile u8 *)(*(u8 **)(obj + 0x24) + 6);
    obj[0x63] = 0x10;
    if (*(s16 *)(g + 0x1F0) != 0)
        return;
    if (*(s32 *)(*(u8 **)(g + 0x2290) + 0x98) == 0)
        return;
    lim = 0.05f;
    qcopy(v, g + 0x80);
    func_L00_002D3778(v, v, *(f32 *)(g + 0x254));
    d = *(f32 *)(g + 0x250) - *(f32 *)(g + 0x254);
    if (d < lim)
        d = lim;
    func_L00_00310748(*(void **)(g + 0x2290), 0, v, *(f32 *)(g + 0x264), d);
    a = *(f32 *)(g + 0x264) + lim;
    if (*(s32 *)(g + 0x229C) == 4)
        a += 0.15f;
    if (func_L00_002ADF80() != 0)
        a = *(f32 *)(g + 0x254);
    qcopy(v, g + 0x80);
    func_L00_002D3778(v, v, a);
    d = *(f32 *)(g + 0x250) - a;
    if (d < lim)
        d = lim;
    func_L00_00310748(*(void **)(g + 0x2290), 1, v, *(f32 *)(g + 0x264), d);
}
