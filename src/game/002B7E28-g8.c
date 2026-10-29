#include "include_asm.h"
#include "common.h"

/* func_002BABE8 is in 002B7E28-g8.c.

   It reads the game-time word D_001B1688, whose retail access is the pair
   `lui $v0,%hi(D_001B1688)` / `lw $v0,%lo(D_001B1688)($v0)`: one register for the
   address and the loaded word.  A file built with -G8 (config/cflags.txt) makes the
   compiler emit a bare symbol reference, which the assembler expands into that
   pair; a -G0 unit emits `lui`/`lw` with two different registers instead.  The
   same file holds the clear of the fixed-address word at 0x10000000, which the
   retail reaches through its own `lui`/`sw` pair. */

extern int D_001B1688;

/* The fixed-address word the particle update clears.  Its address is the same in
   every program, so it is named after the address; the incomplete array keeps it
   out of the small-data pool, which is what makes the compiler split the address
   into the retail's `lui`/`sw` pair. */
extern int D_10000000[];

extern void func_002AE838(char *dst, char *src);

extern void func_00282CC0(char *dst, char *a, char *b);

extern float func_00283CE0(int a);

extern int func_00283D38(int a, int b, float f);

extern int func_00282978(short *p);

extern void func_00282D08(float *out, char *a, char *b, float f);

extern void func_002B9180(void *p);

typedef struct {
    float v[4];
} Vec4_002BABE8;

void func_002BABE8(char *self)
{
    char *s2 = self;
    char *s3 = self + 0x20;
    Vec4_002BABE8 t0, t1, t2;
    float f;

    if (D_001B1688 & 1) {
        *(unsigned char *)(s2 + 8) = *(unsigned char *)(s2 + 8) + 1;
    }
    if (*(short *)(s3 + 0x10) != 0) {
        D_10000000[0] = 0;
        func_002AE838((char *)&t0, s3);
        func_00282CC0(s2 + 0x10, s2 + 0x10, (char *)&t0);
        f = func_00283CE0(*(short *)(s2 + 0xA)) / func_00283CE0(*(short *)(s3 + 0x10));
        *(int *)(s2 + 4) = func_00283D38(*(int *)(s3 + 8) & 0xFFFFFF, *(int *)(s3 + 8), 1.0f - f);
        *(float *)(s2 + 0xC) = (float)(*(short *)(s3 + 0x16) * 1000);
        if (func_00282978((short *)(s2 + 0xA)) != 0) {
            *(short *)(s3 + 0x10) = 0;
            *(short *)(s2 + 0xA) = *(unsigned short *)(s3 + 0x12);
        }
    } else if (*(short *)(s3 + 0x12) != 0) {
        func_002AE838((char *)&t1, s3);
        func_002AE838((char *)&t2, s2 + 0x24);
        f = func_00283CE0(*(short *)(s2 + 0xA)) / func_00283CE0(*(short *)(s3 + 0x12));
        func_00282D08((float *)&t0, (char *)&t2, (char *)&t1, f);
        func_00282CC0(s2 + 0x10, s2 + 0x10, (char *)&t0);
        *(float *)(s2 + 0xC) = ((float)(*(short *)(s3 + 0x16) - *(short *)(s3 + 0x18)) * f
                               + (float)*(short *)(s3 + 0x18)) * 1000.0f;
        *(int *)(s2 + 4) = func_00283D38(*(int *)(s3 + 0xC), *(int *)(s3 + 8), f);
        if (func_00282978((short *)(s2 + 0xA)) != 0) {
            *(short *)(s3 + 0x12) = 0;
            *(short *)(s2 + 0xA) = *(unsigned short *)(s3 + 0x14);
        }
    } else {
        func_002AE838((char *)&t0, s2 + 0x24);
        func_00282CC0(s2 + 0x10, s2 + 0x10, (char *)&t0);
        *(int *)(s2 + 4) = func_00283D38(*(int *)(s3 + 0xC) & 0xFFFFFF, *(int *)(s3 + 0xC),
                                         func_00283CE0(*(short *)(s2 + 0xA))
                                             / func_00283CE0(*(short *)(s3 + 0x14)));
        *(float *)(s2 + 0xC) = (float)(*(short *)(s3 + 0x18) * 1000);
        if (func_00282978((short *)(s2 + 0xA)) != 0) {
            func_002B9180(s2);
        }
    }
}

/* One step of a dialogue script: a node array of 28-byte records, the current node
   index at +0x36 of the script state. */
typedef struct {
    int message;
    unsigned short sound;
    short next;
    short kind;
    short arg;
    short ifTrue;
    short ifFalse;
    unsigned short flags;
    char pad12[0xA];
} DialogNode_002B8108;

typedef struct {
    char pad0[4];
    short prev;
    char pad6[2];
    unsigned char skippable;
    char pad9[0x2D];
    short cur;
    int startTime;
    DialogNode_002B8108 *nodes;
} DialogState_002B8108;

typedef struct {
    char *s[6];
} Separators_002B8108;

typedef struct {
    char pad0[0x80];
    int cost;
    char pad84[0x10];
    unsigned short price;
    char pad96[0x4A];
} ClassRecord_002B8108;

/* The talking moby, its dialogue state and the message on screen: 002F5220-g8.c
   reads the moby and state fields of the same block.  Being one aggregate (not
   three scalars) is what keeps retail's stores ahead of the following node loads. */
typedef struct { int unk0; char *moby; void *data; int unkC; int message; } DialogTalk_002B8108;
extern DialogTalk_002B8108 D_001B178C MACRO_ADDR;
extern int D_001AA2B8 __attribute__((sda));
extern Separators_002B8108 D_001AA250;
extern char D_001AA278[];
extern char D_001AA288[];
extern int D_001A79F8;
extern short D_001A7A1A;
extern unsigned char D_001A7BB4;
extern unsigned char D_00139568[];
extern ClassRecord_002B8108 D_00239BA0[];
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern unsigned char D_001A7B30[] MACRO_ADDR;

extern int func_002B49E0(int, int, int, int, int);
extern int func_002B0D70(void);
extern void func_0028BCA0(char *);
extern int func_0028B5D0(int);
extern char *func_00288FB8(int);
extern char *func_00115690(char *, const char *);
extern char *func_001163E0(const char *, const char *);
extern int func_00115DA8(char *, const char *, ...);

/* The class-record lookups are written index-first, i[D_00139568] and
   (j)[D_00239BA0]: retail adds each index to its base in that operand order
   (blocker 28), which is also what orders the loads in the switch cases. */
void func_002B8108(char *owner, DialogState_002B8108 *st, int enter)
{
    DialogNode_002B8108 *node = &st->nodes[st->cur];
    char text[0x100];
    Separators_002B8108 seps;
    char number[0x20];
    short kind;
    int cond;
    short next;

    if (st->nodes == 0) {
        return;
    }
    if (enter) {
        st->prev = st->cur;
        st->startTime = D_001B1688;
        if (st->cur != node->next) {
            unsigned short flags = node->flags;
            st->cur = node->next;
            node = &st->nodes[st->cur];
            st->skippable = node->flags & 1;
            if (flags & 4) {
                unsigned short sound;
                D_001B178C.moby = owner;
                D_001B178C.data = st;
                sound = node->sound;
                if (sound & 0x4000) {
                    func_002B49E0(1, 1, 0, (short)(sound ^ 0x4000), 0);
                } else {
                    func_002B49E0(2, 1, (short)sound, 0, 0);
                }
            }
        }
    }
    if (st->cur == -1) {
        return;
    }
    D_001B178C.message = node->message;
    kind = node->kind;
    if (kind == 6) {
        seps = D_001AA250;
        func_00115690((char *)0x70000000, func_00288FB8(node->message));
        {
            char *p = func_001163E0((char *)0x70000000, D_001AA288);
            if (p != 0) {
                p[1] = 's';
            }
        }
        {
            int price = (node->arg[D_00139568])[D_00239BA0].price;
            func_00115DA8(number, D_001AA278, price / 1000, seps.s[D_001A7BB4 % 6], price % 1000);
        }
        func_00115DA8(text, (char *)0x70000000, number);
    } else {
        func_00115DA8(text, func_00288FB8(node->message));
    }
    if (D_001B178C.message != 0) {
        func_0028BCA0(text);
    } else if (D_001AA2B8 != -1) {
        func_0028B5D0(D_001AA2B8);
        D_001AA2B8 = -1;
    }
    if (node->kind == 0) {
        return;
    }
    switch (node->kind) {
    case 1:
        cond = D_001A79F8 >= (node->arg[D_00139568])[D_00239BA0].cost;
        break;
    case 2:
        cond = D_001A7AF8[node->arg] != 0;
        break;
    case 3:
        cond = D_001A7AF8[node->arg] != 0 && D_001A7B30[node->arg] == 0;
        break;
    case 5:
        cond = func_002B0D70() >= node->arg;
        break;
    case 6:
        cond = D_001A79F8 >= (node->arg[D_00139568])[D_00239BA0].price && func_002B0D70() >= 4;
        break;
    case 7:
        cond = D_001A7A1A >= node->arg;
        break;
    default:
        cond = 0;
        break;
    }
    if (cond) {
        next = node->ifTrue;
    } else {
        next = node->ifFalse;
    }
    if (next != st->cur) {
        st->cur = next;
        st->startTime = D_001B1688;
        node = &st->nodes[next];
        st->skippable = node->flags & 1;
        func_002B8108(owner, st, 0);
    }
}
