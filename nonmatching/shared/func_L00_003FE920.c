/* func_L00_003FE920 (w2 batch 3, 2026-10-28). Profile -O2 -G8 -ffunction-sections -g -frac2-qcopy -frac2-qcopy-barrier
   (new unit). 412/420 bytes (was 400/420). Hero as a union view (HERO macro, a local `h` for the first group
   so the high half stays in $s5 for the later reread), byte table D_00139581 (the old name D_0013957F was
   wrong: retail reads 0x139581). Left: retail has the `nop nop` before `div.s` even with -g, saves the
   obj/hero pair the other way round (s0 = hero, s1 = obj), puts q at sp+0 and r at sp+0x10 (here q at
   sp+0x10 whatever the declaration order), and builds the byte-table address as `lui; lbu lo(reg)` with
   a second register. */
#include "common.h"


typedef struct {
    u8 pad00[0x50];
    float scale;
    u8 pad54[0xE0 - 0x54];
} TableEntry_L00_003FE920;

extern u8 D_00139581[];
extern TableEntry_L00_003FE920 D_L00_00262570[];
typedef int HeroQ __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern u8 D_00189E20[];
#define HERO ((Hero *)D_00189E20)
extern u8 D_L00_001B9010[];
extern int D_001B0C0C __attribute__((sda));
extern float D_001B0C10 __attribute__((sda));

extern void func_00282F20(void *, void *, float);
extern void func_L00_0037FA90(void *, void *, float, float, float);
extern void func_L00_0032A1A8(void *, void *, void *, float);
extern float func_00283CE0(int);
extern float func_00283B98(float, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);

void func_L00_003FE920(u8 *obj, u8 *out, int mode, u8 *flag)
{
    float f20;
    float f2;
    float q[4] __attribute__((aligned(16)));
    float r[4] __attribute__((aligned(16)));
    u8 *src;
    Hero *h = HERO;

    f20 = D_L00_00262570[D_00139581[0]].scale * 0.016666668f;
    if (h->h[0x24EC / 2] == 1) {
        func_00282F20(out, obj + 0xD0, -f20);
        src = obj + 0xC0;
    } else {
        func_00282F20(out, &h->b[0x760], f20);
        src = &h->b[0x750];
    }
    qcopy(q, src);
    if (h->i[0x1500 / 4] != 0) {
        func_L00_0037FA90(out, flag, f20, 32.0f, 0.6981318f);
    }
    qcopy(q, D_L00_001B9010);
    if (HERO->ptr[0xBF8 / 4] != 0) {
        func_L00_0032A1A8(HERO->ptr[0xBF8 / 4], flag, out, f20);
    }
    f20 = func_00283CE0(mode);
    f20 = f20 / func_00283CE0(D_001B0C0C - 1);
    f2 = D_001B0C10 * 0.017453294f;
    if (mode != 2) {
        float a = func_00283B98(-f2, (f2 + f2) * f20);
        func_002AB668(r, q, a);
        func_002ACDE8(out, out, r);
    }
}
