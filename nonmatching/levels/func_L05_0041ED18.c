/* func_L05_0041ED18 (w2 batch 3, 2026-10-28). Profile -O2 -G8 -ffunction-sections, unit L05_0041ED18-g8.c.
   488/488 bytes, 29 differing lines (was 456/488). Fixed: the pad as a struct view (`lui`/`addiu` per use
   with the high half in $s1), the abs words as incomplete sda arrays, the accepted path returning from inside
   the cases. Left: retail's cases test D_1350 first and share ONE tail test (`beqz $v0` after the last
   load) with a threaded jump to the success block that sits right after case 3, which looks like
   `ok = a ? b : 0` per case without a cmov; every if/ternary/flag spelling tried here gives movz or
   duplicated blocks. */
#include "common.h"

/* func_L05_0041ED18 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/levels/shared/L05_0041ED18-g8.c: 456/488 bytes.
 * US: 0/3 local places; PAL: ABSENT; US2: ABSENT.
 * No strict linked build was run because no local placement matched.
 * Input base lifetime, switch/control block ordering and frame allocation differ. The successful confirmation exits before the failed-confirmation flag and button check. Reopen with measured input layout and block-order evidence.
 */


extern int D_L05_001B904C[] __attribute__((sda));
extern int D_L05_001B13A8 __attribute__((sda));
extern int D_L05_001B13AC __attribute__((sda));
extern int D_L05_001B13EC __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
extern int D_L05_001B1354[] __attribute__((sda));
extern int D_L05_001B1358[] __attribute__((sda));
extern int D_L05_001B13E8 __attribute__((sda));
typedef struct { char pad_000[0x1A0]; union { unsigned long long held; unsigned int word[2]; } pad; } PadView;
extern char D_00138180[];
#define PAD ((PadView *)D_00138180)
extern void ref_L05_0041ED18_00(void *);
extern void func_0029B758(int, int);
extern int func_002E5E58(int, int, void *);
extern int func_002B49E0(int, int, int, int, unsigned char *);

int func_L05_0041ED18(void)
{
    unsigned int buttons;
    if (D_L05_001B904C[0] && !D_L05_001B13AC) {
        func_0029B758(0, (int)ref_L05_0041ED18_00);
        D_L05_001B13A8 = 0;
        D_L05_001B13AC = 1;
    }
    buttons = PAD->pad.word[1];
    if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--D_L05_001B13EC < 0) D_L05_001B13EC = 3;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        if (++D_L05_001B13EC > 3) D_L05_001B13EC = 0;
    }
    if (PAD->pad.word[1] & 0x10)
        func_002B49E0(3, 1, 4, 0, 0);
    if (PAD->pad.word[1] & 0x40) {
        switch (D_L05_001B13EC) {
        case 0:
            { D_L05_001B13E8 = 0; func_002E5E58(4, 0, 0); return -2; }
        case 3:
            if (D_L05_001B1350 && D_L05_001B1354[0] && D_L05_001B1358[0]) { D_L05_001B13E8 = 0; func_002E5E58(4, 0, 0); return -2; }
            break;
        case 1:
            if (D_L05_001B1350) { D_L05_001B13E8 = 0; func_002E5E58(4, 0, 0); return -2; }
            break;
        case 2:
            if (D_L05_001B1350 && D_L05_001B1354[0]) { D_L05_001B13E8 = 0; func_002E5E58(4, 0, 0); return -2; }
            break;
        }
        func_002E5E58(5, 0, 0);
        D_L05_001B13E8 = 1;
    }
    if (PAD->pad.held & 0xA000000000ULL)
        func_002E5E58(5, 0, 0);
    return -2;
}