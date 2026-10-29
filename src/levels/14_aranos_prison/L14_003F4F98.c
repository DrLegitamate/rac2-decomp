#include "include_asm.h"
#include "common.h"
extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern char D_00188660[];
extern void func_L14_00432450(void *);
extern char D_L14_001B9500[];
extern char D_0018A0E0[];
extern void func_002FC560(unsigned int, unsigned long);
extern void func_00281DE8(void *, int, int, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);

extern char D_00189EA0[];
extern char D_L14_001A8F20[] __attribute__((sda));
/* The same entity-base pointer is read both absolutely and through $gp. */
extern char *D_L14_001B259C_gp SDATA(D_L14_001B259C);
extern char *D_L14_001B259C_direct __asm__("D_L14_001B259C") __attribute__((sda));
extern int func_002A8508(int, int);
extern float func_00282E80(void *, void *);
extern int func_002B38B8(void *);
extern int func_002ACBC8(void *, int);
extern void func_002A7470(void *, int, int, int);
extern int func_00277258(void *, float, int, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_0029F338(void *);


typedef int PrisonQword __attribute__((mode(TI)));
typedef struct { PrisonQword v[4]; } PrisonMatrix;
typedef struct {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    long long mode;
    char pad[24];
} PrisonQuad;
extern PrisonMatrix D_L14_001B1A00;


typedef struct { char pad[0x20]; float rate[4]; unsigned int start[4]; unsigned int end[4]; int timer[4]; float angle[4]; } PrisonVisualState;
extern void func_L14_004308D0(void *, int, int, int, float, float, float);
extern float func_L14_00430898(float);
extern void func_L14_00430E08(void *);
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern void func_002E5CF8(int, int, void *);
extern int func_00282948(void *);
extern void func_00325DA0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_00325C50(void *, void *, int, void *, float);
extern void func_002B0990(void *, void *, int, int, float);

extern char D_L14_001BF980[];

extern void func_00282F20_2(void *out, void *in, float scale);

extern void func_00282CC0_6(void *out, void *in1, void *in2);

extern int func_002761F8(void *a, void *b, int mode, void *self, int flag);

extern void func_00282D30_6(void *out, void *in, float scale);

INCLUDE_ASM("asm/levels", func_L14_003F4F98);

/* Read the word at offset 0x 18 through the pointer stored at owner offset 0x 68. */
unsigned int func_L14_004137F8(unsigned int param_1)
{
    unsigned int inner_ptr;
    unsigned int result;

    inner_ptr = *(unsigned int *)(param_1 + 0x68);
    result = *(unsigned int *)(inner_ptr + 0x18);
    return result;
}

/* Normalises and combines two temporary vectors from a state block, dispatches on the combined result and conditionally scales the output vector. */
void func_L14_00413CD8(char *self, char *p1, int p2)
{
    float a[4];
    float b[4];

    func_00282F20_2(a, self + 224, 0.1f);
    func_00282F20_2(b, self + 224, -3.0f);
    func_00282CC0_6(a, a, self + 16);
    func_00282CC0_6(b, b, self + 16);

    if (func_002761F8(a, b, 2, self, 0))
        func_00282F20_2(p1, D_L14_001BF980, 1.0f);
    else
        func_00282F20_2(p1, self + 224, -1.0f);

    if (p2 == 0)
        func_00282D30_6(p1, p1, -1.0f);
}

extern unsigned char *D_L14_001B259C __attribute__((sda));
extern void func_L03_004199F0(void *);
extern int func_L02_0032EDD8(void *, void *, int, int *);

typedef struct {
    int id;
    unsigned char links[4];
    unsigned char pad08[24];
} PrisonGraphNode;

typedef struct {
    unsigned char pad00[0x80];
    PrisonGraphNode nodes[32];
    int count;
} PrisonGraphState;

/* Looks up the graph nodes of first and second and, when they differ, sets (or with clear,
   clears) bit 7 of the link between them in both nodes' four link bytes. The links of node 0
   serve as the base for both scans, and both scans read the two ids from their stack slots. */
void func_L14_00420B10(int index, void *first, void *second, int clear) {
    unsigned char *self = D_L14_001B259C + index * 256;
    PrisonGraphState *state = *(PrisonGraphState **)(self + 0x68);
    int id0, id1;
    int i;
    unsigned char *links;
    unsigned char *entry;

    if (!self[0x20])
        func_L03_004199F0(self);
    id0 = id1 = -1;
    if (func_L02_0032EDD8(first, state->nodes, state->count, &id0)) {
        if (func_L02_0032EDD8(second, state->nodes, state->count, &id1)) {
            if (id0 != id1) {
                links = state->nodes[0].links;
                i = 0;
                do {
                    entry = &links[id0 * sizeof(PrisonGraphNode) + i];
                    if ((*entry & 127) == id1) {
                        if (clear)
                            *entry &= 127;
                        else
                            *entry |= 128;
                        break;
                    }
                    ++i;
                } while (i < 4);
                i = 0;
                do {
                    entry = &links[id1 * sizeof(PrisonGraphNode) + i];
                    if ((*entry & 127) == id0) {
                        if (clear)
                            *entry &= 127;
                        else
                            *entry |= 128;
                        break;
                    }
                    ++i;
                } while (i < 4);
            }
        }
    }
}

INCLUDE_ASM("asm/levels", func_L14_00421BC0);

INCLUDE_ASM("asm/levels", func_L14_004221D8);

INCLUDE_ASM("asm/levels", func_L14_00422498);

/* func_L14_004228C0 is defined in L14_003F4F98-g8.c. */

/* func_L14_004229A0 is defined in L14_003F4F98-ribbon-g8.c. */

extern void func_423000();
extern void func_423240();
extern void func_423358();
extern void func_423B30();
extern void func_423BD8();

void func_L14_00422FA0(char *a0)
{
    if (*(unsigned char *)(a0 + 0x20) == 0) {
        func_423000(a0);
    } else {
        func_423240(a0);
        func_423358(a0);
        func_423B30(a0);
        func_423BD8(a0);
    }
}

INCLUDE_ASM("asm/levels", func_L14_00423000);

/* func_L14_00423358 lives in L14_00423358-g8.c (small-data accesses). */

extern void func_002B5278(char *object, float factor);

extern void func_002B5258(char *object);

extern void func_002B50E0(char *object, char *bone, float factor);

extern void func_002B4FF0(char *object, char *bone, float factor);

/* The level's own jump table (the label of the data blob at 0x002AA360). */
extern void *jtbl_002AA360[];

/* Dispatches on the owner's animation step and plays the matching bone animation. */
void func_L14_00423B30(char *object)
{
    static void * volatile tab[] = { &&cA, &&cC };
    char *state;
    unsigned int sel;

    sel = *(unsigned char *)(object + 0x42) - 1;
    state = *(char **)(object + 0x68);
    if (sel < 19) {
        goto *jtbl_002AA360[sel];
    }
    goto end;
cA:
    if (*(short *)(state + 0x776) != 0) {
        func_002B5278(object, *(float *)(state + 0x744));
    } else {
        func_002B5258(object);
    }
    goto out;
cC:
    if (*(short *)(state + 0x77A) != 0) {
        func_002B50E0(object, state + 0x700, *(float *)(state + 0x768));
    } else {
        func_002B4FF0(object, state + 0x700, *(float *)(state + 0x740));
    }
out:
end:
    return;
}

extern char D_L14_001B9500[];

extern void func_80326928(char *a0, void *a1);

extern void func_8032AA20(char *a0, void *a1, int a2, float a3, float a4);

extern float func_802F5DF8(char *a0, void *a1);

extern void func_803240F8(char *a0);

/* Restarts the owner's animation: two timed fades, the counter, then the panic state. */
void func_L14_00423BD8(char *a0)
{
    char *s1;
    float f20;
    float f21;

    s1 = *(char **)(a0 + 0x68);
    f21 = 0.03f;
    f20 = 0.3f;
    func_80326928(a0, s1 + 0x50);
    func_8032AA20(a0, s1 + 0x680, 1, f21, f20);
    func_8032AA20(a0, s1 + 0x600, 0, f21, f20);
    if (*(unsigned short *)(a0 + 0x96) <= 0xFFFE)
        *(unsigned short *)(a0 + 0x96) = *(unsigned short *)(a0 + 0x96) + 1;
    *(unsigned short *)(s1 + 0x776) = 0;
    *(unsigned short *)(s1 + 0x778) = 0;
    *(unsigned short *)(s1 + 0x77A) = 0;
    if (*(unsigned char *)(a0 + 0x31) != 0) {
        if (func_802F5DF8(a0 + 0x10, D_L14_001B9500) < 24.0f) {
            func_803240F8(a0);
            *(unsigned char *)(a0 + 0x6F) = 0x16;
        }
    }
}

extern void func_318ED0();
extern void func_2F5C68();
extern float func_2F62F0(float a, float b);
extern float func_2F5DB0(float *p);

void func_L14_00423DC0(char *a0, int a1)
{
    float v[4];
    char *s0;
    float f;

    s0 = *(char **)(a0 + 0x68);
    *(unsigned short *)(s0 + 0x776) = 1;
    func_318ED0(a0, 2, v);
    func_2F5C68(v, a1, v);
    f = func_2F62F0(v[0], v[1]);
    *(float *)(s0 + 0x744) = f;
    f = func_2F5DB0(v);
    f = -func_2F62F0(f, v[2]) * 0.5f;
    *(float *)(s0 + 0x6E4) = f;
    *(float *)(s0 + 0x664) = f;
}

INCLUDE_ASM("asm/levels", func_L14_00423E50);


INCLUDE_ASM("asm/levels", func_L14_00425CB0);

INCLUDE_ASM("asm/levels", func_L14_004265B8);

/* func_L14_00426D18 lives in the -g8 sibling file (it reads a count through $gp). */

extern short D_001A6480[];

extern void func_385CB8(unsigned int reg, unsigned long value);

extern void func_2EF6D8(int, int, int, int, int);

/* Queues the level jingle for the owner with the volume its state block asks for. */
void func_L14_00426DE8(char *a0)
{
    char *v0;
    int s0;

    v0 = *(char **)(a0 + 0x68);
    s0 = ((int)((1.0f - *(float *)(v0 + 0x68)) * 128.0f)) << 24;
    func_385CB8(0x42, 9);
    func_2EF6D8(0, D_001A6480[0xA9], 0, D_001A6480[0xA8], s0);
}


INCLUDE_ASM("asm/levels", func_L14_00426F28);


/* func_L14_00427250 lives in the -g8 sibling file (it reaches a global through $gp). */


INCLUDE_ASM("asm/levels", func_L14_004275E0);

INCLUDE_ASM("asm/levels", func_L14_004281D0);

extern unsigned char *D_L14_001FB060[];

/* The same global as D_L14_001B259C, under a second name: this access is
   $gp-relative, that one absolute. */
extern unsigned char *D_L14_001B259C_1 __attribute__((sda));

/* Walks the 0x7FFF-masked id list at table[index] and flags class 0x112B entries. */
void func_L14_004286F8(unsigned char *a0)
{
    unsigned char *base;
    unsigned char *p;
    unsigned short *q;
    char *e;

    if (a0[0x21] == 0xFF)
        return;
    p = D_L14_001FB060[a0[0x21]];
    if (p == 0)
        return;
    q = (unsigned short *)p;
    base = D_L14_001B259C_1;
    for (;;) {
        e = (char *)(base + ((*q & 0x7FFF) << 8));
        if ((signed char)e[0x20] >= 0) {
            if (*(signed short *)(e + 0xAA) == 0x112B) {
                *(unsigned short *)(*(unsigned int *)(e + 0x68) + 0x316) = 1;
            }
        }
        if ((signed short)*q < 0)
            break;
        q++;
    }
}

/* func_L14_00428A08 lives in the -g8 sibling file (it reads a count through $gp). */

/* func_L14_00428BA0 lives in the -g8 sibling file (it reads two globals through $gp). */

/* func_L14_00428E68 is defined in L14_00428E68-g8.c. */

INCLUDE_ASM("asm/levels", func_L14_004295D0);

void func_L14_004298F0(unsigned char *self) {
    unsigned char *state = *(unsigned char **)(self + 0x68);
    float delta[4] __attribute__((aligned(16)));
    func_00282948(state + 0x30c);
    func_00282948(state + 0x310);
    if (*(unsigned short *)(self + 0x96) < 65535)
        ++*(unsigned short *)(self + 0x96);
    func_00325DA0(self, state + 0x308);
    func_00282CF0(delta, self + 0x10, state + 0x2d0);
    qcopy(state + 0x2d0, self + 0x10);
    if (self[0x95] == 1) {
        *(float *)(state + 0x2fc) = func_00283B98(*(float *)(state + 0x2fc), 0.2094395459f);
        func_00325C50(self, state + 0x300, 1, delta, *(float *)(state + 0x2fc));
    } else {
        *(float *)(state + 0x2fc) = func_00283B98(*(float *)(state + 0x2fc), 0.01163553074002266f);
        func_00325C50(self, state + 0x300, 0, delta, *(float *)(state + 0x2fc));
    }
    func_002B0990(self, state + 0x230, 7, 1, 2.0f);
}


extern void *func_801234F0(float scale);

extern long long func_80131430(long long value);

extern long long func_80122B00(long long a, long long b);

extern void *func_80122DA8(void *a, long long b);

extern float func_80123298(long long a);

extern void func_80321F58(char *a0, int a1, int a2);

/* Fills the owner's screen slot with the width the display state reports. */
void func_L14_0042D018(char *a0)
{
    char *p;
    void *s0;
    long long v;

    p = *(char **)(a0 + 0x68);
    if (*(unsigned char *)(a0 + 0x20) != 0)
        return;
    s0 = func_801234F0(*(float *)(a0 + 0xC));
    v = func_80131430(0x4000000000000000LL);
    v = func_80122B00(v, 0x4090000000000000LL);
    v = func_80122DA8(s0, v);
    *(float *)(p + 0x10) = func_80123298(v);
    func_80321F58(a0, 1, -1);
}

/* func_L14_0042FB10 is defined in L14_0042FB10-effect-g8.c. */

/* Per-object state of the sliding gate (func_L14_0042FDA8). */
typedef struct {
    int linked[4];
    int f10;
    int f14;
    int f18;
    int group;
} PrisonGateState;

/* A 0x100-byte entity record. */
typedef struct {
    char pad00[0x10];
    float pos[4];
    u8 mode;
    char pad21[3];
    int *next;
    char pad28[0xC];
    u16 flags;
    char pad36[0xD];
    u8 anim;
    char pad44[0x1C];
    u8 animFlags;
    char pad61[7];
    PrisonGateState *state;
    char pad6C[0xC];
    int f78;
    char pad7C[0x19];
    u8 f95;
    char pad96[2];
    int f98;
    char pad9C[0x5C];
    float angle;
    char padFC[4];
} PrisonEntity;

/* Gate logic: opens when the player nears, is hit open by linked objects, and
   hands off to the next object when it slides clear. */
void func_L14_0042FDA8(PrisonEntity *self)
{
    float temp[4] __attribute__((aligned(16)));
    float front[4] __attribute__((aligned(16)));
    float left[4] __attribute__((aligned(16)));
    float right[4] __attribute__((aligned(16)));
    /* Passed unwritten to the left/right additions below, as retail does; the matching code needs that. */
    float offset1[4] __attribute__((aligned(16)));
    float offset2[4] __attribute__((aligned(16)));
    PrisonGateState *state = self->state;
    int i;
    int entry;
    int group;
    PrisonEntity *other;
    char *base;

    if (self->mode == 0) {
        /* Mark the group's members busy. */
        if (D_L14_001FB060[group = state->group] && func_002A8508(group, -1) >= 2) {
            unsigned short *list;

            list = (unsigned short *)D_L14_001FB060[state->group];
            base = D_L14_001B259C_direct;
            do {
                entry = *list;
                other = (PrisonEntity *)(base + ((entry & 0x7FFF) << 8));
                other->flags |= 0x43;
            } while ((group = (short)*list++) >= 0);
        }

        if (func_00282E80(&self->pos, D_00189EA0) < 6.0f && func_002B38B8(self) &&
            !func_002ACBC8(D_00189EA0, state->f14) &&
            !func_002ACBC8(D_00189EA0, state->f18)) {
            self->mode = 1;
            self->f78 = 0x24C102;
            if (self->anim != 1)
                func_002A7470(self, 1, 0, 0);
            self->f98 = 0;

            /* Release the group's members. */
            if (D_L14_001FB060[group = state->group] && func_002A8508(group, -1) >= 2) {
                unsigned short *list;

                list = (unsigned short *)D_L14_001FB060[state->group];
                base = D_L14_001B259C_direct;
                do {
                    entry = *list;
                    other = (PrisonEntity *)(base + ((entry & 0x7FFF) << 8));
                    other->flags &= 0xFFBC;
                } while ((group = (short)*list++) >= 0);
            }
        } else if (func_002ACBC8(D_00189EA0, state->f14)) {
            self->mode = 5;
        }

        for (i = 0; i < 4; i++) {
            int id = state->linked[i];

            if (id != -1) {
                other = (PrisonEntity *)(D_L14_001B259C_gp + (id << 8));
                if (other->f95 || (s8)other->mode < 0) {
                    if (state->f10) {
                        self->mode = 2;
                        qcopy(temp, self->pos);
                        temp[2] += 1.0f;
                        prisonStartSound(2, 0, self);
                        func_002ABBB8(self, D_L14_001A8F20, temp, 0.0f, 0.0f, 10, 3, 16,
                            4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
                        return;
                    }
                    self->mode = 1;
                    if (self->anim != 1)
                        func_002A7470(self, 1, 0, 0);
                    self->f98 = 0;
                }
            }
        }
    }

    if (self->mode == 1 && (self->animFlags & 2)) {
        self->mode = 3;
        self->f78 = 0x224C1;
        if (self->anim != 2)
            func_002A7470(self, 2, 0, 0);
    }

    if (self->mode == 2) {
        temp[0] = func_00283180(self->angle - 1.57079649f) * 0.3f;
        temp[1] = func_00283198(self->angle - 1.57079649f) * 0.3f;
        temp[2] = 0;
        func_00282CC0(self->pos, self->pos, temp);
        qcopy(front, self->pos);
        qcopy(left, self->pos);
        qcopy(right, self->pos);
        front[2] += 0.75f;
        left[2] += 0.75f;
        right[2] += 0.75f;
        temp[0] = func_00283180(self->angle) * 0.8f;
        temp[1] = func_00283198(self->angle) * 0.8f;
        temp[2] = 0;
        temp[0] = func_00283180(self->angle + 3.14159298f) * 0.8f;
        temp[1] = func_00283198(self->angle + 3.14159298f) * 0.8f;
        temp[2] = 0;
        func_00282CC0(left, left, offset1);
        func_00282CC0(right, right, offset2);
        if (func_00277258(front, 0.6f, 0, self) || func_00277258(left, 0.68f, 0, self) || func_00277258(right, 0.68f, 0, self)) {
            prisonStartSound(2, 0, self);
            func_002ABBB8(self, D_L14_001A8F20, front, 0.0f, 0.0f, 10, 3, 16,
                4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
            func_0029F338(self);
            return;
        }
    }

    if (self->mode == 3 && func_002ACBC8(D_00189EA0, state->f14)) {
        self->mode = 4;
        if (self->anim != 3)
            func_002A7470(self, 3, 0, 0);
    }

    if (self->mode == 4 && (self->animFlags & 2)) {
        self->mode = 5;
        self->f98 = self->next[4];
        if (self->anim)
            func_002A7470(self, 0, 0, 0);
    }
}


/* func_L14_00430410 is defined in L14_00430410-g8.c. */

extern float func_2F6DA0(float x);

float func_L14_00430898(float x)
{
    return func_2F6DA0(x * 0.15915494f) * 6.2831855f;
}

/* Builds a camera-facing quad and rotates its texture coordinates about their center. */
void func_L14_004308D0(void *position, int texture, int color, int mode,
                     float scale, float distance, float angle)
{
    PrisonQuad q;
    float xy[2];
    float forward[4], right[4], up[4], center[4], offset[4];
    PrisonMatrix matrix;
    float c, s;
    int i, j;
    char *u, *v;
    float (*dst)[4], (*mat)[4];

    func_00281DE8(&q, texture, mode, 128);
    q.mode = 5;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = color;
    q.uv[0][0] = 0; q.uv[0][1] = 0;
    q.uv[1][0] = 0; q.uv[1][1] = 1;
    q.uv[2][0] = 1; q.uv[2][1] = 0;
    q.uv[3][0] = 1; q.uv[3][1] = 1;
    c = func_00283180(angle);
    s = func_00283198(angle);
    /* Walk the whole packet so the final cursors remain within its storage. */
    v = (char *)&q + 0x54;
    u = (char *)&q + 0x50;
    for (i = 3; i >= 0; i--) {
        xy[0] = *(float *)u - 0.5f;
        xy[1] = *(float *)v - 0.5f;
        *(float *)u = xy[0] * c - xy[1] * s;
        *(float *)v = xy[0] * s + xy[1] * c;
        *(float *)u += 0.5f;
        u += 8;
        *(float *)v += 0.5f;
        v += 8;
    }
    qcopy(center, position);
    func_00282CF0(forward, D_L14_001B9500, center);
    func_00282F20(forward, forward, 1.0f);
    func_00282DD8(right, forward, D_0018A0E0);
    func_00282F20(right, right, 1.0f);
    func_00282DD8(up, right, forward);
    func_00282D30(offset, forward, distance);
    func_00282CC0(center, center, offset);
    matrix.v[0] = D_L14_001B1A00.v[0];
    matrix.v[1] = D_L14_001B1A00.v[1];
    matrix.v[2] = D_L14_001B1A00.v[2];
    matrix.v[3] = D_L14_001B1A00.v[3];
    dst = q.pos;
    mat = (float (*)[4])&matrix;
    for (j = 3; j >= 0; j--, dst++) {
        func_00282D30(*dst, *mat, scale);
        mat++;
        func_002830C0(*dst, *dst, forward);
    }
    func_002FC560(0x47, 0x53001);
    func_00280B90(&q, 0, 0);
    func_002FC560(0x47, 0x5360B);
}

/* func_L14_00430B70 is defined in L14_00430B70-visual.c. */

INCLUDE_ASM("asm/levels", func_L14_00430E08);

INCLUDE_ASM("asm/levels", func_L14_004321C0);

extern void func_002A7750(void *, int, int);
extern int func_002A7820(int, int);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern char D_00188660[];
extern void func_L14_00432450(void *);

void func_L14_004321D0(char *object)
{
    int *state = *(int **)(object + 0x68);
    switch ((unsigned char)object[0x20]) {
    case 0:
        state[10] += 63;
        state[11] += 63;
        state[12] += 63;
        state[13] += 63;
        state[14] += 63;
        state[15] = 10;
        state[16] = -1;
        func_002A7750(object, 1, -1);
        break;
    case 1:
        func_002A7750(object, func_002A7820(2, 3), -1);
        break;
    case 2:
        if (func_002B3868(object)) {
            if (state[16] != -1 && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner == object && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
                func_002E59F8(state[16]);
            state[16] = -1;
            state[3] = func_002A7820(state[0], state[1]);
        }
        if (((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner != object || !((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
            state[16] = prisonStartSound(0, 4, object);
        if (func_00282948(state + 3))
            func_002A7750(object, 1, -1);
        break;
    case 3:
        if (func_002B3868(object)) {
            if (state[16] != -1 && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner == object && ((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
                func_002E59F8(state[16]);
            state[16] = -1;
            state[3] = func_002A7820(state[0], state[1]);
        }
        if (((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->owner != object || !((PrisonSoundAnchor *)(D_00188660 + state[16] * 112))->active)
            state[16] = prisonStartSound(1, 4, object);
        if (func_00282948(state + 3))
            func_002A7750(object, 1, -1);
        break;
    }
    func_L00_002E6EF8(func_L14_00432450, object);
}
