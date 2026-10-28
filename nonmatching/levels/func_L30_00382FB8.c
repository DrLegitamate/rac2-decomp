/* Retained exact-C reconstruction: 284/284 bytes.
 * Profile: -O2 -G8 -ffunction-sections -fno-rerun-loop-opt.
 * US, US2 and PAL each 0/1. Complete 24x24 eight-neighbor stencil and bank swap replace the comment-only screen. Byte-offset row views retain the measured neighbor order. Disabling the second loop pass recovers 284 bytes and the incrementing inner counter; all FP operations and the inner branch span agree. GPR allocation and outer-row setup remain different.
 * No strict linked match. Reopen with independent source, allocation or
 * compiler evidence for the remaining difference; do not repeat tied forms.
 */
#include "common.h"
extern int D_001AEBB8 __attribute__((sda));
extern int D_001AEBBC __attribute__((sda));
extern float D_L30_00233A60[];

void func_L30_00382FB8(void)
{
    int source=D_001AEBB8*0x900;
    int destination=D_001AEBBC*0x900;
    int row,column;
    for(row=1;row<23;row++) {
        int rowOffset=row*0x60;
        int previous=(row-1)*0x60+source;
        int next=(row+1)*0x60+source;
        int current=rowOffset+(source+4);
        int out=rowOffset+destination;
        for(column=1;column<23;column++) {
            int at=column*4;
            float sum=*(float *)(previous+at+(char *)D_L30_00233A60)
                     +*(float *)(next+at+(char *)D_L30_00233A60)
                     +*(float *)(current+at-8+(char *)D_L30_00233A60)
                     +*(float *)(current+at+(char *)D_L30_00233A60)
                     +*(float *)(previous+at-4+(char *)D_L30_00233A60)
                     +*(float *)(previous+at+4+(char *)D_L30_00233A60)
                     +*(float *)(next+at-4+(char *)D_L30_00233A60)
                     +*(float *)(next+at+4+(char *)D_L30_00233A60);
            float *cell=(float *)(out+at+(char *)D_L30_00233A60);
            float value=sum*0.25f-*cell;
            *cell=value-value*0.0625f;
        }
    }
    {
        int old=D_001AEBB8;
        int other=D_001AEBBC;
        D_001AEBBC=old;
        D_001AEBB8=other;
    }
}
