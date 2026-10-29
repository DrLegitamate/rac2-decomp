/* func_0033D2C0 - 384 bytes. Rechecked 29 October 2026: isolated `python3 tools/check.py func_0033D2C0 --diff` candidate compiled 384/384 bytes, 0/28 USA v1.01 places; first difference is the callee-saved object register at +0x04. Opus near miss (M18): the three-row slider panel in func_0033CC20 style; size exact, 41 lines of callee-saved register assignment (retail: object s1, format s0, bright s2, dim s3, &pair s4, color s5). */
/* 29 October 2026 decomp-permuter run (`rac2/ntsc`, -O2 -G0, four workers,
   180 seconds): base score 42, best score 3 after 9,355 candidates. The best
   generated source takes `&format` and later reads `*new_var`; it has no
   permuter artefacts, but the actual checker still reports 0/28, first at
   +0x114 in the selector/index setup. Splitting the boolean selector into a
   local on that candidate moved the first mismatch to +0xF4 and still gave
   0/28. Rewriting the selection as `D_001A7B98 ? pair.ids[1] : pair.ids[0]`
   reduced the candidate to 376/384 bytes, also 0/28. No candidate passed
   `tools/check.py`, so the marker remains. Search outputs are private under
   /tmp and are not source. */
#include "include_asm.h"
/* Draws the three-row slider panel: two labelled sliders and the shared "%s: %s" option row,
 * the row matching the current selection in the bright color (func_0033CC20's layout). */
typedef struct { int ids[2]; } SolTextPair2;
extern SolTextPair2 D_L00_001AE1A8;
extern char D_L00_001AE1B0[];
extern char D_L00_001AE118[];
extern int D_001A7B98;
extern void func_0033AF48(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_0027FA10(int, int, unsigned long, char *, int);
extern int func_0027FB40(int, int, unsigned long, char *, int);
extern void func_00336548(void *);

void func_0033D2C0(char *object)
{
    char buffer[128];
    SolTextPair2 pair;
    char *label;
    char *second;
    char *format;
    int color;

    func_0033AF48(object + 8);
    color = *(int *)(object + 0x2A8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE1A8;
    format = D_L00_001AE1B0;
    label = func_00288FB8(0x2F0F);
    func_00115DA8(buffer, format, label);
    func_0027FA10(0x100, 0x91, color, buffer, -1);
    func_00336548(object + 0x2AC);

    color = *(int *)(object + 0x2A8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label = func_00288FB8(0x2F10);
    func_00115DA8(buffer, format, label);
    func_0027FA10(0x100, 0xBE, color, buffer, -1);
    func_00336548(object + 0x2F4);

    color = *(int *)(object + 0x2A8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    format = D_L00_001AE118;
    label = func_00288FB8(0x2F11);
    second = func_00288FB8(pair.ids[D_001A7B98 != 0]);
    func_00115DA8(buffer, format, label, second);
    func_0027FB40(0x100, 0xE1, color, buffer, -1);
}
