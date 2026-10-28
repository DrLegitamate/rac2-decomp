/* Near miss (W1, 28 October 2026): 516/516 B, 6 lines off at the 27 places (was 16; a seventh,
   `addiu $s3,$v0,0x10` vs the relocated form, is only the symbol addend). Profile
   `-O2 -G8 -ffunction-sections`.
   Fixed this round: func_00277258 declared with the float second (void *, float, void *, void *),
   which puts `mov.s $f12` before the `daddu $a1` as retail; the loop-tail copy through qcopy(),
   which keeps `i++` after the 16-byte copy; the sda constant read into its own local before the
   `sh` (`scale = D_L00_001B14D0`), which puts 1.0 in $f3, the constant in $f4 and the hero pointer
   in $a0 as retail; `int gotA, gotB, i` declared in that order (s4/s5 as retail).
   Left: retail issues the sda constant load after the `sh $v0,0x38($s0)` and `addiu $s1,$sp,0x10`
   (right before the hero pointer load), here it is issued right after the first call. Moving the
   statement after the `sh` brings back the old $f3/$f4 and $v1 allocation (10 lines).
   D_L00_001B8E10 and D_L00_001B8E20 are one object (retail keeps &D+0x10 in $s3 and reads the hero
   pointer as -0x10($s3)); the loop is `while (i < 3)` with i++ at the end and
   `else if (!B) break; else gotB = 1;`. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern char D_L00_001B8E10[];
extern char D_L00_001BF220_1[];
extern char D_L00_001BF230[];
extern float D_L00_001B14D0 __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern int func_L00_00420388(void *, float);
extern int func_00277258(void *, float, void *, void *);
extern void *func_L00_004237C8(char *, void *, int, int);

/* Picks the best of three blends of the owner's block. */
void *func_L00_004239A8(char *a0)
{
    char *base = *(char **)(a0 + 0x70);
    char *st = base + 0x1F0;
    void *mid = base + 0x60;
    char *end = base + 0x160;
    TI128 v, w;
    void *q;
    void *tgt;
    void *ret;
    float f20;
    float scale;
    float d;
    int gotA = 0;
    int gotB = 0;
    int i = 0;
    char *cam = D_L00_001B8E10 + 0x10;

    func_00282CC0(&v, base + 0xB0, end);
    scale = D_L00_001B14D0;
    *(short *)(st + 0x38) = 2;
    q = *(void **)(*(char **)D_L00_001B8E10 + 0x70);
    tgt = *(void **)(st + 0x48);
    f20 = scale + *(float *)((char *)q + 0x234) * *(float *)((char *)q + 0x22C) *
              (*(float *)((char *)q + 0x230) - 1.0f);
    while (i < 3) {
        if (func_L00_00420388(&v, f20))
            gotA = 1;
        else if (!func_00277258(&v, f20, tgt, *(void **)(cam + 0xC4)))
            break;
        else
            gotB = 1;
        if (*(short *)(st + 0x38) != 0) {
            func_00282CF0(&w, D_L00_001BF220_1, &v);
            func_00282F20(&w, &w, 1.0f);
            d = func_00282DB0(cam + 0x30, &w);
            if (d > 0.75f)
                *(short *)(st + 0x38) = 1;
            else if (d < -0.75f)
                *(short *)(st + 0x38) = -1;
            else
                *(short *)(st + 0x38) = 0;
        }
        qcopy(&v, D_L00_001BF230);
        i++;
    }
    ret = func_L00_004237C8(a0, &v, gotA, gotB);
    func_00282CC0(st + 0x20, (char *)mid + 0x50, end);
    if (*(short *)(st + 0x38) == 2)
        *(short *)(st + 0x38) = 0;
    return ret;
}
