/* Retained exact-C attempt: 672/672 bytes.
 * Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * US, US2 and PAL each 0/1. The initializer retains all ten child updates, twelve default floats and repeated target-field updates. Captured table/default pointers recover the frame and size. Entry flag-mask scheduling and pointer operand/allocation differences remain.
 * Local checks only; no strict linked match. Reopen with independent
 * source, allocation or assembler evidence for the stated difference.
 */
#include "common.h"
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern void func_L11_00437DC0(void *,int,int,int);
extern void func_L11_00437E68(void *,int,int,int);
extern void func_002A04B8(void *,int *,int *,int *);
extern void func_002A0488(void *,int,int,int);
extern void func_L11_0043A9D8(void *);
extern char *D_L11_001B359C NOT_SDA;
extern float D_L11_001B1240[] SDATA(D_L11_001B1240);
#define DATA(p) (*(char *volatile *)((p)+0x68))
#define MODEL(p) (table + (*(int *)(DATA(p)+0x358) << 8))
#define FLAGS(p) (*(volatile unsigned short *)((p)+0x34))

void func_L11_00439950(char *object)
{
    int red,green,blue;
    char *state=DATA(object);
    int i;
    unsigned short flags;
    float *defaults;
    char *table;
    char *reset;
    *(unsigned char *)(state+0x2E)=1;
    *(float *)(state+0x20)=(float)*(short *)(state+0x24);
    *(unsigned char *)(object+0x31)=1;
    flags = FLAGS(object) & 0xFFFE;
    FLAGS(object) = flags;
    flags = (flags|0x1000)&0xFFB9;
    FLAGS(object) = flags;
    *(int *)(object+0x98)=*(int *)(*(char **)(object+0x24)+0x10);
    *(unsigned char *)(object+0x7F)=0;
    *(short *)(state+0x378)=10;
    func_002A7750(object,2,0);
    if (*(unsigned char *)(object+0x43))
        func_002A7470(object,0,0,0);
    func_L11_00437DC0(object,1,0,0);
    i=0;
    func_L11_00437E68(object,1,0,0);
    reset = state + 0x380;
    *(short *)(state+0x374)=-1;
    func_002A04B8(object,&red,&green,&blue);
    defaults = (float *)(state + 0x2F0);
    for (;i<10;i++) {
        *(unsigned char *)(reset+i)=0;
        func_L11_0043A9D8(D_L11_001B359C+(*(int *)(DATA(object)+0x330+i*4)<<8));
        func_002A0488(D_L11_001B359C+(*(int *)(DATA(object)+0x330+i*4)<<8),red,green,blue);
    }
    {
        float *out=defaults;
        float *in=D_L11_001B1240;
        for(i=11;i>=0;i--)
            *out++=*in++;
    }
    table = D_L11_001B359C;
    FLAGS(MODEL(object)) &= 0xFFFD;
    FLAGS(MODEL(object)) &= 0xFFFB;
    FLAGS(MODEL(object)) &= 0xFFBF;
    FLAGS(MODEL(object)) |= 0x1000;
    FLAGS(MODEL(object)) &= 0xFFFE;
    *(unsigned char *)(MODEL(object)+0x31)=1;
    {
        char *model=D_L11_001B359C + (*(int *)(DATA(object)+0x358) << 8);
        *(int *)(model+0x98)=*(int *)(*(char **)(model+0x24)+0x10);
    }
    if (*(short *)(state+0x70)) {
        *(short *)(state+0x70)=0;
        func_002A0488(object,*(unsigned char *)(state+0x74),*(unsigned char *)(state+0x75),*(unsigned char *)(state+0x76));
        *(short *)(state+0x72)=1;
    }
}
