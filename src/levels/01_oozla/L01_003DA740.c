#include "common.h"

typedef struct { u8 data[256]; } AttachObject;
extern AttachObject *D_L01_001B255C __attribute__((sda));
extern u8 *D_L01_001FE180[] NOT_SDA;
extern f32 func_00282E80(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282FB8(void *, void *, f32);
extern s32 func_002A8AF0(void *, void *, s32);


extern void func_L01_003DC8B8(u8 *, void *, void *);
extern void func_L01_003DC9E0(void *, void *);
extern void func_L01_003DC9A8(void **, s32 *);
extern s32 func_L01_00321178(void *, void *);
extern void func_L01_00318638(void *, void *, void *);

extern s32 func_310648();

extern f32 func_310580(f32 x, f32 y);

extern s32 func_310528(s32 a, s32 b);

extern f32 func_2E3A48(f32 x);

extern f32 func_2E3A60(f32 x);

extern void func_2E3470(void *a, void *b, void *c);

extern void func_32EF38(void *buf, s32 a1, s32 a2, s32 a3, f32 x, f32 y);

extern void func_00115484(void *buf, s32 value, s32 count);

extern s32 func_00277F48(f32 radius, void *pos, s32 flag, void *obj, s32 arg);

/* The level's table of the records the spawner looks through. */
extern u32 D_L01_001C3980[];

/* func_L01_003DA740 is in L01_003DA740-particles-g8.c. */

/* func_L01_003DAB98 is in L01_003DAB98-g8.c. */

INCLUDE_ASM("asm/levels", func_L01_003DAE58);

/* Scatters the measured primitive around the object, a1 times. */

/* func_L01_003DBCB8 is defined in L01_003DBCB8-qcopy-barrier.c. */

/* func_L01_003DBF38 is defined in L01_003DBF38-qcopy-barrier.c. */

INCLUDE_ASM("asm/levels", func_L01_003DC078);

/* func_L01_003DC838 is defined in L01_003DA740-g8.c (this unit has no $gp access for it). */

/* Marks the records of type 0xA26 the object finds and collects them in a1. */
void func_L01_003DC8B8(u8 *a0, void *a1, void *a2) {
    s32 i;
    s32 n;
    u32 **out = a1;
    s32 *count = a2;

    func_00115484(out, 0, 4);
    *count = 0;
    n = func_00277F48(3.0f, a0 + 0x10, 1, a0, 0);
    if (n <= 0)
        return;
    for (i = 0; i < n; i++) {
        if (D_L01_001C3980[i] == 0)
            continue;
        if (*(s16 *)(D_L01_001C3980[i] + 0xAA) != 0xA26)
            continue;
        *(s32 *)(D_L01_001C3980[i] + 0x9C) = 1;
        *(u8 *)(D_L01_001C3980[i] + 0xBC) = 1;
        out[*count] = D_L01_001C3980[i];
        *count = *count + 1;
        if (*count >= 16)
            return;
    }
}

void func_L01_003DC9A8(void **a0, s32 *a1) {
    s32 i;

    for (i = 0; i < *a1; i++) {
        *(s32 *)((u8 *)*a0 + 0x9C) = 0;
        a0++;
    }
}


void func_L01_003DC9E0(void *arg, void *fallback) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 matrix[16] __attribute__((aligned(16)));
    u8 *obj = arg;
    u8 *state = *(u8 **)(obj+0x68);
    u8 *target;
    u8 *path;
    s32 index = *(s32 *)(state+0x410);
    if (index != -1) {
        target = (u8 *)&D_L01_001B255C[index];
        if (!target) return;
        if (*(s16 *)(target+0xAA) == 0xA56) {
            if (func_00282E80(obj+0x10,target+0x10)>1.0f) {
                func_00282CF0(delta,obj+0x10,target+0x10);
                func_00282F20(delta,delta,1.0f);
                func_00282CC0(pos,target+0x10,delta);
            } else qcopy(pos,obj+0x10);
            if (pos[2] < *(f32 *)(target+0x18)+0.01f)
                pos[2] = *(f32 *)(target+0x18)+0.011f;
        } else if (*(s16 *)(target+0xAA) == 0xA53) {
            func_00283698(matrix,target+0xC0);
            func_00282CF0(delta,obj+0x10,target+0x10);
            func_002830C0(delta,delta,matrix);
            if (delta[0]>2.0f) delta[0]=2.0f;
            else if (delta[0]<-2.0f) delta[0]=-2.0f;
            if (delta[1]>5.0f) delta[1]=5.0f;
            else if(delta[1]<-5.0f) delta[1]=-5.0f;
            if (delta[2]<0.01f) delta[2]=0.01f;
            func_00283098(delta,delta,target+0xC0);
            func_00282CC0(pos,target+0x10,delta);
        } else qcopy(pos,obj+0x10);
        func_00282CF0(delta,pos,obj+0x10);
        func_00282FB8(delta,delta,0.10000000894069671631f);
        func_00282CC0(obj+0x10,obj+0x10,delta);
        if (*(f32 *)(obj+0x18)<pos[2]) *(f32 *)(obj+0x18)=pos[2]+0.001f;
    } else {
        s32 pathIndex=*(s32 *)(state+0x1FC);
        if(pathIndex!=-1) {
            path=D_L01_001FE180[pathIndex];
            if(path && !func_002A8AF0(obj+0x10,path+0x10,*(s32 *)path)) qcopy(obj+0x10,fallback);
        }
        {
            u8 *other = *(u8 **)(state + 0x248);
            if (other && (*(s16 *)(other + 0xAA) == 0xA56 ||
                          *(s16 *)(other + 0xAA) == 0xA53))
                *(s32 *)(state + 0x410) = (AttachObject *)other - D_L01_001B255C;
        }
    }
}




INCLUDE_ASM("asm/levels", func_L01_003DCE70);

INCLUDE_ASM("asm/levels", func_L01_003DCF40);

/* func_L01_003DD3A0 is in L01_003DD3A0.c. */

/* func_L01_003DD6A8 */
extern void func_002AB8C0(void *, void *);

extern void func_00282978(void *);

extern s32 func_00282948(void *);

extern void func_002B0990(void *, void *, s32, s32, f32);

void func_L01_003DD6A8(u8 *a0)
{
    u32 v;
    u8 *p = *(u8 **)(a0 + 0x68);

    func_002AB8C0(a0, p + 0x100);
    v = *(u16 *)(a0 + 0x96);
    if (v <= 0xFFFE) {
        *(u16 *)(a0 + 0x96) = v + 1;
    }
    func_00282978(p + 0x3D8);
    func_00282948(p + 0x404);
    func_00282978(p + 0x3D6);
    v = *(s16 *)(p + 0x3DA);
    if (v != 0) {
        *(u16 *)(p + 0x3D6) = 0x168;
        *(s16 *)(p + 0x3DA) = 0;
    }
    func_002B0990(a0, p + 0x300, 1, 1, 1.8f);
}

INCLUDE_ASM("asm/levels", func_L01_003E8ED8);

INCLUDE_ASM("asm/levels", func_L01_003EC0C0);

INCLUDE_ASM("asm/levels", func_L01_003ECCF8);

INCLUDE_ASM("asm/levels", func_L01_00405300);

INCLUDE_ASM("asm/levels", func_L01_0040EED0);

INCLUDE_ASM("asm/levels", func_L01_0040F118);

void func_L01_0040F340(u8 *a0) {
    if (*(u8 *)(a0 + 0x20) == 0) {
        *(u8 *)(a0 + 0x30) = 0xFF;
        *(u8 *)(a0 + 0x20) = 1;
    }
}

INCLUDE_ASM("asm/levels", func_L01_0040F360);

INCLUDE_ASM("asm/levels", func_L01_0040F5A8);

INCLUDE_ASM("asm/levels", func_L01_0040F958);

INCLUDE_ASM("asm/levels", func_L01_00410AD0);

/* func_L01_00412E00 is defined in L01_00412E00-flags-g8.c. */

/* func_L01_00412F18 is defined in L01_00412F18-g8.c. */

INCLUDE_ASM("asm/levels", func_L01_00416440);



/* func_L01_00416C08 is in L01_003DA740-rings-g8.c. */

/* func_L01_00416E78 is in L01_00416E78-camera.c. */

INCLUDE_ASM("asm/levels", func_L01_004171C8);

void func_L01_0041C960(u8 *a0) {
    *(u16 *)(a0 + 0x34) |= 0x802;
}

INCLUDE_ASM("asm/levels", func_L01_0041C970);

INCLUDE_ASM("asm/levels", func_L01_0042C450);

INCLUDE_ASM("asm/levels", func_L01_0042C540);

INCLUDE_ASM("asm/levels", func_L01_0042C8D8);

/* func_L01_0042CE78 */
typedef struct L01_0042CE78_ENTRY {
    char pad0[0x38];
    u8 f38;
    u8 f39;
} L01_0042CE78_ENTRY;

typedef struct L01_0042CE78_OBJ {
    char pad0[0x84];
    s16 f84;
} L01_0042CE78_OBJ;

extern u8 *D_L01_001B1F04 __attribute__((sda));

extern s32 func_L00_004290C0(void *);

s32 func_L01_0042CE78(L01_0042CE78_OBJ *a0, u8 *a1)
{
    L01_0042CE78_ENTRY *e = *(L01_0042CE78_ENTRY **)(D_L01_001B1F04 + a0->f84 * 0x20 + 0x1C);
    s32 r;

    if (e->f39 != 0) {
        r = -1;
    } else if (e->f38 != 0) {
        r = 1;
    } else if (a1 != 0 && *(s16 *)(a1 + 0x7E) == 0) {
        r = 0;
    } else {
        if (func_L00_004290C0(a0) != 0) {
            goto one;
        }
        goto zero;
    one:
        r = 1;
        return r;
    zero:
        r = 0;
        return r;
    }
    return r;
}
