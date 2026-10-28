/* PR #357 review: plain, single-declaration reconstruction; no volatile or
 * assembler-name aliases. Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * USA size 736/736 bytes, first mismatch +0x204; all three releases
 * remain nonmatching. A measured 128-byte pose-record view and independent
 * locals preserve the data accesses, but the table/index loads and angle
 * argument setup are scheduled differently. Scalar locals and row-pointer
 * forms tie. Reopen with a real layout/lifetime witness, not forced reloads.
 */
#include "common.h"

typedef struct { unsigned char pad00[0x30]; float position[4]; unsigned char pad40[0x30]; float rotation[4]; } PoseRecord;
typedef struct { unsigned char pad00[0x80]; int index; } PoseMotion;
extern unsigned char *D_L01_001B255C SDATA(D_L01_001B255C);
extern PoseRecord *D_L01_001B264C NOT_SDA;
extern unsigned char D_001A7B0B[];
extern unsigned char D_001A7B2A[];
extern float func_00283180(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002AA150(float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002AD6F0(void *, void *, void *, void *);
void func_L01_00405300(unsigned char *m)
{
    float position[4], rotation[4], delta[4];
    unsigned char *p = *(unsigned char **)(m + 0x68);
    float blend;
    qcopy(position, m + 0x10);
    qcopy(rotation, m + 0xf0);
    switch (m[0x20]) {
    case 0:
        *(int *)(p + 0x88) = 0;
        *(int *)(p + 0x5c) |= 1;
        qcopy(p + 0x60, m + 0x10);
        qcopy(p + 0x70, m + 0xf0);
        func_002A7750(m, 1, -1);
        break;
    case 1:
        if (m[0xbc]) goto start_motion;
        if (*(int *)(p + 0x8c) == -1) goto start_motion;
        {
            int child_state = D_L01_001B255C[*(int *)(p + 0x8c) * 256 + 0x20];
            if (child_state == 0xfe) goto start_motion;
            if (child_state == 0xfd) goto start_motion;
        }
        if (!D_001A7B0B[0]) goto start_motion;
        if (D_001A7B2A[0]) {
start_motion:
            func_002A7750(m, 2, -1);
        }
        m[0xa8] = 255;
        break;
    case 2:
        *(float *)(p + 0x88) += 1.0f / *(float *)(p + 0x84);
        if (*(float *)(p + 0x88) > 1.0f) *(float *)(p + 0x88) = 1.0f;
        blend = (1.0f - func_00283180(*(float *)(p + 0x88) * 3.1415927f)) * 0.5f;
        {
            int index = ((PoseMotion *)p)->index;
            PoseRecord *target = D_L01_001B264C;
            func_00282CF0(delta, target[index].position, p + 0x60);
        }
        func_00282D30(delta, delta, blend);
        func_00282CC0(m + 0x10, p + 0x60, delta);
        {
            int index = ((PoseMotion *)p)->index;
            PoseRecord *target = D_L01_001B264C;
            *(float *)(m + 0xf8) = func_002AA150(*(float *)(p + 0x78), target[index].rotation[2], blend);
        }
        {
            PoseRecord *target = D_L01_001B264C;
        *(float *)(m + 0xf4) = func_002AA150(*(float *)(p + 0x74), target[((PoseMotion *)p)->index].rotation[1], blend);
        }
        {
            PoseRecord *target = D_L01_001B264C;
        *(float *)(m + 0xf0) = func_002AA150(*(float *)(p + 0x70), target[((PoseMotion *)p)->index].rotation[0], blend);
        }
        if (*(float *)(p + 0x88) >= 1.0f) func_002A7750(m, 3, -1);
        break;
    case 3:
        *(unsigned short *)(m + 0x34) |= 2;
        break;
    }
    if (m[0x20] < 3) {
        func_00282CF0(delta, m + 0x10, position);
        func_002AD6F0(p + 0x20, delta, rotation, m + 0xf0);
    }
}
