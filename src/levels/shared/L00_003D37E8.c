#include "include_asm.h"

extern void func_L00_003D6FB8_1(char *p);
extern long long func_002E67A0_2(int id);
extern float func_0031A888_1(void);
extern void func_002EE178_1(char *dst, char *src, float scale);


extern void func_00282D30_2(char *dst, char *src, float scale);

extern void func_L00_003DC820_1(char *pkt);

extern long long func_0027C878_1(char *p);

extern float func_00283248_3(float x, float y);

extern float func_00282E20_2(char *p);

extern void func_00283410_3(float *matrix, float *quat);

extern void func_00282F20_3(float *off, char *src, float scale);

extern void func_L00_003DC8A8_1(char *pkt, float angle);

extern void func_00280B90_1(char *pkt, float *matrix, int mode);

extern void ref_L00_003E0F58_00(char *);

extern void ref_L00_003E0F58_01(char *, float);

extern void func_L00_003E0CE8_1(char *pkt);

extern void func_L00_003E0D70_1(char *pkt, float angle);

extern long long func_002E67A0_1(char *p);

extern float func_802EE7A8_1(float x, float y);

extern float func_802EE2E8_1(char *p, float *v);

extern void func_802EE970_1(float *matrix, float *quat);

extern void func_802EE138_1(float *off, float *v, char *p);

extern void func_802EE3D0_1(float *dst, float *src, float angle);

extern void func_802EAC30_1(char *pkt, float *matrix, int mode);

extern void func_L00_003DFF98_1(char *p);

extern void func_L00_003E0020_1(char *p, float scale);

/* The vector the aim helpers read, at 0x001B8C80. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector D_L00_001B8C80;

INCLUDE_ASM("asm/levels", func_L00_003D37E8);

INCLUDE_ASM("asm/levels", func_L00_003D3DE0);


/* func_L00_003D3FB0 lives in L00_003D3FB0-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_003D40D8);

/* func_L00_003D4548 is defined in L00_003D4548-g8.c. */



INCLUDE_ASM("asm/levels", func_L00_003D4A20);


/* shared native body of family a04928c6 */
void func_L00_003D6FB8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}

void func_L00_003D7250(int unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    func_L00_003D6FB8_1(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_002E67A0_2(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = D_L00_001B8C80.x_140 - *(float *)pos;
    dy = D_L00_001B8C80.y_144 - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_802EE7A8_1(dx, dy);
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                              D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = func_0031A888_1();
    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    func_002EE178_1(pkt, pkt, scale);
    func_002EE178_1(pkt + 16, pkt + 16, scale);
    func_002EE178_1(pkt + 32, pkt + 32, scale);
    func_002EE178_1(pkt + 48, pkt + 48, scale);
    func_802EAC30_1(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    func_002EE178_1(pkt, pkt, 0.5f);
    func_002EE178_1(pkt + 16, pkt + 16, 0.5f);
    func_002EE178_1(pkt + 32, pkt + 32, 0.5f);
    func_002EE178_1(pkt + 48, pkt + 48, 0.5f);
    func_802EAC30_1(pkt, m, 0);
}

/* shared native body of family a04928c6 */
void func_L00_003DA2B0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}



INCLUDE_ASM("asm/levels", func_L00_003DB118);

INCLUDE_ASM("asm/levels", func_L00_003DBF50);



INCLUDE_ASM("asm/levels", func_L00_003DC3E0);

typedef int Quad640 __attribute__((mode(TI)));

extern void func_L00_003DCC48(float f12, float f13, float f14, void *pos, char *a1, int a2, int a3);
extern int func_0031A768_1(int lo, int hi);
extern void func_L00_003DC910(char *pos, int a1, float fA, int a2, float fB, char *a3, int t0, float fC);
extern void func_L00_003DCAC8(char *pos, int a1, int a2, float f12, float f13, char *a3, int t0,
                              char *src);

/* Effect update by state: 1 starts the burst (one random-angle puff), 2 counts the timer down and draws the two fade rings. */
void func_L00_003DC640(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    Quad640 pos;
    float zero, scale;
    int n;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 1:
        pos = *(Quad640 *)(obj + 0x10);
        func_L00_003DCC48(0.0f, 0.85f, 0.25f, &pos, s + 0x10, 0x103080, 4);
        scale = *(float *)(obj + 0x2C) * 95.0f;
        n = func_0031A768_1(0x5F, 0x6F) >> 2;
        func_L00_003DC910(obj + 0x10, 0x103080, scale, n, func_0031A888_1(), (char *)0xB, 2, -1.0f);
        break;
    case 2:
        if (--*(int *)(s + 0x6C) <= 0)
            *(int *)(s + 0x6C) = 0;
        zero = 0.0f;
        pos = *(Quad640 *)(obj + 0x10);
        func_L00_003DCC48(zero, 0.85f, 0.25f, &pos, s + 0x10, 0x103080, 4);
        if (*(int *)(s + 0x7C) == 0) {
            func_L00_003DCAC8(obj + 0x10, 0x103080, *(int *)(s + 0x6C),
                              *(float *)(obj + 0x2C) * 45.0f, zero, (char *)0xB, 2, s + 0x50);
            func_L00_003DCAC8(obj + 0x10, 0x3F3F3F, *(int *)(s + 0x6C),
                              *(float *)(obj + 0x2C) * 33.75f, zero, (char *)0xB, 2, s + 0x50);
        }
        break;
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003DC820(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003DC8A8(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003DC910(char *pos, int a1, float fA, int a2, float fB, char *a3, int t0, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003DC820_1(pkt);
    r = func_002E67A0_1(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_802EE7A8_1(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                              D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                               D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003DC8A8_1(pkt, fA);
    func_802EAC30_1(pkt, m, 0);
}

/* Builds a 144-byte packet, derives a quaternion from source floats through four float helpers, writes the last matrix row from a source point plus a computed offset, then dispatches the packet. */
void func_L00_003DCAC8(char *pos, int a1, int a2, float f12, float f13, char *a3, int t0,
                       char *src)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003DC820_1(pkt);
    r = func_0027C878_1(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = func_00283248_3(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -func_00283248_3(func_00282E20_2(src), *(float *)(src + 8));
    quat[0] = f13;

    func_00283410_3(m, quat);
    func_00282F20_3(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003DC8A8_1(pkt, f12);
    func_00280B90_1(pkt, m, 0);
}

INCLUDE_ASM("asm/levels", func_L00_003DCC48);

INCLUDE_ASM("asm/levels", func_L00_003DD2B8);

void func_L00_003DD680(char *p)
{
    if (*(unsigned char *)(p + 0x20) == 0) {
        *(unsigned short *)(p + 0x34) |= 0x800;
        *(unsigned char *)(p + 0x20) = 1;
    }
}

INCLUDE_ASM("asm/levels", func_L00_003DD6A8);

INCLUDE_ASM("asm/levels", func_L00_003DDEC8);

/* func_L00_003DE088 lives in L00_003DE088-g8.c. */


/* func_L00_003DE490 is defined in L00_003DE490-basis-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_003DE950);


INCLUDE_ASM("asm/levels", func_L00_003DF710);


/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003DFF98(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003E0020(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003E0088(char *pos, int a1, int a2, char *a3, int t0,
                       float fA, float fB, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003DFF98_1(pkt);
    r = func_002E67A0_1(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_802EE7A8_1(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                              D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                               D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003E0020_1(pkt, fA);
    func_802EAC30_1(pkt, m, 0);
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003E0CE8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003E0D70(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Builds a 144-byte packet, derives a quaternion from source floats through four float helpers, writes the last matrix row from a source point plus a computed offset, then dispatches the packet. */
void func_L00_003E0DD8(char *pos, int a1, int a2, char *a3, int t0,
                                        char *src, float f12, float f13)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003E0CE8_1(pkt);
    r = func_0027C878_1(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = func_00283248_3(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -func_00283248_3(func_00282E20_2(src), *(float *)(src + 8));
    quat[0] = f13;

    func_00283410_3(m, quat);
    func_00282F20_3(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003E0D70_1(pkt, f12);
    func_00280B90_1(pkt, m, 0);
}

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003E0F58(char *pos, int a1, int a2, char *a3, int t0,
                       float fA, float fB, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    ref_L00_003E0F58_00(pkt);
    r = func_002E67A0_1(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_802EE7A8_1(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                              D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                               D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    ref_L00_003E0F58_01(pkt, fA);
    func_802EAC30_1(pkt, m, 0);
}

INCLUDE_ASM("asm/levels", func_L00_003E2180);

INCLUDE_ASM("asm/levels", func_L00_003E2510);


INCLUDE_ASM("asm/levels", func_L00_003E2E80);
