/* Retained exact-C reconstruction: 928/924 bytes.
 * Profile: -O2 -G0 -ffunction-sections -frac2-zero-ti-por.
 * US and US2 0/3; PAL absent. The complete joint-matrix query and particle phases retain the eight-GPR/three-FPR C65A0 contract and six-GPR/three-FPR A8C28 interface. A real matrix-basis lifetime plus qcopy recovers the frame/head. Typed EE-bank interleaving recovers the three query setups. Basis/object priorities, local store ordering and final particle constants still differ.
 * No strict linked match. Reopen with independent source, allocation or
 * compiler evidence for the remaining difference; do not repeat tied forms.
 */
#include "common.h"
typedef int EffectQuad __attribute__((mode(TI)));
extern void func_0029FC20(void *,int,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002A8C28(void *,void *,float,int,float,float,int,int,int);
extern void func_002ACB48(void *,float);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern void *func_002C65A0(void *,void *,int,int,int,int,int,int,float,float,float);
extern char *func_002C16C0(void *,void *,int,int,int,int,float,float,float,float,float);
extern int func_002A7820(int,int);
extern unsigned char *D_001F2540[];

void func_00322690(char *object,float *position,int joint,float strength)
{
    float matrix[16] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float delta[4],first[4],second[4],velocity[4];
    float last[4] __attribute__((aligned(16)));
    int i,j;
    float *basis, *axisBase;
    func_0029FC20(object,joint,matrix);
    axisBase = axis;
    basis = matrix+4;
    qcopy(axisBase,basis);
    func_00282CF0(delta,matrix+12,position);
    func_00282F20(first,axisBase,0.85f);
    func_00282F20(second,axisBase,1.6f);
    func_00282CC0(first,first,delta);
    func_00282CC0(second,second,delta);
    {
        float firstZ=first[2];
        float secondZ=second[2];
        secondZ-=0.1f;
        firstZ-=0.1f;
        second[2]=secondZ;
        first[2]=firstZ;
    }
    func_00282F20(velocity,basis,0.25f);
    func_00282CC0(velocity,velocity,position);
    func_002A8C28(object,delta,0.3f,1,strength,1.0f,0,1,0);
    func_002A8C28(object,first,0.3f,1,strength,1.0f,0,1,0);
    func_002A8C28(object,second,0.3f,1,strength,1.0f,0,1,0);
    object = (char *)last;
    for(i=2;i>=0;i--) {
        float start,end,gravity;
        func_002ACB48(delta,0.1f);
        start=func_002A7878(0.2f,0.4f)*210000.0f;
        end=func_002A7878(1.0f,1.5f)*210000.0f;
        gravity=func_002A78D8(0.0f,0.01f);
        func_002C65A0(delta,velocity,7,0x808080,30,127,32,0,start,end,gravity);
    }
    *(EffectQuad *)last=0;
    last[2]=0.1f;
    last[3]=1.0f;
    func_00282CC0(object,object,position);
    for(j=0;j>=0;j--) {
        char *particle=func_002C16C0(first,object,15,60,0x606060,3,105000.0f,21000.0f,1.0f,-0.00019999999494757503f,0.0f);
        if (particle) {
            char *data;
            unsigned char texture = D_001F2540[23][0];
            *(volatile unsigned char *)(particle+3)=0x44;
            *(volatile unsigned char *)(particle+2)=texture;
            if (func_002A7820(0,1)) {
                data=particle+0x20;
                *(volatile unsigned char *)(particle+3)=0x48;
                *(volatile int *)(particle+4)=0x70707F;
                *(volatile short *)(data+0x1E)=127;
                *(volatile unsigned char *)(data+0x11)=0x70;
                *(volatile unsigned char *)(data+0x12)=0x70;
                *(volatile unsigned char *)(data+0x13)=0x70;
            }
        }
    }
}
