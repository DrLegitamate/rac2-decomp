/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections, in place in src/levels/shared/L00_002D7940.c
 * (that unit has no common.h; s32 comes from its own typedefs).
 * Retail: 468 bytes; compiled: 468 bytes.
 * Coverage: us: 0/27 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Draws the current caption of the level's caption table (index at +0x20 of the
 * control block at 0x1BC200, 40-byte entries at 0x1BC588): the text, six shaded bars
 * shrinking by 5/6 below it, then the text again on top.
 *
 * Control flow, calls, the 5/6 division with its zero check and the per-use reloads of
 * the screen width (an incomplete sda array, as retail expands it) match. Register
 * allocation differs throughout (about 40 lines in level 00): retail keeps the control
 * block in $s5, 40 in $s6, the table in $s1 and table + 0x14 in $s0, and builds the
 * 0xFFFFFFFF colour as addiu -1 / dsrl32 where cc1 uses lui 0xFFFF / dsrl32.
 * The second draw as an inlined helper (with its own base pointers) is what made the
 * final draw rebuild the addresses from their high parts as retail does.
 * Tried: the first draw through the helper too (460 bytes); the y reads through an
 * int pointer at table + 0x14 (this version); both together (464).
 */

typedef int s32;

/* One 40-byte entry of the level's caption table. */
typedef struct {
    s32 key;
    char pad04[0xC];
    s32 width;
    s32 y;
    char pad18[0x10];
} Caption_2E3520;

extern char D_L00_001BC200[];
extern Caption_2E3520 D_L00_001BC588[];
extern s32 D_001A7340[] __attribute__((sda));

extern s32 func_L00_002E36F8(s32 key);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern void func_00280190(void *, unsigned long, char *, int);
extern void func_0027DE50(int, int, int, int, unsigned long);

static __inline__ void func_L00_002E3520_draw(unsigned short *layout, char *text)
{
    char *ctl = D_L00_001BC200;
    Caption_2E3520 *cap = &D_L00_001BC588[*(short *)(ctl + 0x20)];

    func_002802E0(layout, 0, cap->y, 0, D_001A7340[0], D_001A7340[0] / 2, cap->width, 0x12, 1);
    func_00280190(layout, 0xFFFFFFFFUL, text, -1);
}

void func_L00_002E3520(void)
{
    unsigned short layout[12];
    char *ctl = D_L00_001BC200;
    Caption_2E3520 *caps = D_L00_001BC588;
    char *text;
    s32 top;
    s32 h;
    s32 i;
    s32 *ys = &D_L00_001BC588[0].y;

    text = (char *)func_L00_002E36F8(caps[*(short *)(ctl + 0x20)].key);
    if (text == 0)
        return;
    func_002802E0(layout, 0, ys[*(short *)(ctl + 0x20) * 10], 0, D_001A7340[0],
                  D_001A7340[0] / 2, caps[*(short *)(ctl + 0x20)].width, 0x12, 1);
    func_00280190(layout, 0xFFFFFFFFUL, text, -1);
    top = ys[*(short *)(ctl + 0x20) * 10] - 2;
    h = top - 2;
    for (i = 5; i >= 0; i--) {
        func_0027DE50(top - h, top, -D_001A7340[0], D_001A7340[0] * 2, 0x18000000);
        h = h * 5 / 6;
    }
    func_L00_002E3520_draw(layout, text);
}
