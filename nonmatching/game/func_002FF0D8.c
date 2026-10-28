/* Retained reconstruction, USA v1.01.
 * 416/428 bytes, game -O2 -G0 -g, measured on the initial retained copy spelling. Reconstructs transition count/rate, vector snapshots, resident defaults and mode-dependent actor selection with the actual pointer return of func_002FF300. Scalar SDA metadata retains mixed address forms, but copied-vector addressing and later branch/store scheduling differ. A pointer variant with -mno-split-addresses reaches an assembler internal assertion; no tool changes were attempted.
 * No strict linked match.
 */
#include "common.h"

extern u16 D_001AD7F8 SDATA(D_001AD7F8);
extern s16 D_001B2312 __attribute__((sda));
extern float D_001B2314 __attribute__((sda));
extern float D_001B2320[4];
extern float D_001B2330[4];
extern s16 D_001B2310 __attribute__((sda));
extern s16 D_001B2318 __attribute__((sda));
extern u8 D_001B231C __attribute__((sda));
extern u8 D_001B231D __attribute__((sda));
extern u8 D_001B2345 __attribute__((sda));
extern unsigned char *D_001B2340 __attribute__((sda));
extern int D_001AD7E4 SDATA(D_001AD7E4);
extern int D_001AD7E8 SDATA(D_001AD7E8);
extern unsigned char D_00189E20[];
extern unsigned char D_001A63A8[];
extern unsigned char D_00139568[];
extern unsigned char D_00239BA0[];
extern float func_00283CE0(int);
extern char *func_002FF300(int, int);

void func_002FF0D8(void)
{
    unsigned char *record;
    D_001B2312 = D_001AD7F8;
    D_001B2314 = 1.0f / func_00283CE0(D_001B2312);
    qcopy(D_001B2320, D_00189E20 + 0x80);
    qcopy(D_001B2330, D_00189E20 + 0x90);
    D_001B2310 = 0;
    if (*(int *)(D_001A63A8 + 0x68) == 0 && *(int *)(D_001A63A8 + 0x24) == -1) {
        *(int *)(D_001A63A8 + 0x28) = 0;
        *(int *)(D_001A63A8 + 0x24) = 0xDB7;
    }
    D_001AD7E4 = 1;
    D_001AD7E8 = 0;
    D_001B231C = 0;
    D_001B231D = 0;
    if (D_001B2318 == 31) {
        record = D_00239BA0 + D_00139568[31] * 0xE0;
        D_001B2340 = (unsigned char *)func_002FF300(*(int *)(record + 0x14), 1);
        D_001B2345 = 0;
    } else if (D_001B2318 == 45) {
        record = D_00239BA0 + D_00139568[45] * 0xE0;
        D_001B2340 = (unsigned char *)func_002FF300(*(int *)(record + 0x14), -1);
        D_001B2345 = 0;
    } else if (D_001B2318 == 9) {
        D_001B2340 = (unsigned char *)func_002FF300(601, 0);
        D_001B2345 = 0;
    } else {
        D_001B2345 = 1;
        record = D_00239BA0 + D_00139568[D_001B2318] * 0xE0;
        D_001B2340 = *(unsigned char **)(D_00189E20 + *(int *)(record + 0xC) * 0x50 + 0x1220);
    }
}
