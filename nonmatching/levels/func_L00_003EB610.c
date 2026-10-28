/* Updated retained constructor: game -O2 -G8, 424/424 bytes, 0/27 USA.
 * The reviewed clobbering qcopy/qzero route preserves all actual transfers,
 * but the three-copy loop still reverses to a countdown. It replaces retail's
 * slti with a nop and uses bgez instead of bnez; search setup and later GPR
 * allocation also differ. Disabling the repeated loop pass leaves this tie.
 * The table uses an explicit unknown-extent GP view, and the shared resident
 * owner pointer now has its canonical D_0018C0B0 identity.
 * Next: an evidenced source loop/lifetime structure; do not invent counter uses.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x58];
    int value;
    char pad2[0x84];
} MappedEntry3EB610;

extern int D_L00_001B0798[] SDATA(D_L00_001B0798);
extern char *D_0018C0B0 NOT_SDA;
extern unsigned char D_00139568[];
extern MappedEntry3EB610 D_L00_00262570[];
extern int func_L00_002D3F30(int, int);
extern char *func_0029EFD0(int);

char *func_L00_003EB610(char *a0, char *a1)
{
    int found = -1;
    int *tab = D_L00_001B0798;
    int *p;
    int i;
    char *obj;

    i = 0;
    p = tab;
    do {
        char *o = (char *)*p;

        if (o == 0 || *(short *)(o + 0xAA) != 0xCB2 || *(unsigned char *)(o + 0x20) == 0xFE
            || *(unsigned char *)(o + 0x20) == 0xFD) {
            found = i;
            break;
        }
        i++;
        p++;
    } while (i < 4);
    if (found < 0)
        return 0;
    if (func_L00_002D3F30(0x1F, 1) == 0)
        return 0;
    obj = func_0029EFD0(0xCB2);
    if (obj != 0) {
        char *st = *(char **)(obj + 0x68);
        int j = 0;
        char *zp = obj + 0xF0;
        char *src;
        char *dst;

        *(char **)(st + 0x34) = a0;
        *(short *)(obj + 0x32) = 0x7F;
        obj[0x30] = 0xFF;
        obj[0x31] = 1;
        *(long long *)(obj + 0x38) = *(long long *)(a0 + 0x38);
        src = D_0018C0B0;
        dst = obj + 0xC0;
        src += 0xC0;
        while (j < 3) {
            qcopy(dst, src);
            j++;
            src += 16;
            dst += 16;
        }
        qzero(zp);
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        qcopy(obj + 0x10, a1);
        *(float *)(obj + 0x2C) = *(float *)(obj + 0x2C) * 0.1f;
        *(int *)(st + 0x38) = -1;
        *(int *)(st + 0x3C) = 0;
        *(int *)(st + 0x40) = D_L00_00262570[D_00139568[0x1F]].value;
        tab[found] = (int)obj;
        *(int *)(st + 0x38) = found;
        obj[0x20] = 0;
    }
    return obj;
}
