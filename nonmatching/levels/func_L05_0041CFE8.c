/*
 func_L05_0041CFE8 (424 bytes, 1 place) - appended to L05_00314E28-g8.c (-G8); size exact (w5, 2026-10-28), 8 masked lines differ.
 The loop is `if (high[0x10] == obj) { body }` plus the three pointer increments (no break), float constants as literals in the calls (loop.c hoists them to f20/f21),
 prologue `t = D; low = t + 0x10; high = t + 0x30; base = t;`, counter `unsigned int` (a signed counter is reversed to a count-down by loop.c).
 Open: retail's counter is a signed up-counter (slti); in the second call retail loads `lw a3,gp` after `lui a2`.
 */
extern char D_L05_002659E0[];
extern char D_L05_00268E20[];
extern int D_L05_001B0F48 __attribute__((sda));
extern int D_L05_001B1340 __attribute__((sda));
extern float func_002A7940(void);
extern void func_00281EB8(void *, unsigned int, unsigned int, int, float, float, float);
extern void func_L05_00416698(void *, void *, unsigned int, int, float);
extern void func_L05_0041D218(void *, void *, unsigned int, int, float);

void func_L05_0041CFE8(char *obj)
{
    char *t = D_L05_00268E20;
    char *low = t + 0x10;
    char *high = t + 0x30;
    char *base = t;
    unsigned int i;

    for (i = 0; i < 0x80; i++) {
        float v;

        if (*(char **)(high + 0x10) == obj) {
            func_L05_0041D218(base, low, 0x807F7F7F, D_L05_001B1340, 0.025f);
            func_L05_0041D218(base, low, 0x60008000, D_L05_001B1340, 0.05f);
            v = func_002A7940();
            func_00281EB8(high, 0x31, 0x60008000, 1, 1.35f, 0.35f, v);
            v = func_002A7940();
            func_00281EB8(high, 0x31, 0x807F7F7F, 1, 1.0f, 0.35f, v);
            v = func_002A7940();
            func_00281EB8(low, 0x31, 0x60008000, 1, 0.125f, 0.08f, v);
            v = func_002A7940();
            func_00281EB8(low, 0x31, 0x807F7F7F, 1, 0.08f, 0.08f, v);
        }
        base += 0x50;
        low += 0x50;
        high += 0x50;
    }
}
