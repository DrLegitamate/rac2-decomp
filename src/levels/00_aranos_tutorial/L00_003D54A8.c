#include "include_asm.h"



extern void func_L00_003DA2B0(char *);
extern long long func_0027C878(int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern void func_00283410(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);
typedef struct { char pad[0x140]; float x,y,z; } AimVector10;
extern AimVector10 D_L00_001B8C80;
void func_L00_003DA548(int unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    func_L00_003DA2B0(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_0027C878(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = D_L00_001B8C80.x - *(float *)pos;
    dy = D_L00_001B8C80.y - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_00283248(dx, dy);
    quat[1] = -func_00283248(func_00282E80(pos, &D_L00_001B8C80.x),
                              D_L00_001B8C80.z - *(float *)(pos + 8));
    quat[0] = func_002A7940();
    func_00283410(m, quat);
    func_00282CF0(off, &D_L00_001B8C80.x, pos);
    func_00282F20(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    func_00282D30(pkt, pkt, scale);
    func_00282D30(pkt + 16, pkt + 16, scale);
    func_00282D30(pkt + 32, pkt + 32, scale);
    func_00282D30(pkt + 48, pkt + 48, scale);
    func_00280B90(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    func_00282D30(pkt, pkt, 0.5f);
    func_00282D30(pkt + 16, pkt + 16, 0.5f);
    func_00282D30(pkt + 32, pkt + 32, 0.5f);
    func_00282D30(pkt + 48, pkt + 48, 0.5f);
    func_00280B90(pkt, m, 0);
}



/* Tutorial prompts, interaction locks and traversal visibility. */
extern char D_00189EA0[];
typedef struct { char pad[0x2290]; unsigned char *moby; char pad2[0x238]; int count; } TutorialPlayer;
extern TutorialPlayer D_00189E20;
extern unsigned short D_0018C958[];
extern unsigned short D_0018C840[],D_0018C7B0[],D_0018C828[];
extern int D_001A7A00 __attribute__((sda)),D_001A7398 __attribute__((sda));
extern unsigned char *D_L00_001B1EA8 __attribute__((sda));
typedef struct {int active;char pad[0x20];int id;} TutorialPromptState;
extern TutorialPromptState D_L00_0027D848;
extern float func_00282E48(void *,void *);
extern int func_00312E10(void *);
extern void func_00288E18(int,int);
extern int func_002ACBC8(void *,int);
extern int func_002A8508(int,int),func_00288D58(void),func_00288FB8(int);
extern void func_00285828(int,int,int,int),func_00285788(int,int),func_002B49E0(int,int,int,int,int);
void func_L00_003E7768(unsigned char *object) {
    int *state=*(int **)(object+0x68);
    unsigned char *other;
    switch(object[0x20]) {
    case 0:
        object[0x30]=255; object[0x20]=1; break;
    case 1:
        if(!D_0018C958[0x48/2]) {
            for(other=D_L00_001B1EA8;other;other=*(unsigned char **)(other+0x28)) {
                if(*(short *)(other+0xaa)==0x326 && func_00282E48(other+0x10,D_00189EA0)<10.0f && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x48/2] && !func_00312E10(other)) {
                    if(D_00189E20.count<D_001A7A00) func_00288E18(0x9af,6);
                    else if(func_00282E48(other+0x10,D_00189EA0)<1.0f && !D_0018C958[0x2e8/2]) func_00288E18(0x9e7,0x3e);
                }
            }
        }
        if(func_002ACBC8(D_00189EA0,state[0]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x18/2]) func_00288E18(0x9ab,2);
        if(func_002ACBC8(D_00189EA0,state[1]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x24/2] && !D_0018C958[0x30/2]) {
            if(D_001A7398==30) func_00288E18(0x9ac,3);
            else if(D_001A7398==42) func_00288E18(0x9ad,4);
        }
        if(func_002ACBC8(D_00189EA0,state[3]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x54/2] && !D_0018C958[0x60/2] && !D_0018C958[0x6c/2] && func_002A8508(state[5],-1)) {
            if(D_001A7398==42) func_00288E18(0x9b0,7);
            else if(D_0018C840[0]) func_00288E18(0x9b1,8);
            else func_00288E18(0x9b2,9);
        }
        if(func_002ACBC8(D_00189EA0,state[2]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1) {
            if(func_00288D58() && !D_0018C958[0x5a0/2]) {
                int first,second;
                D_0018C958[0x5a0/2]=1;
                first=func_00288FB8(0x112b);second=func_00288FB8(0xa21);
                func_00285828(first,0,second,1);func_00285788(0x40,0);func_002B49E0(4,1,10,0,0);
            } else if(!func_00288D58() && !D_0018C958[0x3c/2] && !D_0018C7B0[0]) func_00288E18(0x9ae,5);
        }
        if(func_002ACBC8(D_00189EA0,state[4]) && !D_0018C828[0] && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x78/2]) func_00288E18(0x9b3,10);
        break;
    }
    D_00189E20.moby[0x7e]|=1;
    { unsigned char *scan; for(scan=D_L00_001B1EA8;scan;scan=*(unsigned char **)(scan+0x28)) if(*(short *)(scan+0xaa)==0xac1) scan[0x7e]|=1; }
    if(func_002ACBC8(D_00189EA0,state[6]) || func_002ACBC8(D_00189EA0,state[7])) D_00189EA0[0x2470]=1;
    else D_00189EA0[0x2470]=0;
}

INCLUDE_ASM("asm/levels", func_L00_003EACC0);

extern int func_002ACBC8(void *a0, int a1);
extern char D_00189EA0[];
extern float D_L00_001B1AE8 __attribute__((sda));

void func_L00_003EB3B8(void *a0) {
    int result = func_002ACBC8(D_00189EA0,
                               *(int *)*(int *)((char *)a0 + 0x68));
    if (result != 0) {
        D_L00_001B1AE8 = 30.0f;
    } else {
        D_L00_001B1AE8 = 95.0f;
    }
}

INCLUDE_ASM("asm/levels", func_L00_003EE288);

INCLUDE_ASM("asm/levels", func_L00_0040D648);

INCLUDE_ASM("asm/levels", func_L00_0040EAA0);

INCLUDE_ASM("asm/levels", func_L00_00412E68);

void func_L00_00419B80(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419BA8(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419BD0(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419BF8(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419C20(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419C48(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419C70(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}
