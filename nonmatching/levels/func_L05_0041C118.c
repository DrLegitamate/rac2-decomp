/* func_L05_0041C118 (w2 batch 3, 2026-10-28). Unit -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
   204/212 bytes. The list head as `extern char *D_L05_001B2528[] MACRO_ADDR;` read as [0] gives retail's tied
   `lui $v1 ; lw $v1,lo($v1)`. Left: retail compares the tag with `xor $v0,$v0,$a1` (a1 = 0xFBF hoisted into
   the beqz slot) where this folds it to `xori` (a local, short, static const, ternary, goto, for/while/do
   all fold); the header stores (retail sh 0x32, sb 0x30, sb 0x31 with v1/v0/a1 constants). */
#include "common.h"

/* Bounded manual reconstruction, 2026-10-25; not linked.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * 204/212 bytes; us: 0/4 placements; us2: 0/4 placements; pal: 0/4 placements.
 * The complete position copy uses the reviewed helper. The list head and cache retain pointer
 * types; the head requires absolute addressing. The cached pointer is read before the random-value
 * store, as observed. Header constant sharing and store scheduling, list tag materialization and
 * list-base allocation remain different.
 * Reopen with original header field or list-tag lifetime evidence, rather than inventing volatile
 * accesses or barriers.
 * Prior complete variants and diagnostic dumps are preserved privately.
 * No candidate or linked-build credit is claimed.
 */

extern char *func_0029EFD0(int);
extern void func_00282C88(void *);

extern float func_002A7940(void);

extern char *D_L05_001B2528[] MACRO_ADDR;

extern char *D_L05_001B1300 __attribute__((sda));

extern void func_L05_0041C410(char *);

typedef int TI128 __attribute__((mode(TI)));

void *func_L05_0041C118(char *object)
{
    char *p = func_0029EFD0(0x10CF);
    char *e;
    char *found;
    float random;
    char *cached;

    if (p != 0) {
        *(short *)(p + 0x32) = 0xFF;
        *(u8 *)(p + 0x30) = 0xFF;
        *(u8 *)(p + 0x31) = 1;
        qcopy(p + 0x10, object + 0x10);
        func_00282C88(p + 0xF0);
        random = func_002A7940();
        cached = D_L05_001B1300;
        *(float *)(p + 0xF8) = random;
        if (cached == 0) {
            e = D_L05_001B2528[0];
            if (e != 0) {
                found = 0;
                do {
                    if (*(short *)(e + 0xAA) == 0xFBF)
                        found = e;
                    e = *(char **)(e + 0x28);
                } while (e != 0);
                D_L05_001B1300 = found;
            }
        }
        func_L05_0041C410(p);
        *(float *)(p + 0x2C) = *(float *)(*(char **)(p + 0x24) + 0x24);
        return p;
    }
    return 0;
}
