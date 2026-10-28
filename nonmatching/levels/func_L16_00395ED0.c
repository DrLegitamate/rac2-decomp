/* Near miss, worker w3 batch 3: 532/532 B, frame 0xE0 equal, 0/2 with ONE swap. Profile `-O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier` (no -mno-split-addresses); the vectors are `float X[] __attribute__((sda))` (macro loads), D_34B0[0] is read through the SDATA alias (gp). Left: `addiu $a1,$s0,0x50` and `mov.s $f12,$f20` swapped before the func_002AA548 call. A prototype that lists the float before the second pointer matches but misdescribes the matched func_002AA548, so it is not used. */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef union { Vector128 bits; float f[4]; } Vector;
typedef struct { Vector128 rotation[3], source[3], quaternion, angles; Vector position; } BlendWorkspace;
extern float func_002AA548(float *,float *,float,float,float,float);
extern void func_002833F0(void *,void *);
extern float func_00283248(float,float);
extern float func_00282E20(void *);
extern float func_002AA150(float,float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00283810(void *,void *,void *,float);
extern void func_00283958(void *,void *);
extern void func_002AB6D8(float *,float *);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern float D_L16_001B3490[] __attribute__((sda));
extern float D_L16_001B34A0[] __attribute__((sda));
extern float D_L16_001B34B0[] __attribute__((sda));
extern float D_L16_001B34C0[] __attribute__((sda));
void func_L16_00395ED0(char *object)
{
    BlendWorkspace local;
    char *state=*(char **)(object+0x68);
    float startAngle,endAngle,startLength,endLength,startHeight,endHeight,angle,length;
    float *position;
    if (*(int *)(state+4)==-1) return;
    if (*(float *)(state+0x4c)<1.0f) func_002AA548((float *)(state+0x4c),(float *)(state+0x50),1.0f,0.0001850000117f,0.0001850000117f,0.01110000070f);
    func_002833F0(local.source,state+0x20);
    if (*(float *)(state+0x4c)<1.0f) {
        startAngle=func_00283248(D_L16_001B34B0[0],D_L16_001B34B0[1]);
        endAngle=func_00283248(D_L16_001B34C0[0],D_L16_001B34C0[1]);
        startLength=func_00282E20(D_L16_001B34B0);
        endLength=func_00282E20(D_L16_001B34C0);
        startHeight=D_L16_001B34B0[2]; endHeight=D_L16_001B34C0[2];
        angle=func_002AA150(startAngle,endAngle,*(float *)(state+0x4c));
        length=(endLength-startLength)*(*(float *)(state+0x4c))+startLength;
        local.position.f[0]=func_00283180(angle)*length;
        local.position.f[1]=func_00283198(angle)*length;
        local.position.f[2]=0.0f;
        local.position.f[2]=(endHeight-startHeight)*(*(float *)(state+0x4c))+startHeight;
    } else { qcopy(&local.position,D_L16_001B34C0); }
    position=local.position.f;
    func_00283098(position,position,local.source);
    func_00282CC0(position,position,state+0x10);
    func_00283810(&local.quaternion,D_L16_001B3490,D_L16_001B34A0,*(float *)(state+0x4c));
    func_00283958(&local.quaternion,local.rotation);
    func_002AB6D8((float *)local.rotation,(float *)&local.angles);
    func_00335370(position);
    func_003353C8(&local.angles);
}
