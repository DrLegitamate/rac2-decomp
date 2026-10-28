/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -fno-gcse.
 * 536/536 bytes; first mismatch remains +0x144. The new -fno-gcse witness from func_L04_00456860 was tested against the retained source and tied the previous result. The existing tail-induction reopening condition remains applicable.
 * US object comparison only in this retry; no linked strict-build claim.
 * Reopen with a measured allocation, scheduling or source-interface witness.
 */
/* Retained readable reconstruction; NOT MATCHING and no exact-C credit.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier
 * Fresh local measure: 536/536 bytes; 0/2 USA v1.01 placements; first mismatch +0x144.
 * Evidence: Approved aligned state copies and the true callback-function pointer declaration are retained. The tail keeps TI transfers: qcopy adds a loop-padding nop. Callback no-split-addresses gave 544 bytes. Tail pointer allocation/induction and final store scheduling still differ.
 * Reopen: Obtain a measured loop/allocator witness for the existing tail transfers; preserve the dynamic source count and 640-byte destination stride.
 * Older notes below are historical. Equal size and allocator diagnostics do
 * not establish relocation/binding qualification or linked equality.
 */
#include "common.h"

/* 2026-10-23 readable reconstruction. Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * 536/536 bytes, 0/2 placements in us and us2; not carried by pal. First mismatch +0x144: tail-copy register allocation and pointer induction; final state-store order also differs. Six trials covered sda, comparison order, branch wording, indexed versus explicit pointer loops, and -g. Reopen with an equivalent pointer-loop witness.
 * Earlier screening-only commentary is preserved below as historical context.
 */
/* from src/levels/shared/L11_002C5E80.c: not written this wave. Retail 536 bytes, 2 place(s), first word at L11:0046b9f0.
 * Rule: MMI/LQ/SQ (op 0x1e).
 * No C attempt was made (wave-5 tour-2 discard rule).
 * Retail opens with:
 *   0x0046b9f0  addiu       $sp, $sp, -0x30
 *   0x0046b9f4  sd          $s2, 0x20($sp)
 *   0x0046b9f8  sd          $s0, 0x10($sp)
 *   0x0046b9fc  daddu       $s2, $a0, $zero
 *   0x0046ba00  sd          $ra, 0x28($sp)
 *   0x0046ba04  sd          $s1, 0x18($sp)
 * Kept as data for the maintainers. */

typedef int Vec128_L11 __attribute__((mode(TI)));
extern int D_001A79F0;
extern char D_00189EA0[];
extern int D_L11_001B25A0 __attribute__((sda));
extern char *D_L11_001FF580[];
extern char D_L11_00264760[];
extern int func_002A77E0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_L11_0046BC08(void *);
extern void func_L11_0046BD18(char *);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern int func_00291308(void *, int, float, float);
extern void ref_L11_0046B9F0_00(void *);

void func_L11_0046B9F0(char *object)
{
    float position[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *source;
    Vec128_L11 *destination;
    Vec128_L11 *tail;
    int count;
    int i;
    if (*(int *)(state + 0x38) >= 20) *(int *)(state + 0x3c) = 1;
    if (*(int *)(state + 0x3c) || D_001A79F0 == 4 || D_001A79F0 == 11) {
        if (*(int *)(state + 0x38) >= 20 && 85.0f < *(float *)(D_00189EA0 + 8)) return;
        qcopy(state, object + 0x10);
        qcopy(state + 0x10, state);
        *(float *)(state + 0x20) += (6.0f - *(float *)(state + 0x20)) * 0.07f + 12.0f;
        position[0] = 0.0f;
        position[1] = *(float *)(state + 0x20);
        position[2] = 0.0f;
        func_00282CC0(state + 0x10, state, position);
        qcopy(position, state + 0x10);
        if (D_001A79F0 != 4 && D_001A79F0 != 11) D_L11_001B25A0 = func_002A77E0(20);
        else D_L11_001B25A0 = 20;
        func_L11_0046BC08(object);
        func_L11_0046BD18(object);
        source = D_L11_001FF580[*(int *)(state + 0x34)];
        count = D_L11_001B25A0;
        i = count - 4;
        if (i < count) {
            destination = (Vec128_L11 *)(D_L11_00264760 + *(int *)(state + 0x38) * 640) + i;
            tail = (Vec128_L11 *)source + i + 1;
            do {
                *destination++ = *tail++;
                i++;
            } while (i < count);
        }
        func_L00_002E6EF8(ref_L11_0046B9F0_00, object);
        if (!*(unsigned char *)(object + 0x20)) {
            *(int *)(state + 0x24) = func_00291308(state, 0, 0.0f, 0.0f);
            object[0x20] = 1;
            *(int *)(state + 0x2c) = D_L11_001B25A0;
            *(int *)(state + 0x30) = -1;
        }
    }
}
