/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections, in place in src/levels/shared/L00_003EA0E0.c
 * (that unit already declares D_00189E20 with another type, hence the _1 alias name,
 * and func_L00_003EAC88 with its Rac2Native_..._AnalysisOwner parameter).
 * Retail: 556 bytes; compiled: 556 bytes.
 * Coverage: us: 0/27 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Control flow, calls, constants and the movz for the ready flag match. The saved
 * registers are permuted (about 45 lines in level 00): retail has self $s0, the state
 * $s1, the game block $s2, the spot buffer $s3 and the block's high part $s6; cc1 has
 * self $s1, the state $s2, the block $s3, the spot buffer $s0 plus a copy in $s6.
 * Tried: the block directly everywhere (568 bytes); a block local for the set-up only
 * (560); for everything (this version, 556); the spot buffer through a pointer (548).
 */

extern char D_00189E20_1[];
extern unsigned int D_00138324;

extern void func_0029FCC0(void *, int, void *);
extern void func_002FDF40(void *, void *, void *, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(void *);
extern int func_L00_002D3F30(int, int);
extern void func_L00_002AF568(void);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_00387CA8(void *, void *);
extern void func_L00_002AF7D0(void);
extern void func_L00_002E6EF8(void *, void *);
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
extern void func_L00_003EAC88(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* A ship pad: finds its landing spot (farther out in game mode 29), waits until the player
   can use it (state 1), launches the ship sequence (2) and waits for it to end (3). */
void func_L00_003EAA58(unsigned char *self)
{
    float at[4] __attribute__((aligned(16)));
    float spot[4] __attribute__((aligned(16)));
    unsigned char *st = *(unsigned char **)(self + 0x68);
    float reach;
    int ready = 1;
    char *game;

    func_0029FCC0(self, 0, at);
    game = D_00189E20_1;
    reach = 4.5f;
    if (*(int *)(game + 0x2294) == 29)
        reach = 11.0f;
    func_002FDF40(spot, at, 0, 0, 1.5f, reach, 0.25f, 0.0030555557f);
    *(int *)(st + 0x24) = func_002FE5A0(at, spot, st, st + 0x10, self, 0, 0, 0.0030555557f);
    if (*(int *)(game + 0x2294) == 29) {
        if (func_00282948(game + 0x2534) == 0)
            ready = 0;
    } else {
        *(int *)(game + 0x2534) = 40;
    }
    switch (self[0x20]) {
    case 0:
        self[0x20] = 1;
        *(int *)(st + 0x24) = 0;
    case 1:
        if ((*(unsigned int *)(game + 0x1230) & D_00138324) == 0)
            break;
        if (*(unsigned char *)(game + 0x22BC) != 0)
            break;
        if (ready == 0)
            break;
        if (func_L00_002D3F30(-1, 1) != 0) {
            func_L00_002AF568();
            self[0x20] = 2;
            *(int *)(st + 0x20) = 20;
        } else {
            func_002E5CF8(2, 0, (char *)self);
        }
        break;
    case 2:
        if (func_00282948(st + 0x20) != 0) {
            func_002E5CF8(0, 0, (char *)self);
            *(unsigned char **)(func_L00_00387CA8(at, spot) + 0xB8) = self;
            func_L00_002AF7D0();
            self[0x20] = 3;
            *(int *)(st + 0x20) = 10;
        }
        break;
    case 3:
        if (func_00282948(st + 0x20) != 0)
            self[0x20] = 1;
        break;
    }
    func_L00_002E6EF8((void *)func_L00_003EAC88, self);
}
