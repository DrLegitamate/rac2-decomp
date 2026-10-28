#include "common.h"

typedef int MotionQuad __attribute__((mode(TI)));
typedef union { float v[4]; MotionQuad q; } MotionVec;

extern void func_002E3470(void *, void *, void *);

typedef int ClosestPointQuad __attribute__((mode(TI)));

typedef struct { char *p[6]; } Sep6;

extern Sep6 D_L01_001AA550;

extern char D_L01_001AA568[];

extern char D_L01_001AA578[];

extern char D_L01_001AA588[];

extern int func_00115DA8_2(char *dst, char *fmt, ...);

extern char D_L01_00189E20[];

extern char D_L01_002637A0[];

extern int D_L01_001A8F40;

extern char D_L01_00189E20_sda[] __attribute__((sda));

extern void func_002C7CA8(void);

extern void func_002B4070(void);

extern void func_002ADDC8(void);

extern void func_002C37C8(void);

extern void func_002AEB80(void);

extern void func_002B9878(void);

extern void func_002A7740(void);

extern void func_002AB1C8(void);

extern void func_002A9520(void);

extern void func_002A9310(void);

extern void func_002FDB00(void *a0);

extern void func_002AB328(void);

extern void func_0030F444(int a0);

extern char D_L01_00189E20[];

extern void func_002A8EE0(int a0, int a1);

extern char D_L01_00139568[];

extern unsigned char D_0018C0D4[];

extern void func_002BEB90(unsigned long, unsigned long);

extern void *D_0018C0B0;

extern float D_L01_00189F90;

extern unsigned short *D_L01_001FB020[];

extern unsigned short *r1_D_L01_001ABFC0[];

extern char *r1_D_L01_00160058 MACRO_ADDR;

extern int r1_D_L01_00160058_m __asm__("r1_D_L01_00160058") MACRO_ADDR;

extern char *D_L01_001FE180[];

extern int func_311B48(char *a0, void *a1, int a2);

extern int func_3163C8(char *a0, void *a1);

extern int func_316558(char *a0, void *a1);

extern int func_3164A0(char *a0, void *a1);

extern void func_002E3CD8(void *a0, void *a1);

extern void func_002E3F60(void *a0, void *a1);

extern void func_002E34A0(void *a0, void *a1, void *a2);

extern void func_L01_002E3940(void *a0, void *a1, void *a2);

extern void func_002E3470(void *a0, void *a1, void *a2);

extern void func_002E3918(void *a0, void *a1, void *a2);

extern void func_002E3470(void *a0, void *a1, void *a2);

extern float func_00283B98(float f12, float f13);

extern float func_00283198(float f12);

extern int func_00283D38(int a0, int a1, float f12);

extern float func_002A7878(float f12, float f13);

extern void func_002AEC18(void *a0, int a1);

extern float func_002E3B10(float f12, float f13);

extern int func_002B50E0(char *a0, char *a1, float f12);

extern char *func_00321F08(int a0);

extern void func_003140B0(char *a0, char *a1, int a2, float f12, float f13,
                          float f14, float f15);

extern char D_00139A28[];


extern int D_L01_001A79F0;

extern int D_L01_0028EA50[];

extern int D_L01_001C5D20[];

extern void func_002A6CF0(int a0);

extern float func_002E3618(void *a0, void *a1);

extern unsigned char D_L01_001AA6F8[];

extern char D_00188660[];

extern int func_003711D8(int a0);

extern unsigned char D_L01_001395B8[];

extern void func_003907B8(int a0, int a1, int a2);


void func_L01_002A84D8(void) {
    char *p;

    func_002C7CA8();
    func_002B4070();
    func_002ADDC8();
    func_002C37C8();
    func_002AEB80();
    p = D_L01_00189E20;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        func_002B9878();
        func_002A7740();
        if (*(unsigned char *)(p + 0x22B4) != 0) {
            func_002AB1C8();
            func_002A9520();
            func_002A9310();
            func_002FDB00(p + 0x80);
            func_002AB328();
            func_0030F444(*(int *)(p + 0x2290));
        }
    }
}


void func_L01_002A9298(void) {
    char *b = D_L01_00189E20;
    int i = *(int *)(b + 0x1248);
    unsigned char c;
    unsigned char *t;

    if (i < 0)
        return;
    c = *(unsigned char *)(D_L01_00139568 + i);
    t = (unsigned char *)D_L01_002637A0 + c * 0xE0;
    if (t[4] == 0)
        return;
    if (*(int *)(b + 0x1220) == 0)
        return;
    func_002A8EE0(*(int *)(b + 0x1220), *(int *)(b + 0x2290));
}


INCLUDE_ASM("asm/levels", func_L01_002AE128);

INCLUDE_ASM("asm/levels", func_L01_002B0318);

extern void func_L00_002AF7D0(void);
extern void func_L00_002B1F90(void);
extern void func_L00_00322EC8(char *a0);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(int a0);
extern void func_L01_002BEB90(int a0, int a1);
extern void func_L01_002B3D28(void);
extern char D_00189E20[];

void func_L01_002B3458(int a0, int a1, int a2) {
    char *s0 = D_00189E20;

    func_L00_002AF7D0();
    s0[0x22B6] = 1;
    func_L00_002B1F90();
    *(int *)(s0 + 0x2290) = *(int *)(s0 + 0xC18);
    func_L00_00322EC8(s0 + 0x18E0);
    func_L00_00322EC8(s0 + 0x1A30);
    *(int *)(*(int *)(s0 + 0x2290) + 0x9C) = -1;
    if (a0 != 4 || *(unsigned char *)(s0 + 0x22B4) != a0)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    {
        char *s1 = D_00189E20;

        *(unsigned char *)(s1 + 0x22B4) = a0;
        *(int *)(s1 + 0xC14) = a2;
        *(int *)(s1 + 0x2290) = a2;
    }
    func_L01_002B3D28();
    {
        char *s2 = D_00189E20;

        *(float *)(s2 + 0x250) = *(float *)(s2 + 0x258);
        *(float *)(s2 + 0x254) = *(float *)(s2 + 0x25C);
        *(unsigned short *)(*(int *)(s2 + 0x2290) + 0x34) |= 6;
        *(float *)(s2 + 0xC20) = 1.0f;
        *(float *)(s2 + 0xC24) = 1.0f;
        func_L00_002D24B8();
        func_002A677C(*(int *)(s2 + 0x2290));
        *(unsigned short *)(s2 + 0x24F2) = a1;
    }
    func_L01_002BEB90(a1, 2);
}


/* func_L01_002B3788 is defined in L01_002B3788-contact.c. */

/* func_L01_002B3D28 is defined in L01_002B3D28.c. */



INCLUDE_ASM("asm/levels", func_L01_002B4DA0);

INCLUDE_ASM("asm/levels", func_L01_002B5EA0);

INCLUDE_ASM("asm/levels", func_L01_002B6948);

/* func_L01_002BE0E0 is defined in L01_002A7248-timers-g8.c. */

void func_L01_002C1988(unsigned long x) {
    unsigned long mode = 1;
    if (x)
        mode = 2;
    if (D_0018C0D4[0] == 0)
        func_002BEB90(0, mode);
}

/* func_L01_002C2CF0 is defined in L01_002C2CF0-keep-block-order.c. */

void func_L01_002C8990(void) {
    *(unsigned short *)((char *)D_0018C0B0 + 0x34) |= 1;
}

void func_L01_002C89A8(void) {
    *(unsigned short *)((char *)D_0018C0B0 + 0x34) &= 0xFFFE;
}

void func_L01_002C98B8(void) {
    if (D_L01_00189F90 < 0.045f)
        func_002BEB90(0, 1);
    else
        func_002BEB90(3, 1);
}


INCLUDE_ASM("asm/levels", func_L01_002E1510);


/* func_L01_002E1680 is defined in L01_002E1680.c. */

INCLUDE_ASM("asm/levels", func_L01_002E2608);

INCLUDE_ASM("asm/levels", func_L01_002EABA8);


/* Defined in L01_002F14E8-g8.c. */

INCLUDE_ASM("asm/levels", func_L01_002F1588);



INCLUDE_ASM("asm/levels", func_L01_00304270);

/* Defined in L01_00310BC0.c. */

/* rac1-decomp src/overlays/shared/mobyutil_0026E8E0.c: func_L01_0026F090 */
// Walks a list of moby indices and sets the state byte of each one that is non-negative.
void func_L01_003115E8(int list, int state)
{
    unsigned short *p;
    unsigned short *q = (unsigned short *)r1_D_L01_001ABFC0[list];
    if (q != 0) {
        p = q;
        do {
            char *m = (char *)(((*p & 0x7FFF) << 8) + r1_D_L01_00160058_m);
            if (m[0x20] >= 0) {
                m[0x20] = state;
            }
        } while (*(short *)p++ >= 0);
    }
}

/* Defined in L01_00311C18.c. */

/* func_L01_003120A8 is defined in L01_003120A8-helpers.c. */

void func_L01_003128C0(char *p) {
    *(int *)(p + 0x70) = 0;
    *(float *)(p + 0x74) = 0.2f;
}


/* chain of four probes on the same object; the first that reports a hit picks the code */
int func_L01_003165E8(char *a0, int a1, char *a2, char *a3, char *t0) {
    if (a1 >= 0) {
        char *p = D_L01_001FE180[a1];
        if (func_311B48(a0, p + 0x10, *(int *)p))
            return 1;
    }
    if (func_3163C8(a0, a2))
        return 2;
    if (func_316558(a0, a3))
        return 3;
    if (func_3164A0(a0, t0))
        return 4;
    return 0;
}

void func_L01_00316C48(void *a0, void *a1, void *a2, void *a3, void *t0) {
    float p[0x10];
    float q[0x10];
    float v[4];

    func_002E3CD8(p, a3);
    func_002E3F60(p, p);
    func_002E3CD8(q, t0);
    func_002E34A0(v, a0, a2);
    func_L01_002E3940(v, v, p);
    func_L01_002E3940(v, v, q);
    func_002E3470(a1, v, a2);
}

/* func_L01_00318638 is defined in L01_00318638-qcopy-barrier.c. */

void func_L01_0031A278(char *a0, float *a1, float f12, float f13, float f14) {
    a1[0] = f12;
    a1[1] = f13;
    a1[2] = f14;
    func_002E3918(a1, a1, a0 + 0xC0);
    func_002E3470(a1, a1, a0 + 0x10);
}

INCLUDE_ASM("asm/levels", func_L01_0031AB20);

INCLUDE_ASM("asm/levels", func_L01_0031B300);

int func_L01_0031BC68(int a0, int a1, float phase) {
    float v = func_00283198(phase);
    return func_00283D38(a0, a1, v * 0.5f + 0.5f);
}




void func_L01_003208D0(void *a0, float *a1, int a2) {
    unsigned char *p = (unsigned char *)a0;
    float r;
    int i;

    if (p[0x23] == 0 && a2 == 0)
        return;

    r = func_00283B98(*a1, 0.14544412f);
    *a1 = r;
    r = func_00283198(r);
    i = func_00283D38(0x8000C020, 0x80008000, (r + 0.5f) * 0.5f);
    if (func_002A7878(0.0f, 1.0f) < 0.05f)
        i = func_00283D38(i, 0x8080FFFF, 0.3f);
    func_002AEC18(a0, i);

    if (a2 != 0) {
        if (p[0x23] < 0x3D)
            p[0x23] = p[0x23] + 3;
        else
            p[0x23] = 0x40;
    } else {
        if (p[0x23] >= 4)
            p[0x23] = p[0x23] - 3;
        else
            p[0x23] = 0;
    }
}

INCLUDE_ASM("asm/levels", func_L01_003209F8);

int func_L01_00321178(char *a0, char *a1) {
    float v = func_002E3B10(*(float *)(a1 + 0) - *(float *)(a0 + 0x10),
                            *(float *)(a1 + 4) - *(float *)(a0 + 0x14));
    return func_002B50E0(a0, a1, v);
}

int func_L01_00322288(int a0, float f12) {
    char *p = func_00321F08(a0);
    if (p == 0)
        return 0;
    func_003140B0((char *)a0 + 0xF8, p + 0xB4, 0, f12, *(float *)(p + 0x14),
                  *(float *)(p + 0x18), *(float *)(p + 0x1C));
    return 1;
}



/* shared native body of family d1b66aa7f0ecd20d */
void func_L01_003242C8(char *dst, int x, int idx)
{
    Sep6 t;
    t = D_L01_001AA550;
    if (x > 999999) {
        int m = x / 1000000;
        int w = x % 1000000;
        func_00115DA8_2(dst, D_L01_001AA568, m, t.p[idx % 6], w / 1000,
                          t.p[idx % 6], w % 1000);
    } else if (x >= 1000)
        func_00115DA8_2(dst, D_L01_001AA578, x / 1000,
                          t.p[idx % 6], x % 1000);
    else
        func_00115DA8_2(dst, D_L01_001AA588, x);
}


extern int func_00115AC0(char *dst, char *src, int len);

/* Expands a template: copies src into the scratchpad, then writes it to out, replacing %d (next number) and %<n>d (n-th number) with the numbers listed in nums (every second int, up to ten, stopped by -1). */
void func_L01_00324410(char *out, char *src, int *nums)
{
    int tab[10];
    unsigned char buf[32];
    int i;
    int *p;
    int *q;
    unsigned char *s;
    char *w;
    int n;
    int cnt;
    int v;

    p = nums;
    i = 0;
    func_00115AC0((char *)0x70000000, src, 0xFF);

    q = tab;
    for (;;) {
        p += 2;
        v = p[-2];
        if (v == -1)
            break;
        *q++ = v;
        i++;
        if (i >= 10)
            break;
    }

    s = (unsigned char *)0x70000000;
    w = out;
    cnt = 0;
    while (*s != 0) {
        if (*s == '%') {
            if (s[1] == 'd') {
                v = cnt++;
                s += 2;
            } else {
                v = s[1] - '0';
                s += 3;
            }
            func_L01_003242C8((char *)buf, tab[v], 0);
            n = 0;
            if (*buf != 0) {
                while (buf[n] != 0 && n < 32) {
                    *w = buf[n];
                    n++;
                    w++;
                }
            }
            *w = 0;
        } else {
            *w = *s;
            s++;
            w++;
        }
    }
    *w = 0;
}

INCLUDE_ASM("asm/levels", func_L01_00324550);

/* func_L01_003245E0 is defined in L01_002A7248-g8.c (this unit has no $gp access for it). */

void func_L01_003246A0(int a) {
    char *base = D_00139A28;
    char *p;
    base = base + 0xC;
    p = base + a * 16;
    if (*(int *)p == 0)
        *(int *)p = 1;
}

/* func_L01_003246D0 is defined in L01_003246D0.c. */

/* Scans the half-open span of the pair table for the caller's key. */
int func_L01_003246F8(int key) {
 unsigned n=(unsigned)D_L01_001A79F0;
 int i;
 int end;
 if(n>=0x13) return 0;
 i=D_L01_0028EA50[n];
 end=D_L01_0028EA50[n+1];
 while(i<end) {
  if(D_L01_001C5D20[i]==key) return i;
  i++;
 }
 return -1;
}

/* RAC1 counterpart: src/overlays/shared/span_particle.c, spawn_span_particle. */
INCLUDE_ASM("asm/levels", func_L01_00326DD8);

typedef int Quad331CA0 __attribute__((mode(TI)));
typedef struct { unsigned char b0, b1, b2, b3; int color; unsigned char seed, alpha; unsigned short size; float life; union { Quad331CA0 q; float f[4]; } position; float payload[8]; } Particle331CA0;
extern Particle331CA0 *func_002B9030(int kind);
extern float func_002A7878(float low, float high);
extern int func_00283CF0(float value);
extern unsigned char *D_L01_001FF164;

/* Spawns the burst particle of the given kind at position, carrying the velocity and the size scale in its payload. */
void func_L01_00331CA0(Quad331CA0 *position, int kind, Quad331CA0 *velocity, float scale)
{
    Quad331CA0 saved = *velocity;
    Quad331CA0 *vp = &saved;
    Particle331CA0 *p = func_002B9030(0x49);

    if (p) {
        float life = 0.0f;
        int tint = 0;

        switch (kind) {
        case 0:
            func_002A7878(0.25f, 0.25f);
            life = 0.12f;
            tint = 0x20;
            break;
        case 1:
            func_002A7878(1.0f, 1.0f);
            life = 0.5f;
            tint = 0xD;
            break;
        }
        p->size = 0x37;
        p->color = (tint << 24) | 0xFFFFFF;
        p->alpha = func_00283CF0(4.0f) + 0x20;
        p->b1 = 0;
        p->b3 = 0x48;
        p->b2 = D_L01_001FF164[kind];
        p->life = life * 210000.0f;
        p->seed = func_002A7878(0.0f, 360.0f);
        p->position.q = *position;
        *(Quad331CA0 *)p->payload = *vp;
        p->payload[3] = scale;
    }
}

/* func_L01_00331E08 is in L01_00331E08.c. */

/* Averages each 16-byte record of the table the argument points at against the record
   (i + 1) % n, storing the result in the record's own +0xC field and returning the
   running sum; a null argument reports and answers -1.0f. */
float func_L01_003377C8(unsigned char *a0) {
    unsigned char *s2;
    unsigned char *q;
    int s0, s1, n;
    float f20;
    float f0;

    s2 = a0;
    f20 = 0.0f;
    if (s2 == 0) {
        func_002A6CF0((int)D_L01_001AA6F8);
        return -1.0f;
    }
    n = *(int *)s2;
    if (n <= 0)
        return f20;
    s0 = 0;
    do {
        s1 = s0 + 1;
        f0 = func_002E3618(s2 + 0x10 + (s0 << 4), s2 + 0x10 + ((s1 % n) << 4));
        q = s2 + (s0 << 4);
        *(float *)(q + 0x1C) = f0;
        f20 += f0;
        s0 = s1;
        n = *(int *)s2;
    } while (s0 < n);
    return f20;
}

INCLUDE_ASM("asm/levels", func_L01_00337888);




int func_L01_00355BA0(int index, int value) {
    char *p = D_00188660 + index * 0x70;
    *(unsigned short *)(p + 0x80) = value;
    return 1;
}


void func_L01_00371228(int a0, int a1) {
    int i = func_003711D8(a0);
    if (i >= 0)
        D_L01_001395B8[i] |= (unsigned char)(1 << a1);
}

INCLUDE_ASM("asm/levels", func_L01_003801B8);

/* func_L01_003808C0 is in L01_003808C0-g8.c for its GP accesses. */

INCLUDE_ASM("asm/levels", func_L01_0038EF40);

/* A model with kind 0x12 is exempt from the trigger's visibility switches. */
#define SPATIAL_TRIGGER_EXEMPT(p) \
    ((p) && *(char **)((p) + 0x24) && \
     *(short *)(*(char **)((p) + 0x24) + 0x46) == 0x12)

INCLUDE_ASM("asm/levels", func_L01_003907B8);

#undef SPATIAL_TRIGGER_EXEMPT

void func_L01_003909E0(int a0, int a1, int a2, int a3) {
    unsigned short *p = D_L01_001FB020[a2];
    if (p != 0) {
        do {
            func_003907B8(*p & 0x7FFF, a1, a3);
        } while (*(short *)p++ >= 0);
    }
}

INCLUDE_ASM("asm/levels", func_L01_00390A50);

void func_L01_00390C60(char *a0)
{
    char *v0 = *(char **)(a0 + 0x68);
    char *v1;
    unsigned char a1;

    if (v0 == 0)
        return;
    v1 = *(char **)v0;
    if (v1 == 0)
        return;
    a1 = *(unsigned char *)(v1 + 0x20);
    if (a1 == 0xFE)
        return;
    if (a1 == 0xFD)
        return;
    if (*(unsigned short *)(v1 + 0x34) & 1)
        *(unsigned short *)(a0 + 0x34) |= 0x41;
    else
        *(unsigned short *)(a0 + 0x34) &= 0xFFBE;
}

INCLUDE_ASM("asm/levels", func_L01_00394148);

INCLUDE_ASM("asm/levels", func_L01_00394240);
