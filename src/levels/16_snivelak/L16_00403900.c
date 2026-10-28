#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_L16_00410CC0(u8 *, u8 *);

extern void func_2E74B8(void *, void *, void *);

extern float func_2E7590(void *, void *);

extern s32 func_313EA0(s32);

extern void func_30AD48(void *, s32, void *);

extern float func_313F38(float, float);

extern void func_41F1F0(void *, void *, void *, s32, float, float);

extern void func_00282DD8(void *, void *, void *);

extern void func_002ACE78(void *, void *, float);

extern void func_002A7750(void *, s32, s32);

extern void func_0029FCC0(void *, s32, void *);

extern void func_0029FC20(void *, s32, void *);

extern void func_002A0F48(void *);

extern void func_00283678(void *, void *);

extern void func_002A7470(void *, s32, s32, s32);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282E48(void *, void *);

extern float func_00282E80(void *, void *);

extern int func_L07_00321D68(void *, void *);

extern void func_L02_00327350(s32, s32);

extern void func_L01_00323310(s32, s32);
extern u8 *D_L16_001B2C0C[] __attribute__((sda));
extern u8 D_0013963B;

extern void func_L00_003294F0(void *, s32);

extern void func_002DF3F8(void *, void *);

extern void func_0029F338(void *);

extern void func_0029B3E0(s32, s32);

extern void func_L16_00412C58(u8 *, s32, s32);
extern void func_L16_00412BA8(u8 *, s32);

extern void func_L16_004117A8(u8 *);

extern void func_L16_00411F80(u8 *, s32);

extern void func_L16_0041ECF8(void *, float);

extern void func_002AD7B8(s32);

extern void func_00282948(void *);

extern void func_L16_004050D8(u8 *);

extern void func_0029F978(u8 *, s32, void *);

extern void func_00283898(void *, s32, float);

extern float func_00283BE0(float, float);

extern void func_002A8C00(void *, u8 *, s32, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern float func_00282C48(float);

extern void func_002A8E20(s32, void *);

INCLUDE_ASM("asm/levels", func_L16_00403900);

/* func_L16_00404A60 is in the sibling file L16_00403900-g8.c: its body
   reaches the level's small-data floats through $gp. */

extern u8 *D_L16_001FE7C0[];

/* Steers the object toward the next point of its path (the state's table and cursor at
   0x294/0x2A4); advances the cursor once within half a unit, and returns 1 when the path is done. */
s32 func_L16_00404E40(u8 *moby)
{
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = D_L16_001FE7C0[*(s32 *)(state + 0x294)];

    if (*(s32 *)(state + 0x2A4) >= *(s32 *)path)
        return 1;
    qcopy(point, path + 16 + *(s32 *)(state + 0x2A4) * 16);
    func_00282CF0(step, point, moby + 0x10);
    func_00282F20(step, step, 0.20000002f);
    func_L07_00321D68(moby, step);
    if (*(s32 *)(state + 0x2AC) != 0) {
        if (func_00282E48(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    } else {
        if (func_00282E80(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    }
    return 0;
}

/* func_L16_00404F50 is defined in L16_00404F50.c. */

/* func_L16_004050D8 is defined in L16_004050D8-helpers.c. */

/* func_L16_00405488 is in L16_00405488-g8.c. */


INCLUDE_ASM("asm/levels", func_L16_0040C840);

INCLUDE_ASM("asm/levels", func_L16_0040CD88);

/* func_L16_0040CF98 is defined in L16_00403900-g8.c. */

extern u16 *D_L16_001FB660[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern s32 D_L16_001B2B38[] __attribute__((sda));

/* Sets a flag word in the state record (+0x68) of every entity of the object's group, stopping
   at the first id with no entity: +0x244 for class 0xF35, +0x24C for class 0xEA3. */
void func_L16_0040D188(u8 *arg0)
{
    u16 *p;
    u8 *e;

    if (arg0[0x21] == 0xFF)
        return;
    p = D_L16_001FB660[arg0[0x21]];
    while (arg0[0x21] != 0xFF && arg0[0x21] <= D_L16_001B2B38[0] && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L16_001FB660[arg0[0x21]])) {
        e = D_L16_001B2B1C[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == 0xF35)
            *(s32 *)(*(u8 **)(e + 0x68) + 0x244) = 1;
        else if (*(s16 *)(e + 0xAA) == 0xEA3)
            *(s32 *)(*(u8 **)(e + 0x68) + 0x24C) = 1;
        p++;
    }
}

INCLUDE_ASM("asm/levels", func_L16_0040D258);

INCLUDE_ASM("asm/levels", func_L16_0040D4E8);

INCLUDE_ASM("asm/levels", func_L16_0040DAE0);


INCLUDE_ASM("asm/levels", func_L16_00410618);

/* func_L16_00410B88 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

/* Copies the measured 32-bit field pair of the handle reached at 0x68 onto the second
   pair after the helper has prepared the object's second half. */
void func_L16_00410C80(u8 *arg)
{
    u8 *s0;

    s0 = *(u8 **)(arg + 0x68);
    func_L16_00410CC0(arg, arg + 0x10);
    *(s32 *)(s0 + 0x220) = *(s32 *)(s0 + 0x1F4);
    *(s32 *)(s0 + 0x224) = *(s32 *)(s0 + 0x1F8);
}

INCLUDE_ASM("asm/levels", func_L16_00410CC0);

INCLUDE_ASM("asm/levels", func_L16_00410E40);

INCLUDE_ASM("asm/levels", func_L16_00410FA8);

/* func_L16_004110D0 is compiled from L16_004110D0-g8.c. */

INCLUDE_ASM("asm/levels", func_L16_00411368);

/* func_L16_00411480 is defined in L16_00403900-g8.c. */

/* func_L16_00411600 is in L16_00411600-qcopy.c. */

/* Routes one transition request to the handle itself or to its first child, depending on
   the state word and on which of the two animation slots is current. */
void func_L16_004116C8(u8 *arg0, s32 arg1, s32 duration, float f)
{
    u8 *s2;

    s2 = *(u8 **)(arg0 + 0x68);
    if (*(s32 *)(s2 + 0x26C) == 0) {
        if (*(u8 *)(arg0 + 0x43) != arg1)
            func_002A7470(arg0, arg1, (s32)f, duration);
    } else {
        if (*(u8 *)(arg0 + 0x43) != 0x16)
            func_002A7470(arg0, 0x16, (s32)f, duration);
        if (arg1 == 0xA)
            arg1 = 0x16;
    }
    if (arg1 < 0x11)
        func_002A7470(*(u8 **)(s2 + 0x1F0), arg1, (s32)f, duration);
    else
        func_002A7470(*(u8 **)(s2 + 0x1F0), 0, (s32)f, duration);
}

INCLUDE_ASM("asm/levels", func_L16_004117A8);

/* func_L16_00411900 is defined in L16_00411900-g8.c. */

/* func_L16_00411B40 is defined in L16_00411B40-g16.c. */

/* func_L16_00411D00 is defined in L16_00411D00-g8.c. */

/* Builds a 16-byte query record from the game speed and the handle's byte field and
   hands it with a prepared buffer to the generic path. */
INCLUDE_ASM("asm/levels", func_L16_00411F80);

INCLUDE_ASM("asm/levels", func_L16_00412560);

/* func_L16_00412AF0 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

INCLUDE_ASM("asm/levels", func_L16_00412BA8);

/* Walks a rotating candidate index over the measured byte table until a free slot
   is found, arms it, and clears the whole window when none is. */
void func_L16_00412C58(u8 *arg, s32 start, s32 end)
{
    u8 *s3;
    s32 n;
    s32 i;
    s32 k;

    s3 = *(u8 **)(arg + 0x68);
    if (end < start)
        return;
    n = end - start + 1;
    k = func_313EA0(n);
    for (i = 0; i < n; i++) {
        u8 *tbl = s3 + 0x310;

        if (tbl[start + k] == 0) {
            func_L16_00412BA8(arg, start + k);
            return;
        }
        k = (k + 1) % n;
    }
    for (i = 0; i < n; i++)
        s3[0x310 + start + i] = 0;
    func_L16_00412BA8(arg, start + k);
}

/* Finishes the pending entry (its two saved vectors are copied back), then resets the
   level's handles. */
void func_L16_00412D48(u8 *arg)
{
    u8 *s0;
    s32 a0;
    u8 *tbl;

    s0 = *(u8 **)(arg + 0x68);
    if (*(s32 *)(s0 + 0x1BC) != 0) {
        s32 h = *(s32 *)(s0 + 0x1B0);
        s32 m = *(s32 *)(s0 + 0x1B4);

        *(s32 *)(s0 + 0x1BC) = 0;
        func_L02_00327350(h, m);
        a0 = *(s32 *)(s0 + 0x1B8) << 7;
        tbl = D_L16_001B2C0C[0];
        qcopy(arg + 0x10, tbl + 0x30 + a0);
        qcopy(arg + 0xF0, tbl + 0x70 + a0);
        func_L01_00323310(*(s32 *)(s0 + 0x1A4), -1);
    } else {
        func_L01_00323310(*(s32 *)(s0 + 0x1A4), *(s32 *)(s0 + 0x1AC));
    }
    D_0013963B = 1;
    func_L16_004117A8(arg);
    func_L16_00411F80(arg, 1);
    func_L00_003294F0(D_L16_001B2B1C[0] + (*(s32 *)(s0 + 0x190) << 8), 1);
    func_002DF3F8(D_L16_001B2C0C[0] + (*(s32 *)(s0 + 0x198) << 7) + 0x30,
                  D_L16_001B2C0C[0] + (*(s32 *)(s0 + 0x198) << 7) + 0x70);
    func_L16_00412C58(arg, 0, 2);
    func_0029B3E0(0, -1);
    func_002A7750(arg, 2, 1);
}

/* Level teardown: releases the handles the level state holds. */
extern char D_00189EA0[];

void func_L16_00412E70(char *arg0) {
    char *s0 = *(char **)(arg0 + 0x68);

    D_0013963B = 2;
    func_L16_0041ECF8(D_L16_001B2B1C[0] + (*(s32 *)(s0 + 0x190) << 8), 0.0f);
    func_L02_00327350(*(s32 *)(s0 + 0x188), *(s32 *)(s0 + 0x18C));
    func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
    func_002AD7B8(0x11);
    if (*(s32 *)(s0 + 0x1F0) != 0)
        func_0029F338((void *)*(s32 *)(s0 + 0x1F0));
    if (*(s32 *)(s0 + 0x238) != 0)
        func_0029F338((void *)*(s32 *)(s0 + 0x238));
    if (*(s32 *)(s0 + 0x23C) != 0)
        func_0029F338((void *)*(s32 *)(s0 + 0x23C));
    func_L01_00323310(*(s32 *)(s0 + 0x1A0), -1);
    func_0029B3E0(0, -1);
    func_0029F338(arg0);
}


/* func_L16_00412F48 is in L16_00412F48-g8.c. */

/* func_L16_004130B0 is in L16_004130B0-qcopy.c. */

INCLUDE_ASM("asm/levels", func_L16_004133B0);

/* Prepares a 16-byte record from the handle and reports one when the queried value
   does not exceed zero. */
s32 func_L16_00413638(u8 *arg)
{
    s32 buf[4];
    u8 *s0;

    s0 = *(u8 **)(arg + 0x68);
    func_2E74B8(buf, s0 + 0x10, arg + 0x10);
    if (func_2E7590(s0, buf) <= 0.0f)
        return 1;
    return 0;
}

/* func_L16_00413700 is in L16_00413700-qcopy.c. */

/* func_L16_00413D10 is in L16_00413D10-g8.c. */
