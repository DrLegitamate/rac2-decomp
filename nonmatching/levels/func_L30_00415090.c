/* 28 October 2026: 840/840 bytes at -O2 -G0 -ffunction-sections.
 * The measured menu registration, controls, state machine and emission
 * agree except the final stack argument setup from +0x2C8 onward.
 * The evidenced int return of func_002B0CE0 closes the earlier pad-load
 * register difference. Scalar/array pad views, packed-color temporaries,
 * regrouping and truthful FP-last interleaving do not close the setup.
 * Nine compiles; reopen with argument-evaluation/scheduler evidence.
 * No strict match is claimed. */
#include "common.h"

extern char D_00189EA0[];
extern long D_00138320 __attribute__((nosda));
extern int func_002ACBC8(void *, int);
extern int func_002B0CE0(int, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern char *func_L30_00413490(void *);
extern void func_L30_00413528(void *, void *, void *, int, int, int);
extern char *func_L30_004153D8(void *, float, int, int, int, int, int, int, int, int, int, int);
extern char D_L30_001B1E28[];
extern char D_L30_001B1E30[];
extern char D_L30_001B1E48[];
extern char D_L30_001B1E60[];
extern char D_L30_001B1E78[];
extern char D_L30_001B1E90[];
extern char D_L30_001B1EA0[];
extern char D_L30_001B1EA8[];
extern char D_L30_001B1EB0[];
extern char D_L30_001B1EB8[];
extern char D_L30_001B1ED0[];
extern char D_L30_001B1EE0[];

#define MI(o) (*(int *)(state + (o)))
#define MF(o) (*(float *)(state + (o)))
#define MENU (*(char **)(state + 0x2C))

void func_L30_00415090(char *object)
{
    char *state = *(char **)(object + 0x68);
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(float *)(object + 0x1C) = 0.0f;
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (MI(0x3C) != -1 && func_002ACBC8(D_00189EA0, MI(0x3C))) {
            func_002B0CE0(1, 0x27E6, 1);
            { long buttons = D_00138320;
              if ((buttons & 3) == 3) func_002A7750(object, 2, -1); }
        }
        break;
    case 2:
        if (func_002B3868(object)) {
            MENU = func_L30_00413490(object);
            func_L30_00413528(MENU, state + 0x4, D_L30_001B1E28, 1, 0, 1);
            func_L30_00413528(MENU, state + 0xC, D_L30_001B1E30, 0, 0, 50);
            func_L30_00413528(MENU, state + 0x10, D_L30_001B1E48, 0, 0, 50);
            func_L30_00413528(MENU, state + 0x14, D_L30_001B1E60, 0, 0, 50);
            func_L30_00413528(MENU, state + 0x18, D_L30_001B1E78, 0, 0, 50);
            func_L30_00413528(MENU, state + 0x1C, D_L30_001B1E90, 0, 0, 50);
            func_L30_00413528(MENU, state + 0x20, D_L30_001B1EA0, 0, 0, 255);
            func_L30_00413528(MENU, state + 0x24, D_L30_001B1EA8, 0, 0, 255);
            func_L30_00413528(MENU, state + 0x28, D_L30_001B1EB0, 0, 0, 255);
            func_L30_00413528(MENU, state + 0x30, D_L30_001B1EB8, 0, 0, 1);
            func_L30_00413528(MENU, state + 0x34, D_L30_001B1ED0, 0, 0, 1);
            func_L30_00413528(MENU, state + 0x8, D_L30_001B1EE0, 0, 0, 1);
        }
        func_002B0CE0(1, 0, 1);
        if (!MENU || *(short *)(MENU + 0xAA) != 0x118A ||
            *(unsigned char *)(MENU + 0x20) == 0xFE || *(unsigned char *)(MENU + 0x20) == 0xFD)
            func_002A7750(object, 1, -1);
        break;
    }
    if (*(float *)(object + 0x1C) >= 45.0f) {
        *(float *)(object + 0x1C) = 0.0f;
        *(void **)state = func_L30_004153D8(object + 0x10, MF(4), MI(8), MI(0xC), MI(0x10),
            MI(0x14), MI(0x18), MI(0x1C), MI(0x30), MI(0x34), MI(0x38),
            MI(0x20) | ((MI(0x28) << 16) | (MI(0x24) << 8)));
    }
    *(float *)(object + 0x1C) += 1.0f;
}
