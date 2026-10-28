/* func_L00_003FEBA0 (w2 batch 3, 2026-10-28). New unit needed: -O2 -G0 -ffunction-sections -g (the -g line labels
   give the nop pair before div.s once `scale = 1.0f / length * 0.5f;` is its own statement). 436/444 bytes.
   Left: retail has bc1tl (ld $s0 in the likely slot) and `bgez; nop` at the loop end where this has bc1t and
   an `ld $s0` in the loop-end slot; the colour shift/or schedule and the order of `addiu $s2,5`/`lui $s7`.
   Callee names are the catalogue's (level 00 addresses 2EE238, 2EE178, 2EE108, 31A728, 31A7C0, 31A768,
   31A948, 334888). 1/150 is 0x3BDA740F. */
#include "common.h"

extern float func_00282DF0(float *v);
extern void func_00282D30(float *dst, float *src, float scale);
extern void func_00282CC0(float *dst, float *a, float *b);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_002A7A00(float *, float, float);
extern char *func_002BDCE8(float *, int, float *, int, float, float, float, float, int);

void func_L00_003FEBA0(int unused, float *pos, float *dir)
{
    float a[4];
    float b[4];
    float c[4];
    float length;
    float scale;
    float speed;
    int i;
    int shade;
    int color;
    char *particle;

    length = func_00282DF0(dir);
    if (length != 0.0f) {
        scale = 1.0f / length * 0.5f;
        func_00282D30(b, dir, scale);
        func_00282CC0(a, pos, b);
        for (i = 5; i >= 0; i--) {
            func_002A77E0(2);
            func_002A77E0(2);
            speed = func_002A7878(70000.0f, 150000.0f);
            shade = func_002A7820(10, 0x7F);
            func_002A7A00(c, 1.6666668e-05f, 0.0066666672937572f);
            color = shade | ((shade << 16) | ((shade << 8) | 0x7F000000));
            particle = func_002BDCE8(a, 0, c, color, 0.3f, 1.0f, 1.01f, speed, 1);
            if (particle != 0) {
                char *sub = particle + 0x20;
                *(short *)(particle + 0xA) = 0x78;
                *(int *)(sub + 4) = 2;
                *(unsigned char *)(sub + 0xA) = 0x7F;
                *(unsigned char *)(sub + 0xB) = *(unsigned char *)(particle + 0xA);
            }
        }
    }
}
