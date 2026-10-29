#include "include_asm.h"

typedef unsigned char u8;

extern void func_0032B890(int, int, int);

extern void func_0031E6A0(void *, int, int);
extern int func_0031E770(int);
extern void func_0031E3C0(void *, int, int, int);
extern int func_002F1BE0(void *);
extern float func_0031E808(float, float);
extern int func_002F3158(float);

extern void func_002F1F70(void *, void *, void *);
extern void func_002F20A0(void *, void *, void *);
extern void func_002F2270(void *, void *, float);
extern float func_0031E8D0(void);

/* func_L02_00410450 is defined in L02_00410450-controller-g8.c. */

/* func_L02_00410D00 is defined in L02_00410D00-g8.c. */

/* func_L02_00410E58 is defined in L02_00410E58.c. */

INCLUDE_ASM("asm/levels", func_L02_00410F68);

/* Plays one of nine resident messages, chosen by the sub-object's state word. */
/* func_L02_004114A0 is defined in L02_004114A0.c. */

/* func_L02_00411530 is matched in L02_00411530.c (built with -frac2-hazard-labels). */

/* True while the record's state byte still says 2. */
int func_L02_004127F8(u8 *a0) {
    return *(u8 *)(a0 + 0x20) == 2;
}

/* Copies the sub-object's byte 0x40 down to its byte 0x25. */
void func_L02_00414D48(u8 *a0) {
    u8 *v1 = *(u8 **)(a0 + 0x68);
    *(u8 *)(v1 + 0x25) = *(u8 *)(v1 + 0x40);
}

INCLUDE_ASM("asm/levels", func_L02_004164A8);

/* func_L02_00416720 is defined in L02_00410450-qcopy.c. */

/* True when the record is in state 1 and its sub-object holds a cleared origin. */
int func_L02_00416800(void *arg0) {
    int var_a2;
    void *temp_a1;

    var_a2 = 0;
    temp_a1 = *(void **)((unsigned char *)arg0 + 0x68);
    if (((*(unsigned char *)((unsigned char *)arg0 + 0x20)) == 1) && ((*(int *)temp_a1) == 0) && ((*(float *)((unsigned char *)temp_a1 + 4)) == 0.0f)) {
        var_a2 = 1;
    }
    return var_a2;
}

/* func_L02_00421860 is defined in L02_00421860-g8.c. */

INCLUDE_ASM("asm/levels", func_L02_00421DA0);

INCLUDE_ASM("asm/levels", func_L02_00422270);

/* Rebuilds the sub-object's frame from the record's own transform. */
void func_L02_004224C8(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    u8 *s0 = a0 + 0x10;

    func_002F1F70(s1, s0, s1 + 0x40);
    func_002F20A0(s1, s1, s0);
    func_002F2270(s1, s1, 0.25f);
    *(float *)(s1 + 0x30) = func_0031E8D0();
}

/* func_L02_00422538 is defined in L02_00410450-g8.c (this unit has no $gp access for it). */

extern void func_L02_00422720(u8 *);
extern void func_L02_00422BB8(u8 *);
extern void func_L02_00422D68(u8 *);

/* One setup pass, then the five body passes of the resident effect. */
void func_L02_00422638(u8 *a0) {
    int i;

    func_L02_00422720(a0);
    i = 4;
    func_L02_00422BB8(a0);
    do {
        func_L02_00422D68(a0);
    } while (--i >= 0);
}

/* func_L02_00422720 is defined in L02_00422720-g8.c. */

/* func_L02_00422BB8 is defined in L02_00422BB8-g8.c. */

/* func_L02_00422D68 is defined in L02_00422D68-g8.c. */


/* Restarts the record's resident effect once it has settled, picking the
   variant by the resident query and the record's own byte 0x43. */
void func_L02_0042ED48(u8 *a0) {
    u8 *s0 = a0;

    if (*(u8 *)(s0 + 0x20) != 0)
        return;
    func_0031E6A0(s0, 1, -1);
    if (func_0031E770(2) != 0) {
        if (*(u8 *)(s0 + 0x43) != 0)
            func_0031E3C0(s0, 0, 0, 0xA);
    } else {
        if (*(u8 *)(s0 + 0x43) != 1)
            func_0031E3C0(s0, 1, 0, 0xA);
    }
}

/* func_L02_0042EDD0 is matched in L02_0042EDD0-g8.c (built with -frac2-no-annulled-wide-stores -frac2-zero-ti-barrier). */


/* Picks the evasive state the object should take while the resident timer runs. */
void func_L02_0043FA98(u8 *a0) {
    u8 *s0 = a0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    int m;

    if (func_002F1BE0(s1 + 0x48) == 0)
        return;
    if (*(int *)(s1 + 0x44) != 0 || func_0031E808(0.0f, 1.0f) < 0.8f) {
        if (*(u8 *)(s0 + 0x42) != 1)
            m = 1;
        else
            m = 2;
        if (*(u8 *)(s0 + 0x43) != m)
            func_0031E3C0(s0, m, 0, 0x1E);
    } else {
        if (*(u8 *)(s0 + 0x43) != 0)
            func_0031E3C0(s0, 0, 0, 0x1E);
    }
    *(short *)(s1 + 0x48) = func_002F3158(func_0031E808(135.0f, 225.0f));
}
