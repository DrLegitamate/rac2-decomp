#include "include_asm.h"
#include "common.h"

extern void func_002F0538(int);

extern void func_002E7D48(int, int, int, int);

extern unsigned int D_L00_001B18D4;

extern short D_L00_001B267E;

extern void func_002E5C40(void);

void func_L00_0037F790(void)
{
    func_002F0538(0);
    func_002E7D48(0, 0, 0, 0x80);
    if (D_L00_001B267E != 0)
        D_L00_001B18D4 = 0x100FF;
    else
        D_L00_001B18D4 = 0x70;
    func_002E5C40();
}

typedef int Quad __attribute__((mode(TI)));
extern int func_001163B0(void);
extern void func_001163A0(int);
extern float func_002A78D8(float,float);
extern float func_002A7878(float,float);
extern int func_00283D38(int,int,float);
extern int func_002A77E0(int);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void *func_002C3150(void *,void *,int,int,float,int,int);
extern int D_L00_001AEE48 __attribute__((sda));
extern int D_L00_001AEE50[2];
extern float D_L00_001AEE58 __attribute__((sda));
extern float D_L00_001AEE5C;
extern float D_L00_001AEE60[2];
extern char D_L00_001B8DC0[];
extern char D_L00_001A8F20[] MACRO_ADDR;

void func_L00_00385040(char *object)
{
    union { Quad q; float f[4]; } vectors[2];
    char *state=*(char **)(object+0x68);
    int saved=func_001163B0();
    int i=0;
    func_001163A0(*(int *)(state+0x68));
    while(i<D_L00_001AEE48) {
        float speed,blend;
        int color;
        unsigned char random;
        vectors[1].q=0;
        vectors[1].f[0]=20.0f;
        i++;
        vectors[1].f[1]=func_002A78D8(0.0f,D_L00_001AEE58);
        vectors[1].f[2]=func_002A78D8(0.0f,D_L00_001AEE5C);
        vectors[0].q=vectors[1].q;
        func_00283098(&vectors[0],&vectors[0],D_L00_001B8DC0 + 0x230);
        func_00282CC0(&vectors[0],&vectors[0],D_L00_001B8DC0);
        speed=func_002A7878(D_L00_001AEE60[0],D_L00_001AEE60[1]);
        blend=func_002A7878(0.0f,1.0f);
        color=func_00283D38(D_L00_001AEE50[0],D_L00_001AEE50[1],blend);
        random=func_002A77E0(255);
        func_002C3150(&vectors[0],D_L00_001A8F20,color,2,speed,random,0);
    }
    func_001163A0(saved);
}
