/* func_002D4948: near miss, 1,208 of 1,220 bytes at its 28 places (src/game/002D3390-g8.c).

   Everything up to the end of the line-building calls and the whole styling loop
   matches. Two differences remain:
   - retail rematerialises the kind constants 3 and 4 (`addiu v1,3`/`addiu v0,4`
     before each `sb`); cc1 keeps each in a callee-saved register (s1/s2) across the
     calls, two words fewer. 8 and 1 are held in s5/s4 in both. Separating `n++`,
     indexing the lines as an array and other spellings of the stores do not change it.
   - the preset search: writing it with the global D_001ABA74 as the counter gives
     retail's unreduced `mult` loop (loop.c's load_mems keeps the global in a register
     and stores it once at the end) and its `nop` before the head. A `for` puts the
     index-0 test before the hoisted invariants and uses no copy register (retail
     hoists flags/table/table+4/20 above the peeled test and keeps i in a2 and a copy
     in a3); `do`/`while` forms hoist correctly but do not peel the index-0 test.
   Next: find the loop shape that both peels the first test and hoists above it, and
   what makes cc1 rematerialise constants 3/4 (a register-pressure difference earlier
   in the function is a candidate). */

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
    char reserved138[0x94];
    char *items;
    int count;
    int timer;
} CallbackState;

extern CallbackState D_001F2840;

/* A 256-byte menu line. */
typedef struct {
    char pad00[0x20];
    unsigned char b20;
    char pad21[2];
    unsigned char b23;
    char pad24[8];
    float alpha;
    unsigned char b30;
    unsigned char b31;
    short width;
    unsigned short style;
    char pad36[0x62];
    int w98;
    char pad9C[0xE];
    short text;
    char padAC[0x10];
    unsigned char kind;
    char padBD[0x33];
    float colour[3];
    char padFC[4];
} MenuLine_002D4948;

typedef struct {
    unsigned int mask;
    unsigned int value;
    int data[3];
} OptionPreset_002D4948;

typedef struct {
    char pad0[0x3C];
    int w3C;
} Layout_002D4948;

extern unsigned int D_001A7AF0;
/* Text ids per setting value. */
extern short D_001A8C28[4];
extern short D_001A8C30[4];
extern short D_001A8C38[4];
extern short D_001A8C40[4];
extern short D_001A8C48[4];
extern short D_001A8C50[4];
extern short D_001A8C58[4];

extern OptionPreset_002D4948 D_0026CFD8[21];
extern Layout_002D4948 D_0025D478;
extern int D_001ABA74 __attribute__((sda));
extern char *func_002DE550(int);
extern void func_0029F0C8(MenuLine_002D4948 *, int);
extern void func_002A0468(MenuLine_002D4948 *, int, int, int, int);
extern int func_002A0F48(MenuLine_002D4948 *);

/* Builds the options menu from the settings word D_001A7AF0, then finds the preset
   matching the settings. */
int func_002D4948(void)
{
    unsigned int settings = D_001A7AF0;
    int a = (settings >> 2) & 3;
    int b = (settings >> 4) & 1;
    int c = (settings >> 6) & 1;
    int d = (settings >> 7) & 3;
    int e = (settings >> 9) & 1;
    int f = (settings >> 10) & 3;
    int g = (settings >> 14) & 3;
    MenuLine_002D4948 *line;
    int n;
    int i;

    D_001F2840.items = func_002DE550(1);
    line = (MenuLine_002D4948 *)D_001F2840.items;
    func_0029F0C8(line, 0xD54);
    line->kind = 9;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x100);
    func_0029F0C8(line, D_001A8C28[a]);
    line->kind = 8;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x200);
    func_0029F0C8(line, D_001A8C28[a]);
    line->kind = 8;
    line->style |= 0x8000;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x300);
    func_0029F0C8(line, D_001A8C30[b]);
    line->kind = 0;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x400);
    func_0029F0C8(line, D_001A8C38[c]);
    line->kind = 1;
    line = (MenuLine_002D4948 *)(D_001F2840.items + 0x500);
    func_0029F0C8(line, D_001A8C38[c]);
    line->kind = 1;
    line->style |= 0x8000;
    n = 6;
    if (D_001A8C40[d] != 0) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + 0x600);
        n = 7;
        func_0029F0C8(line, D_001A8C40[d]);
        line->kind = 2;
    }
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C48[e]);
    line->kind = 3;
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C48[e]);
    line->kind = 3;
    line->style |= 0x8000;
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C50[f]);
    line->kind = 4;
    line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
    func_0029F0C8(line, D_001A8C50[f]);
    line->kind = 4;
    line->style |= 0x8000;
    if ((D_001A7AF0 >> 12) & 1) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
        func_0029F0C8(line, 0x10E2);
        line->kind = 5;
    }
    if ((D_001A7AF0 >> 13) & 1) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
        func_0029F0C8(line, 0x10E4);
        line->kind = 6;
    }
    if (g != 0) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + n++ * 0x100);
        func_0029F0C8(line, D_001A8C58[g]);
        line->kind = 7;
    }
    for (i = 0; i < n; i++) {
        line = (MenuLine_002D4948 *)(D_001F2840.items + i * 0x100);
        line->width = 0x1FF;
        func_002A0468(line, 0x202020, 14, 14, 0);
        line->width = 0xFF;
        line->b31 = 1;
        line->b30 = 0xFF;
        if (line->text == 0x10E3) {
            line->b23 = 0xFF;
        }
        line->b20 = 0;
        line->w98 = 0;
        line->alpha = 1.0f;
        line->colour[0] = 0.211843f;
        line->colour[1] = 0.33421f;
        line->colour[2] = -2.782353f;
        func_002A0F48(line);
    }
    D_001F2840.count = n;
    D_001F2840.timer = 300;
    for (D_001ABA74 = 0; D_001ABA74 < 21; D_001ABA74++) {
        if ((D_001A7AF0 & D_0026CFD8[D_001ABA74].mask) == D_0026CFD8[D_001ABA74].value) {
            break;
        }
    }
    D_0025D478.w3C = -0x244;
    return 0;
}
