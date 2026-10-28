/*
 func_L05_0041C860 (524 bytes, 1 place) - own unit L05_0041C860-qcopy.c, cflags -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 3 masked lines differ (w5, 2026-10-28): the word stored at r+0x11C is `st` ($a0 holds 1), not a constant; the table pointer is an incomplete sda array element
 (D_L05_001B251C[0]), which restores both branch-likely guards and the size. Open: retail loads the table pointer (`lui;lw`) before the
 reload of state+0x260, ours after it (same wall in func_L05_004155A0 and func_L05_00415B38).
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern char D_L05_002681E0[];
extern char *D_L05_001B251C[] __attribute__((sda));

extern int func_379860(char *object);
extern char *func_379CA0(char *object);
extern void func_379E60(char *object, char *a1, int a2, int a3);
extern void func_37C160(char *object);
extern void func_37B538(char *object, int a1, int a2, int a3);
extern void func_37B948(char *object, int a1, float a2);
extern int func_37B888(char *object);
extern void func_37B6D0(char *object);
extern void func_3065F8(char *block);
extern void func_3062A0(char *block);
extern void func_2FF698(void *fn, char *object);
extern void func_332708(char *object, int a1, int a2, int a3);
extern float func_332B50(float a, float b);
extern int func_307840(char *buf, float value);
extern void func_L05_0041CA70(char *obj);
extern void func_L05_0041CB68(char *object);
extern void func_L05_0041CE00(char *object);
extern void func_L00_003E4948(void);

void func_L05_0041C860(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *r;
    TI128 qbuf;
    int st;

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        func_L05_0041CA70(object);
        func_332708(object, 1, 0, 0);
        func_3065F8((char *)&qbuf);
        *(float *)(object + 0x48) = func_332B50(0.9f, 1.1f);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            func_379E60(object, 0, 0, 0);
            base = D_L05_002681E0;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = func_379CA0(object);
    if (*(int *)(r + 0x110) == 0)
        return;
    {
    int one = 1;
    func_37C160(object);
    func_37B538(object, 0, 0, 0);
    func_37B948(object, one, 64.0f);
    st = *(int *)(r + 0x110);
    if (st == one) {
        if (*(int *)(state + 0x260) != -1) {
            *(int *)(r + 0x11C) = st;
            *(int *)(r + 0x120) = (int)(D_L05_001B251C[0] + *(int *)(state + 0x260) * 256);
        }
        if (*(int *)(r + 0x108) != 0 && *(int *)(r + 0x104) != 0)
            func_L05_0041CB68(object);
        if (func_37B888(object) != 0)
            func_37B6D0(object);
        func_3062A0(state + 0x268);
        qbuf = *(TI128 *)(object + 0x10);
        *(float *)((char *)&qbuf + 0xC) = *(float *)(object + 0xC) * 0.00097656f;
        if (func_307840((char *)&qbuf, 100.0f) != -1)
            func_L05_0041CE00(object);
    }
    }
    func_2FF698(func_L00_003E4948, object);
}
