#include "include_asm.h"
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139574;
extern char *D_0018C0B0 NOT_SDA;
extern int D_L06_001AC790 __attribute__((sda));
extern Collision D_L06_001BFC80;
extern Material D_L06_0026C7F0[];
extern void func_00282CC0(char *, char *, char *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_L00_0038F3D8(void *);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_00283028(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00282948(char *);
extern void func_002FEE50(int);
extern void func_L00_0038DE70(void *, void *, void *);
extern void func_L00_0038E880(void *, void *, void *);


INCLUDE_ASM("asm/levels", func_L06_0033BDC0);


/* Implemented in L06_00361728-helpers.c. */

/* func_L06_003660F0 is matched in L06_003660F0.c (built with -mno-split-addresses). */


INCLUDE_ASM("asm/levels", func_L06_00396268);

/* func_L06_003C5ED8 is in L06_003C5ED8.c. */

/* func_L06_003D0AC8 is defined in L06_003D0AC8.c. */

void func_L06_003D0EE0(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    func_00282CC0(position, position, ctx);
    func_002AFFD8(position, &frame.surface, 0);
    func_00282D30(&frame.surface, &frame.surface, 0.0003055556f);
    func_L00_0038F3D8(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + D_L06_0026C7F0)->material;
    qcopy(&frame.packet.vector, ctx);
    func_00282F70(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (func_002761F8(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &D_L06_001BFC80;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == D_0018C0B0 || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &D_L06_001BFC80;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L06_001AC790 && *(short *)(model + 0xAA) != 0x336)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            func_00283028(&frame.velocity, ctx, &reread->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &D_L06_001BFC80;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            func_00283028(&frame.velocity, ctx, &collision->normal);
            func_00282F20(&frame.velocity, &frame.velocity, 0.033333335f);
            func_00282F20(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (func_00282948(ctx + 0x18)) {
        obj[0xBC] = 1;
        func_00282CC0((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        func_002FEE50(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            func_L00_0038DE70(obj, &frame.velocity, &frame.normal);
        else
            func_L00_0038E880(obj, &frame.velocity, &frame.normal);
    }
}

INCLUDE_ASM("asm/levels", func_L06_003D64C0);

INCLUDE_ASM("asm/levels", func_L06_003F3448);

extern int func_002A9640(char *a0, int a1, int a2);

extern float func_002A96A0(char *a0, int a1);

extern void func_002AB800(char *a0, char *a1);

extern void func_002A6C58(char *a0, int a1, int a2);

extern void func_002AB8C0(char *a0, char *a1);

/* runs a moby's timer down and picks the dying or the revived path from what is left */
void func_L06_003F3690(char *a0, char *a1)
{
    float t = func_002A96A0(a0, func_002A9640(a0, 0xC30000, 0));

    if (t > 0.0f) {
        float left = *(float *)(a1 + 0x20) - t;

        *(float *)(a1 + 0x20) = left;
        if (left > 0.0f) {
            *(unsigned char *)(a1 + 0x57) = 0x5A;
            func_002AB800(a0, a1 + 0x50);
        } else {
            func_002A6C58(a0, 0, 3);
            *(unsigned char *)(a0 + 0x20) = 2;
            *(unsigned char *)(a1 + 0x57) = 0x78;
            func_002AB800(a0, a1 + 0x50);
        }
    }
    *(unsigned char *)(a0 + 0xA8) = 0xFF;
    func_002AB8C0(a0, a1 + 0x50);
}

extern int func_002A8508(int a0, int a1);

/* counts the 0x75E-slot entries that are live and returns the last free one */
int func_L06_003F3760(int a0, char *a1)
{
    char *s0 = a1;
    int free_slot = -1;
    int i;

    *(unsigned char *)(s0 + 0x81) = func_002A8508(*(int *)(s0 + 0x84), -1);
    for (i = 0; i < 20; i++) {
        char *m = ((char **)(s0 + 0xA0))[i];

        if (m != 0 && *(short *)(m + 0xAA) == 0x75E
            && *(unsigned char *)(m + 0x20) != 0xFE && *(unsigned char *)(m + 0x20) != 0xFD)
            (*(unsigned char *)(s0 + 0x81))++;
        else
            free_slot = i;
    }
    return free_slot;
}

INCLUDE_ASM("asm/levels", func_L06_003F3800);

/* func_L06_003F3EF0 is defined in L06_003F3EF0-helpers.c. */

extern void func_0029F338(char *a0);

/* clears one word of a 0x75D moby's state block when it is neither dying nor gone */
void func_L06_003F4020(char *a0, char *a1)
{
    char *m = *(char **)(a1 + 0x10);

    if (m != 0 && *(short *)(m + 0xAA) == 0x75D
        && *(unsigned char *)(m + 0x20) != 0xFE && *(unsigned char *)(m + 0x20) != 0xFD) {
        int *p = *(int **)(m + 0x68);

        p += *(unsigned char *)(a1 + 0x1C);
        p[40] = 0;
    }
    func_0029F338(a0);
}


extern int D_L06_001B3760[];

/* zeroes the six words a finished moby left behind */
void func_L06_003F4908(char *a0)
{
    if (*(unsigned char *)(a0 + 0x20) == 0) {
        int i;

        for (i = 5; i >= 0; i--)
            D_L06_001B3760[i] = 0;
        func_0029F338(a0);
    }
}

INCLUDE_ASM("asm/levels", func_L06_003FB050);

/* func_L06_003FDA08 is matched in L06_0033BDC0-g8.c (it takes the $gp addresses of small-data objects). */

INCLUDE_ASM("asm/levels", func_L06_003FDEB8);

INCLUDE_ASM("asm/levels", func_L06_003FE178);

/* func_L06_00400498 is in L06_00400498-g8.c. */

INCLUDE_ASM("asm/levels", func_L06_004012B0);

INCLUDE_ASM("asm/levels", func_L06_00401820);

INCLUDE_ASM("asm/levels", func_L06_00402230);

/* func_L06_00403F60 is matched in L06_0033BDC0-g8.c (it reaches a global through $gp). */


INCLUDE_ASM("asm/levels", func_L06_00419CA8);

/* clears one word of a 0xA58 moby's state block when it is neither dying nor gone */
void func_L06_0041CAB0(char *a0, char *a1)
{
    char *m = *(char **)(a1 + 0x10);

    if (m != 0 && *(short *)(m + 0xAA) == 0xA58
        && *(unsigned char *)(m + 0x20) != 0xFE && *(unsigned char *)(m + 0x20) != 0xFD) {
        int *p = *(int **)(m + 0x68);

        p += *(unsigned char *)(a1 + 0x1C);
        p[40] = 0;
    }
    func_0029F338(a0);
}

