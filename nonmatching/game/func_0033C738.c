/* Game -O2 -G0: 636/640 bytes, 0/28 USA placements.
 * Unaligned string-table copies match their widths. Constant colours,
 * format and lookup intermediates receive a different callee-save order,
 * and the final boolean index selects a pointer rather than a byte offset.
 * Next: inspect allocation lifetimes with the current regalloc diagnostic.
 */
#include "common.h"
typedef struct { int id[2]; } MenuStringPair;
typedef struct { int id[3]; } MenuStringTriple;
extern MenuStringPair D_001ADE20[], D_001ADDD0[];
extern MenuStringTriple D_001ADE28[];
extern char D_001ADDD8[];
extern int D_001A7BA4, D_001A7BA8, D_001A7BAC;
extern unsigned char D_001A7BB1;
extern int D_001ADE14, D_001ADE1C, D_001ADE04, D_001ADE0C;
extern int D_L00_001ADE00 SDATA(D_L00_001ADE00);
extern int D_L00_001ADE08 SDATA(D_L00_001ADE08);
extern int D_L00_001ADE10 SDATA(D_L00_001ADE10);
extern int D_L00_001ADE18 SDATA(D_L00_001ADE18);
extern void func_0033AF48(void *);
extern char *func_00288FB8(int);
extern void func_00115DA8(char *, const char *, ...);
extern int func_0027FB40(int, int, unsigned long long, unsigned char *, int);

void func_0033C738(char *object)
{
    char buffer[128];
    MenuStringPair toggles;
    MenuStringTriple choices;
    MenuStringPair final;
    int *last;
    char *label;
    int style;
    func_0033AF48(object + 8);
    toggles = D_001ADE20[0];
    choices = D_001ADE28[0];
    final = D_001ADDD0[0];
    last = final.id;
    style = *(int *)(object + 0x2a8) == 0 ? (int)0x80d0d0d0 : (int)0x70808080;
    label = func_00288FB8(0x2de2);
    func_00115DA8(buffer, D_001ADDD8, label, func_00288FB8(toggles.id[D_001A7BA4 != 0]));
    func_0027FB40(D_L00_001ADE00, D_001ADE04, style, (unsigned char *)buffer, -1);
    style = *(int *)(object + 0x2a8) == 1 ? (int)0x80d0d0d0 : (int)0x70808080;
    label = func_00288FB8(0x2de1);
    func_00115DA8(buffer, D_001ADDD8, label, func_00288FB8(toggles.id[D_001A7BA8 != 0]));
    func_0027FB40(D_L00_001ADE08, D_001ADE0C, style, (unsigned char *)buffer, -1);
    style = *(int *)(object + 0x2a8) == 2 ? (int)0x80d0d0d0 : (int)0x70808080;
    label = func_00288FB8(0x2f18);
    func_00115DA8(buffer, D_001ADDD8, label, func_00288FB8(choices.id[D_001A7BAC]));
    func_0027FB40(D_L00_001ADE10, D_001ADE14, style, (unsigned char *)buffer, -1);
    style = *(int *)(object + 0x2a8) == 3 ? (int)0x80d0d0d0 : (int)0x70808080;
    label = func_00288FB8(0x31e4);
    func_00115DA8(buffer, D_001ADDD8, label, func_00288FB8(last[D_001A7BB1 != 0]));
    func_0027FB40(D_L00_001ADE18, D_001ADE1C, style, (unsigned char *)buffer, -1);
}
