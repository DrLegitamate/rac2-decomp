/* func_L02_003F52B0 (w2 batch 3, 2026-10-28). Unit src/levels/02_maktar_nebula/L02_003F52B0-qcopy.c,
   profile -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier (the barrier flag is new since the
   older notes). 220/220 bytes, 4 differing lines, all the case-0 setup:
     retail: addiu $a1,$v1,0xB0 ; swc1 $f0,0xB4 ; lui $a0,0x1B ; addiu $a0,$a0,0x3210 ; swc1 $f1,0xB8 ; swc1 $f1,0xB0 ; swc1 $f20,0xBC ; lq ; sq
     this:   lui $a0 ; swc1 B4 ; addiu $a1 ; swc1 B8 ; addiu $a0 ; swc1 B0 ; swc1 BC
   All 720 orders of {the four stores, src=, dst=} with qcopy(dst, src) last were compiled; 4 is the best. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* Prefix view of the effect-position field; not a complete global layout. */
typedef struct { char pad[0xB0]; float effect_position[4]; } EffectPositionView;
extern EffectPositionView D_00189E20;
extern char D_L02_001B3210[];
extern char *D_L02_001AD410 __attribute__((sda));
extern void func_L02_003F5390(char *);
extern void func_L02_003F54D8(char *);
extern void func_L02_003F56C0(char *);
extern void func_L02_003F5710(char *);
extern void func_002833B8(char *, float);
extern void func_002A7750(u8 *, s32, s32);

void func_L02_003F52B0(char *arg0) {
    switch (*(u8 *)(arg0 + 0x20)) {
    case 0: {
        EffectPositionView *g = &D_00189E20;

        float *src;
        char *dst;
        g->effect_position[1] = 200.0f;
        g->effect_position[0] = 500.0f;
        g->effect_position[2] = 500.0f;
        g->effect_position[3] = 1.0f;
        src = g->effect_position;
        dst = D_L02_001B3210;
        qcopy(dst, src);
        *(u8 *)(arg0 + 0x30) = 0xFF;
        func_L02_003F5390(arg0);
        func_002833B8(D_L02_001AD410 + 0x40, 1.0f);
        func_002A7750(arg0, 1, -1);
        break;
    }
    case 1:
        func_L02_003F54D8(arg0);
        func_L02_003F56C0(arg0);
        func_L02_003F5710(arg0);
        break;
    }
}
