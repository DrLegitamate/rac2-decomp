#include "include_asm.h"
#include "common.h"


typedef int TI128 __attribute__((mode(TI)));

extern int func_337518(int a0, char *a1, int a2);

extern void func_42DF10(void *a0);

extern void *D_L10_001ADE90 __attribute__((sda));

extern int func_32AC10(int a0);


extern float func_309B38(float f12, float f13);

extern float func_309B80(float f12, float f13);


int func_L10_0042E590(int a0) {
    return func_337518(a0, (char *)0x230000, 0) != 0;
}

void func_L10_00425410(int a0, void *a1) {
    int i;

    if (a0 > 0) {
        i = a0;
        do {
            func_42DF10(a1);
            i--;
        } while (i != 0);
    }
}

void *func_L10_00449AD0(void) {
    return D_L10_001ADE90;
}

extern char *D_L10_001B2528;
extern void func_32AF78(void *a0);


/* func_L10_00425798 is defined in L10_00425798-flags.c. */

/* func_L10_00424028 is defined in L10_00424028-g8.c. */


INCLUDE_ASM("asm/levels", func_L10_00424528);

INCLUDE_ASM("asm/levels", func_L10_00424CD0);

/* func_L10_00425508 is defined in L10_00424028-reward-g8.c. */


INCLUDE_ASM("asm/levels", func_L10_00424448);

INCLUDE_ASM("asm/levels", func_L10_0042B500);

INCLUDE_ASM("asm/levels", func_L10_0042BCA0);

/* func_L10_0042BE20 is defined in L10_00424028-g8.c (this unit has no $gp access for it). */

/* func_L10_0042BEE0 is in the sibling file L10_00424028-g8.c (it reads $gp data). */

/* func_L10_0042DF10 is defined in L10_0042DF10-g8.c. */

/* func_L10_0042E100 is defined in L10_0042E100-g16.c. */

/* Defined in L10_0042E4D0.c. */

/* func_L10_0042E660 is defined in L10_0042E660-g8.c. */
