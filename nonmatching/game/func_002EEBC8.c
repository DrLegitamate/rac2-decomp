/* Retained exact-C attempt: 328/320 bytes.
 * Profile: -O2 -G0 -ffunction-sections.
 * US and US2 0/1; PAL 0/28. RPC binding/polling, retry delay, response publication and the 64-row clear are reconstructed. Loop block ordering, hoisted addresses and response temporary allocation remain different.
 * Local checks only; no strict linked match. Reopen with independent
 * source, allocation or assembler evidence for the stated difference.
 */
#include "common.h"

extern void func_0011CF78(int);
extern int func_0011D450(void *, int, int);
extern int func_0011D810(void *);
extern int func_0011D620(void *, int, int, void *, int, void *, int, void *, void *);
extern char D_001A7248[];
extern int D_001A726C MACRO_ADDR;
extern int D_001A7244 MACRO_ADDR;
extern int D_001A7270 MACRO_ADDR;
extern int D_001A7278 MACRO_ADDR;
extern int D_001A7240 MACRO_ADDR;
extern int D_001A7274 MACRO_ADDR;
extern int D_L00_00215050[][4];

void func_002EEBC8(void)
{
    int response[4];
    int i;
    int *row;
    func_0011CF78(0);
    for (;;) {
        if (func_0011D450(D_001A7248, 17, 1) < 0)
            for (;;) {}
        while (func_0011D810(D_001A7248)) {}
        if (D_001A726C)
            break;
        for (i = 0xFFFF; i != -1; i--) {}
    }
    func_0011D620(D_001A7248, 2, 0, 0, 0, response, 16, 0, 0);
    D_001A7244 = response[1];
    D_001A7270 = response[0];
    D_001A7278 = response[2];
    D_001A7240 = response[0];
    D_001A7274 = 0;
    row = D_L00_00215050[0];
    for (i = 63; i >= 0; i--) {
        row[0] = 0;
        row[1] = 0;
        row += 4;
    }
}
