#include "common.h"

extern u8 *D_L01_001B255C;

extern u32 D_L01_001FB020[];

extern u8 *func_00305EE8(int);
extern s32 func_355780(u32 a0, u32 a1, void *a2);
extern void func_00308938(void *);
extern void func_00314D00(void *);
extern float D_L01_001B0540 __attribute__((sda));

/* The spawned moby's vars (+0x68). Struct stores let the fixed scalar scale
   load be scheduled ahead of the model-pointer load, as in retail. */
typedef struct {
    u8 pad0[0x60];
    u8 pos[0x10];
    u8 *owner;
    int link;
    int timer;
    u16 index;
    s16 target;
} SpawnVars;

u8 *func_L01_003D25B8(u8 *owner, void *pos, void *vel, int cls, int index)
{
    u8 *p = func_00305EE8(cls);
    if (p) {
        u8 *parent = *(u8 **)(owner + 0x68);
        SpawnVars *state = *(SpawnVars **)(p + 0x68);
        p[0x30] = 0xFF;
        *(s8 *)(p + 0x31) = 1;
        *(u16 *)(p + 0x32) = 0xFF;
        p[0x20] = 0;
        p[0xBC] = 0;
        state->owner = owner;
        state->index = index;
        *(float *)(p + 0x2C) = *(float *)(*(u8 **)(p + 0x24) + 0x24) * D_L01_001B0540;
        qcopy(p + 0x10, pos);
        qcopy(p + 0xF0, vel);
        qcopy(state->pos, pos);
        {
            int value;
            parent += index * 4;
            value = *(int *)(parent + 0x10);
            state->target = -1;
            state->link = value;
        }
        state->timer = 0;
        func_355780(2, 0, p);
        func_00308938(p);
        func_00314D00(p);
    }
    return p;
}

/* Walks the 0x7FFF-masked id list at table[index] and flags class 0xB2B entries. */
void func_L01_003D87B8(s32 index)
{
    u16 *p;
    u32 slot;
    u8 *base;
    u8 *e;

    if (index == -1)
        return;
    slot = D_L01_001FB020[index];
    if (slot == 0)
        return;
    p = (u16 *)slot;
    base = D_L01_001B255C;
    do {
        e = base + ((*p & 0x7FFF) << 8);
        if (*(s8 *)(e + 0x20) >= 0 && *(s16 *)(e + 0xAA) == 0xB2B)
            *(u16 *)(*(u8 **)(e + 0x68) + 0x3DA) = 1;
    } while (*(s16 *)p++ >= 0);
}

extern int D_001A79F0;
extern u8 D_0019B4A8[];
extern u8 D_0019B2E8[];
/* Level save state: collected[] is indexed by a moby's save id (s16 at +0xB2). */
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState D_L01_0021D840;
extern LevelSaveState D_L01_0021E4B0;
typedef struct { u8 flags[256]; } MissionFlags;
extern MissionFlags D_L01_001B23A0 __attribute__((sda));

/* Records a moby (mission byte +0xB0, save id +0xB2) in the current and checkpoint
   collected[] tables; same shape as RAC1's helga_update tail. */
void func_L01_003D8AD0(u8 *p)
{
    u8 *b;
    u8 group;

    if (p[0xB0] != 0xFF && *(short *)(p + 0xB2) >= 0 && !(p[0xB1] & 0x80)) {
        if (*(u16 *)(p + 0xB2) & 1) {
            b = D_0019B4A8 + ((*(short *)(p + 0xB2) >> 1) + (D_001A79F0 << 10));
            if (((*b >> 4) & 7) != 7) *b += 0x10;
        } else {
            b = D_0019B4A8 + ((*(short *)(p + 0xB2) >> 1) + (D_001A79F0 << 10));
            if ((*b & 7) != 7) ++*b;
        }
        D_L01_0021D840.collected[*(short *)(p + 0xB2)] = p[0xB0] + 2;
        if (p[0xB0] == 0xFF) goto record;
        group = p[0xB0];
        if (!(D_L01_001B23A0.flags[group] & 0x80) && (D_0019B2E8[group + (D_001A79F0 << 4)] & 0x80)) {
        record:
            D_L01_0021E4B0.collected[*(short *)(p + 0xB2)] = p[0xB0] + 2;
        }
    }
}
