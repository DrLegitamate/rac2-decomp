#include "include_asm.h"
extern int D_L30_001B2A68 __attribute__((sda));
extern short D_0018A000;
extern unsigned long long D_00138180[];
extern unsigned char D_L30_001B3D30[];
extern void *D_L30_00260E30[];
extern int D_L30_00260F30[][2];
extern void func_2EDB20(void *, void *);
extern void func_323FB0(void *, int, int);
extern void func_L30_004135A0(char *);

extern void func_42C028(int);
extern void func_316DB8(char *);
extern int D_0018C0E8;

void func_L30_00418670(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    func_42C028(3);
    D_0018C0E8 = *(int *)(st + 0x5C);
    func_316DB8(*(char **)(st + 0x50));
}


void func_L30_004130E8(char *obj) {
    int *st = *(int **)(obj + 0x68);
    int step = 0;
    D_L30_001B2A68 = 1;
    D_0018A000 = 5;
    func_2EDB20(func_L30_004135A0, obj);
    if (D_00138180[0x1A0 / 8] & 0x9000000000ULL) {
        func_316DB8(obj);
        return;
    }
    if (((int *)D_00138180)[0x1A4 / 4] & 0x4000) {
        func_323FB0(st, st[1] - 1, 1);
        if (st[2] < st[0] - 15) st[2]++;
    } else if (((int *)D_00138180)[0x1A4 / 4] & 0x1000) {
        func_323FB0(st, 0, 1);
        if (st[0] < st[2]) st[2]--;
    } else if (((int *)D_00138180)[0x1A0 / 4] & 0x2000) {
        step = (((int *)D_00138180)[0x1A0 / 4] & 15) ? 5 : 1;
    } else if (((int *)D_00138180)[0x1A0 / 4] & 0x8000) {
        step = (((int *)D_00138180)[0x1A0 / 4] & 15) ? -5 : -1;
    }
    if (step && *(unsigned short *)(obj + 0x96) >= 5) {
        *(unsigned short *)(obj + 0x96) = 0;
        switch (D_L30_001B3D30[st[0]]) {
        case 0: {
            int value = *(int *)D_L30_00260E30[st[0]];
            value += step;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(int *)D_L30_00260E30[st[0]] = value;
            break;
        }
        case 1: {
            float value = *(float *)D_L30_00260E30[st[0]] + step * 0.01f;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(float *)D_L30_00260E30[st[0]] = value;
            break;
        }
        case 2: {
            unsigned char value = *(unsigned char *)D_L30_00260E30[st[0]];
            value += step;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(unsigned char *)D_L30_00260E30[st[0]] = value;
            break;
        }
        case 3: {
            short value = *(short *)D_L30_00260E30[st[0]];
            value += step;
            if (value > D_L30_00260F30[st[0]][1]) value = D_L30_00260F30[st[0]][1];
            else if (value < D_L30_00260F30[st[0]][0]) value = D_L30_00260F30[st[0]][0];
            *(short *)D_L30_00260E30[st[0]] = value;
            break;
        }
        }
    }
    (*(unsigned short *)(obj + 0x96))++;
}


INCLUDE_ASM("asm/levels", func_L30_00413528);

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


INCLUDE_ASM("asm/levels", func_L30_00415090);

/* func_L30_004153D8 is defined in L30_004153D8.c. */

INCLUDE_ASM("asm/levels", func_L30_004158B0);

INCLUDE_ASM("asm/levels", func_L30_00416A88);

INCLUDE_ASM("asm/levels", func_L30_00416D88);

INCLUDE_ASM("asm/levels", func_L30_00417988);

typedef unsigned short u16;

extern char *func_316A50(int);
extern void func_32BFF0(void *, void *);
extern void func_2F56B0(void *, void *);

void func_L30_00418570(char *a0) {
    char *st = *(char **)(a0 + 0x68);
    char *o;

    o = func_316A50(0xB28);
    if (o == 0) return;
    func_32BFF0(o, a0);
    func_2F56B0(o + 0xC0, o + 0xF0);
    *(u16 *)(o + 0x34) |= 0x100;
    *(char **)(st + 0x50) = o;
}


INCLUDE_ASM("asm/levels", func_L30_004186B0);

INCLUDE_ASM("asm/levels", func_L30_004191E0);

extern int func_2F4B08(char *);
extern void func_2EDD78(void *, char *);
extern void func_L00_00415AA0(char *);

void func_L30_0041A848(char *a0) {
    char *st = *(char **)(a0 + 0x68);

    if (func_2F4B08(st) == 0) {
        func_2F4B08(st + 4);
        func_2EDD78((void *)func_L00_00415AA0, a0);
    } else {
        func_316DB8(a0);
    }
}

/* func_L30_0041B848 is defined in L30_0041B848.c. */
