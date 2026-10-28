#include "common.h"


extern void func_0029F338(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_L08_003B2DB0(void *, void *, void *, int);
extern float func_002A7878(float, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, int, int, float);

/* family c459a266b43242d6 - 352 bytes, 2 placements
   levels/19_grelbin @0x00412F70, levels/8_tabora @0x0041E630

   Fills five output floats from two pinned tables and a resident flag word,
   then clamps the three still free outputs to [-1, 1]. */

extern float D_00189E20_14[];

extern int D_00138180[];

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TI128 __attribute__((mode(TI)));

/* A resident word: the same address and the same value in every program.  It is
   read as a symbol here (the `sda` declaration leaves the one- or two-instruction
   choice to the assembler) and as a literal in func_L08_003DB4A0, whose two
   conditional loads the literal address form is what reproduces. */
extern s32 D_001A79F0 __attribute__((sda));

/* shared callee, named by its catalogue row (08:003289D0, 19:00319288) */
extern void func_L00_00326048(void *, s32, s32, s32, float);

INCLUDE_ASM("asm/levels", func_L08_003D3928);

INCLUDE_ASM("asm/levels", func_L08_003D39F0);

/* One resident word, two states, and a 16-byte table entry: hands the entry to
   func_L00_00326048 with an alpha of 0x3D7A35E0. */
void func_L08_003D3EB8(u8 *a0)
{
    s32 v = *(s32 *)(a0 + 0x68);

    if (v == 0)
        return;
    func_L00_00326048(a0, v, 0x80AAAAD2, 0x80396464, 0.0610865355f);
}

INCLUDE_ASM("asm/levels", func_L08_003D4190);

void func_L08_003D4690(u8 *self)
{
    float direction[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float random[4] __attribute__((aligned(16)));
    u8 *target = *(u8 **)*(u32 *)(self + 0x68);
    int i;
    if (!target || target[0x20] == 0xFE || target[0x20] == 0xFD) {
        func_0029F338(self);
        return;
    }
    if ((self[0x60] & 2) && self[0x43])
        func_002A7470(self, 0, 0, 0);
    if (self[0xBC]) {
        self[0xBC] = 0;
        if (self[0x43] != 1) func_002A7470(self, 1, 0, 0);
        func_002AF000(direction, 1.0f, *(float *)(self+0xF8), -*(float *)(self+0xF4));
        func_0029FCC0(self, 0, position);
        func_L08_003B2DB0(self, position, direction, 0x5A);
        i = 4;
        do {
            *(TI128 *)random = 0;
            random[0] = func_002A7878(-1.0f, 1.0f);
            random[1] = func_002A7878(-1.0f, 1.0f);
            random[2] = func_002A7878(-1.0f, 1.0f);
            *(TI128 *)velocity = *(TI128 *)random;
            func_00282F20(velocity, velocity, func_00282DF0(direction)*0.65f);
            func_00282CC0(velocity, direction, velocity);
            func_00282F20(velocity, velocity, func_002A7878(0.050000004f, 0.10000001f));
            func_L04_00358AE8(position, velocity, 0x5F2F4F6F, func_002A7820(5,10), 50000.0f);
        } while (--i >= 0);
        func_00282F20(direction, direction, 0.008333334f);
        func_L04_00358AE8(position, direction, 0x2F4F7F7F, func_002A7820(4,7), 500000.0f);
    }
}

/* The same resident word, but the 8 case falls through to a 1/2 selector. */
s32 func_L08_003DB4E8(void)
{
    s32 v = D_001A79F0;
    s32 r = 1;

    if (v == 8)
        return 1;
    if (v == 0x13)
        r = 2;
    return r;
}

INCLUDE_ASM("asm/levels", func_L08_003DB518);

/* func_L08_003DB8E8 is matched in its own unit, L08_003DB8E8-g8.c. */


INCLUDE_ASM("asm/levels", func_L08_003E5BB8);




INCLUDE_ASM("asm/levels", func_L08_003F6610);

/* func_L08_0041E4F8 is defined in L08_0041E4F8-flags-g8.c. */

/* shared native body of family c459a266b43242d6 */
void func_L08_0041E630(float *a0, float *a1, float *a2, float *a3, float *p4)
{
    float f1;
    float f2;
    int v1;

    *a0 = -D_00189E20_14[2028];
    *a2 = -D_00189E20_14[2029];
    v1 = D_00138180[104];
    f2 = 0.0f;
    if (v1 & 0x40)
        f2 = 1.0f;
    f1 = (v1 & 0x20) ? (f2 - 1.0f) : f2;
    *a1 = f1;
    *a3 = *(float *)&D_00138180[75];
    v1 = D_00138180[104];
    f1 = 0.0f;
    if (v1 & 0x1)
        f1 = 1.0f;
    if (v1 & 0x2)
        f1 = f1 - 1.0f;
    *p4 = f1;
    if (*a0 > 1.0f)
        *a0 = 1.0f;
    else if (*a0 < -1.0f)
        *a0 = -1.0f;
    if (*a1 > 1.0f)
        *a1 = 1.0f;
    else if (*a1 < -1.0f)
        *a1 = -1.0f;
    if (*p4 > 1.0f)
        *p4 = 1.0f;
    else if (*p4 < -1.0f)
        *p4 = -1.0f;
}

INCLUDE_ASM("asm/levels", func_L08_0041E790);

INCLUDE_ASM("asm/levels", func_L08_0041EA88);

INCLUDE_ASM("asm/levels", func_L08_004207D0);

INCLUDE_ASM("asm/levels", func_L08_0042E678);

INCLUDE_ASM("asm/levels", func_L08_0042EF00);

/* func_L08_00435600 is defined in L08_00435600-helpers.c. */

/* Stores one 16-byte block through the pointer at 0x68 of the argument. */
void func_L08_004356A0(u8 *a0, void *a1)
{
    *(volatile TI128 *)*(u32 *)(a0 + 0x68) = *(TI128 *)a1;
}

/* func_L08_004356B8 is defined in L08_004356B8-g8.c. */


INCLUDE_ASM("asm/levels", func_L08_00435990);

INCLUDE_ASM("asm/levels", func_L08_00435A78);
