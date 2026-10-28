/* Near miss, worker w3 batch 3: 572/572 B, 0/3, 12 lines. Unit L18_002CFD68-qcopy.c; D_L18_001AFBB0 is a sda array (macro tied load); ring updates reload the index fields; ring pointer as local. Left: snapshot/base register swap in the first block (retail $a1/$a0), sra order in the pressed-bits sum, addu operand order. */
#include "common.h"
extern s32 D_L18_001AFBB0[] __attribute__((sda));
extern u8 D_00189E20[];
/* Partial input record: only the observed axes and button words are modeled. */
typedef struct {
    u8 reserved000[0x108];
    float horizontal, vertical;
    u8 reserved110[0x90];
    s32 held;
    u8 reserved1A4[12];
    s32 pressed;
} InputRecordPrefix;
extern InputRecordPrefix D_00138180;
extern void func_L00_002B2BD0(void);
extern s32 func_00282978(void *);
extern s32 func_L00_002D3400(void);
extern float func_L00_002B3900(void);
extern float func_00282E20(void *);
extern void func_L18_002D7650(void);
extern void func_00283410(void *, void *);
extern void func_00283388(void *);
extern void func_00283698(void *, void *);
extern void func_L18_002D0850(void);
extern void func_L00_002C2DE8(void);
extern void func_L18_002DEFF8(void);
typedef struct { u8 b[16]; } Rac2Q;
void func_L18_002D0C00(void)
{
    u8 *base;
    s32 index;
    u8 *ring;
    u8 *snapshot;
    if (D_L18_001AFBB0[0]) {
        func_L00_002B2BD0();
        return;
    }
    snapshot = D_00189E20 + 0x2030;
    qcopy(snapshot, D_00189E20 + 0x80);
    if (D_00138180.held & 3) {
        if (*(s16 *)(D_00189E20 + 0x1454) < 1) *(s16 *)(D_00189E20 + 0x1454) = 1;
    } else func_00282978(snapshot - 0xBDC);
    base = D_00189E20;
    if (*(s32 *)(base + 0x2294) == 16) *(s16 *)(base + 0x1454) = 0;
    base[0x22C3] = func_L00_002D3400();
    *(float *)(base + 0x1FB0) = D_00138180.horizontal;
    *(float *)(base + 0x1FB4) = D_00138180.vertical;
    *(s32 *)(base + 0x270) = 0;
    *(float *)(base + 0x24BC) = func_L00_002B3900();
    if (func_00282E20(base + 0x1FB0) < 0.25f) {
        *(float *)(base + 0x1FB0) = (float)((s32)((D_00138180.pressed >> 13) & 1) - (s32)((D_00138180.pressed >> 15) & 1));
        *(float *)(base + 0x1FB4) = (float)((s32)((D_00138180.pressed >> 14) & 1) - (s32)((D_00138180.pressed >> 12) & 1));
    }
    *(float *)(base + 0x24B8) = func_L00_002B3900();
    func_L18_002D7650();
    ((float *)(base + 0x233C))[*(s32 *)(base + 0x23BC)] = *(float *)(base + 0x98);
    *(s32 *)(base + 0x23BC) = (*(s32 *)(base + 0x23BC) + 1) % 32;
    if (++*(s32 *)(base + 0x23C0) > 32) *(s32 *)(base + 0x23C0) = 32;
    index = *(s32 *)(base + 0x23C4);
    ring = base + 0x1D90;
    qcopy(ring + index * 16, base + 0x80);
    *(s32 *)(base + 0x23C4) = (index + 1) % 32;
    if (++*(s32 *)(base + 0x23C8) > 32) *(s32 *)(base + 0x23C8) = 32;
    func_00283410(base, base + 0x90);
    func_00283388(base + 0x40);
    func_00283698(base + 0x40, base);
    func_L18_002D0850();
    func_L00_002C2DE8();
    func_L18_002DEFF8();
}
