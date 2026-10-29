#include "include_asm.h"

typedef int s32;

typedef unsigned char u8;

/* func_003512B8 : rounds a field to a multiple of 2048 under a semaphore */
extern s32 func_0011AC60(s32);

extern s32 func_0011AC40(s32);

/* func_00351268 : waits, then combines two fields shifted by 11 */
extern s32 func_0011AC60(s32 a0);

extern s32 func_0011AC40(s32 a0);

typedef struct ViBuf {
    int base;               /* 0x0 */
    unsigned char *tags;    /* 0x4 */
    int count;              /* 0x8 */
    int fC;                 /* 0xC */
    int f10;                /* 0x10 */
    int f14;                /* 0x14 */
    int f18;
    char pad1C[0x24];
    int sema;               /* 0x40 */
    int f44;                /* 0x44 */
} ViBuf;

extern void func_0034F780(char *);
extern char D_001AE848[];
extern void func_00350808(unsigned int);
extern int func_00350750(ViBuf *, unsigned int);
extern void func_00350878(unsigned long *, unsigned long, unsigned long, unsigned long);

void func_00350B70(u8 *a0, s32 a1) {
    func_0011AC60(*(s32 *)(a0+0x40));
    *(s32 *)(a0+0x14) += (s32)a1;
    *(long *)(a0+0x48) = (long)a1 + *(long *)(a0+0x48);
    func_0011AC40(*(s32 *)(a0+0x40));
}

INCLUDE_ASM("asm/game", func_00350BC8);
