#include "include_asm.h"

/* Functions of 0032EB28.c whose retail body reaches its resident object through $gp
   (`addiu $v0,$gp,-0x16C8`). A file named *-g8.c is built with -G8 (config/cflags.txt),
   which is what makes the compiler emit that form. */

extern int D_001AD928 __attribute__((sda));
extern int D_001AD908 __attribute__((sda));
extern void F7242f0a4_FUN_00335AE0(void *);

void func_00335D80(void *object) {
    *(void **)object = &D_001AD928;
    F7242f0a4_FUN_00335AE0(object);
}

void func_00335DA0(void *object) {
    *(void **)object = &D_001AD908;
    F7242f0a4_FUN_00335AE0(object);
}

extern float D_L00_001B2708 __attribute__((sda));
extern void func_00300A00(int, int, float, float, float, float, float);

void func_00336320(char *object)
{
    float *first;
    float *second;
    if (**(float **)(object + 0x10) == 0.0f)
        return;
    if (*(int *)(object + 0x40) == 0)
        return;
    first = *(float **)object;
    second = *(float **)(object + 4);
    func_00300A00(*(int *)(object + 0x40), **(int **)(object + 0xC), first[0], first[1],
                 second[0], second[1] * D_L00_001B2708, **(float **)(object + 0x38));
}

extern void func_002FC808(void);
extern void func_00330EC0(void *);
extern void func_002FDBD8(void *, void *, int, float);
extern float ref_L00_00330E48_00 __attribute__((sda));
void func_00330E48(char *owner)
{
    char *data;
    func_002FC808();
    data = *(char **)(owner + 0x68);
    if (*(float *)(data + 0x64) < ref_L00_00330E48_00)
        func_00330EC0(owner);
    if (*(int *)(data + 0x78))
        func_002FDBD8(data + 0x30, data + 0x40, 0, 0.2f);
}

extern int D_001B1688;
extern char *D_001B1B68;
extern float ref_L00_00330BC0_00 __attribute__((sda));
extern float func_00282E48(void *, void *);
extern void func_00302440(void *, void *);

void func_00330BC0(char *object)
{
    char *cursor;
    if (D_001B1688 & 1) {
        cursor = D_001B1B68;
        while (cursor) {
            int kind = *(unsigned char *)(cursor + 0x20);
            if (kind == 0xfe) return;
            if (kind == 0xfd) return;
            if (cursor && *(char **)(cursor + 0x24) &&
                *(short *)(*(char **)(cursor + 0x24) + 0x46) == 0x13) {
                if (func_00282E48(cursor + 0x10, object + 0x10) < ref_L00_00330BC0_00)
                    func_00302440(cursor, object);
            }
            cursor = *(char **)(cursor + 0x28);
        }
    }
}

extern float D_001B284C;
/* The retail reaches 0x1B284C twice: through lui/lwc1 (D_001B284C) and through
   $gp+0x385C (ref_L00_0032FEA8_00).  The compiler picks one form per symbol. */
extern float ref_L00_0032FEA8_00 __attribute__((sda));
extern int D_001B2850;
extern float D_001B2854;
extern float D_001B09A0 __attribute__((sda));
extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_0032FFD8(void *);
extern void func_00330150(void *);
extern void func_003304D8(void *);

void func_0032FEA8(char *object)
{
    char *data = *(char **)(object + 0x68);
    float value;
    int flag;
    char buffer[16];

    if (D_001B284C != 0.0f && D_001B2850 != 0) {
        value = *(float *)(data + 0x58) + D_001B284C * (1.0f / 120.0f);
        *(float *)(data + 0x58) = value;
        if (func_00282C48(value) > D_001B09A0 * (1.0f / 60.0f))
            *(float *)(data + 0x58) = D_001B09A0 * ref_L00_0032FEA8_00 * (1.0f / 60.0f);
    } else {
        *(float *)(data + 0x58) = *(float *)(data + 0x58) * 0.85f;
    }

    flag = D_001B2850;
    value = *(float *)(data + 0x58) * 25.0f;
    *(float *)(object + 0x48) = value;
    if (flag == 0)
        *(float *)(object + 0x48) = value + (D_001B2854 + D_001B2854);

    func_00282F20(buffer, object + 0xC0, *(float *)(data + 0x58));
    func_00282CC0(object + 0x10, object + 0x10, buffer);
    func_0032FFD8(object);
    func_00330150(object);
    func_003304D8(object);
}

/* func_00335DC0: the retail reaches its three globals through $gp (the int at $gp+0x3710 and
   the float at $gp+0x3718) and through lui/addiu (the float at 0x1B2704), so the unit is the
   -G8 one.  The three live in the level's data, at an address that differs from level to
   level, so they are named without an address. */
extern int ref_L00_00335DC0_00 __attribute__((sda));
extern float ref_L00_00335DC0_01;
extern float ref_L00_00335DC0_02 __attribute__((sda));

/* func_00331718 reaches four of its globals through $gp, so it belongs in this unit.
   The float at the same address is reached twice under two names: once through $gp
   (ref_L00_00331718_03) and once through lui/lwc1 (ref_L00_00331718_04).

   It needs the unit ASSEMBLED with -Wa,-G32: the retail reaches the base of its two
   32-byte tables through $gp (addiu $a0,$gp,0x1940), and the assembler's relaxation of
   `la` into addiu $reg,$gp,off fires only for symbols of at most its -G threshold, which
   is 8 by default.  With -Wa,-G32 the function is the retail's 200 bytes, word for word;
   without it it is 208 bytes (the two lui/addiu pairs for the table addresses).
   config/cflags.txt needs:
       src/game/0032EB28-g8.c	-O2 -G8 -ffunction-sections -Wa,-G32
   The flag is safe for the rest of this unit: its other functions take the address of
   4-byte sda symbols, which the retail reaches through $gp as well. */
extern int *ref_L00_00331718_00 __attribute__((sda));
extern int ref_L00_00331718_01[8] __attribute__((sda));
extern float ref_L00_00331718_02[8] __attribute__((sda));
extern float ref_L00_00331718_03 __attribute__((sda));
extern float ref_L00_00331718_04;

extern float func_0029F530(int *);
extern void func_002E5CF8(int, int, int *);

void func_00331718(void)
{
    float value;
    float threshold;
    float diff;
    float old;
    int i;

    if (ref_L00_00331718_00 == 0)
        return;
    value = func_0029F530(ref_L00_00331718_00);
    for (i = 0; i < 8; i++) {
        threshold = ref_L00_00331718_02[i];
        diff = value - threshold;
        if (diff > 0.0f) {
            /* the positive case is handled after the join */
        } else {
            old = ref_L00_00331718_03 - threshold;
            if (old > 0.0f) {
                /* fall through to the join */
            } else {
                continue;
            }
        }
        if (diff < 0.0f) {
            func_002E5CF8(ref_L00_00331718_01[i], 0, ref_L00_00331718_00);
            ref_L00_00331718_03 = value;
            return;
        }
        old = ref_L00_00331718_04 - threshold;
        if (old < 0.0f) {
            func_002E5CF8(ref_L00_00331718_01[i], 0, ref_L00_00331718_00);
            ref_L00_00331718_03 = value;
            return;
        }
    }
    ref_L00_00331718_04 = value;
}

void func_00335DC0(int a0)
{
    float value;

    ref_L00_00335DC0_00 = a0;
    value = 1.076923f;
    if (a0 == 0)
        value = 1.0f;
    ref_L00_00335DC0_01 = value;
    value = 0.9f;
    if (a0 == 0)
        value = 1.0f;
    ref_L00_00335DC0_02 = value;
}

typedef int TI128_333048 __attribute__((mode(TI)));

typedef struct {
    int model;
    unsigned char kind;
    unsigned char pad05[0x47];
    short f4C;
    unsigned char pad4E[0x92];
} ClassRecord333048;

/* The hit description func_002A8E20 applies to a moby. */
typedef struct {
    float vector[4];
    char pad10[8];
    unsigned char type;
    unsigned char source;
    short oclass;
    char pad1C[4];
    int flag;
    char pad24[0xC];
} HitInfo333048;

extern unsigned char D_00139568[];
extern ClassRecord333048 D_00239BA0[];
extern char D_001B5200[];
extern short D_001B1CF0[] __attribute__((sda));
extern int D_001AD7EC;
extern char *D_001BF000[];
extern float D_001B0C30 __attribute__((sda));
extern float D_001B0C34 __attribute__((sda));
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern float func_002A78D8(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_002BDBC0(void *, void *, int, int, int, float);
extern float func_00283248(float, float);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002C7E28(void *, void *, int);
extern void func_002ACAD0(void *, short *);
extern void func_0032C700(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern int func_00277F48(void *, int, void *, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_0029F338(void *);

/* The class slot table: D_00139568 maps a slot to its class record. */
static inline int func_00333048_kind(int index)
{
    ClassRecord333048 *record = &D_00239BA0[D_00139568[index]];
    return record->model != 0 && record->kind == 3;
}

/* func_00333048: thirty sparks around the moby, fifty particles pushed away from the
   point at D_001B5200+0x140, a ring effect, then a hit on every moby in range. The ring prototype is
   interleaved as (pointer, float, float, ints...): the EE passes the two floats in $f12/$f13
   either way, and this order gives retail's argument scheduling. */
void func_00333048(char *object)
{
    float direction[4] __attribute__((aligned(16)));
    float spark[4] __attribute__((aligned(16)));
    HitInfo333048 hit __attribute__((aligned(16)));
    float distance;
    float yaw;
    float angle;
    int i;
    int j;
    int k;
    int count;
    char *camera;

    func_002E5CF8(3, 0, (int *)object);
    for (i = 0; i < 30; i++) {
        distance = func_002A7878(0.0f, 0.37f);
        yaw = func_002A7940();
        func_002AF000(spark, distance, yaw, func_002A7940());
        spark[2] += func_002A7878(0.35f, 0.6f);
        func_00282CC0(spark, spark, object + 0x10);
        distance = func_002A7878(0.0016666668f, 0.016666668f);
        yaw = func_002A7940();
        func_002AF000(direction, distance, yaw, func_002A7940());
        func_002BDBC0(spark, direction, 0x4F20507F, 0x102F, func_002A7820(30, 57), 150000.0f);
    }
    camera = D_001B5200;
    for (j = 0; j < 50; j++) {
        angle = func_00283248(*(float *)(camera + 0x140) - *(float *)(object + 0x10),
                              *(float *)(camera + 0x144) - *(float *)(object + 0x14));
        func_00283CF0(func_002A78D8(1.0f, 2.0f));
        direction[0] = *(float *)(object + 0x10) + func_002A78D8(0.0f, 0.15f);
        direction[1] = *(float *)(object + 0x14) + func_002A78D8(0.0f, 0.15f);
        direction[2] = *(float *)(object + 0x18) + func_002A78D8(0.0f, 0.15f);
        distance = D_001B0C30;
        angle = func_00283B98(angle, func_002A78D8(0.0f, -1.5707965f));
        spark[0] = func_00283180(angle) * 0.016666668f * distance;
        spark[1] = func_00283198(angle) * 0.016666668f * distance;
        distance = D_001B0C34;
        spark[2] = distance * 0.016666668f;
        func_002C7E28(direction, spark, 0x140);
    }
    func_002ACAD0(object, D_001B1CF0);
    func_0032C700(object + 0x10, 1.0f, 20.0f, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, D_001AD7EC);
    count = func_00277F48(object + 0x10, 0, object, 0, 3.0f);
    if (count > 0) {
        char **list = D_001BF000;
        k = count;
        do {
            char *moby = *list;
            if (*(short *)(*(char **)(moby + 0x24) + 0x46) == 5
                || (*(unsigned short *)(moby + 0x34) & 0x4000)) {
                float radius;
                func_00282CF0(direction, moby + 0x10, object + 0x10);
                func_00282F20(direction, direction, 1.0f);
                func_00282F20(hit.vector, hit.vector, 1.0f);
                radius = 10.0f;
                if (func_00333048_kind(0x10))
                    radius = 55.0f;
                func_002A8C00(hit.vector, object, 0x810000, direction, radius);
                *(TI128_333048 *)hit.vector = *(TI128_333048 *)direction;
                hit.vector[3] = 5627.9248f;
                hit.source = 3;
                hit.flag = 1;
                hit.type = 5;
                hit.oclass = *(short *)(moby + 0xAA);
                func_002A8E20(moby, &hit);
            }
            list++;
        } while (--k);
    }
    func_0029F338(object);
}
