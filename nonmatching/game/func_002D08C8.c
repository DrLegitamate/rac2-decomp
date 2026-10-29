/* func_002D08C8 (100 bytes, 28 places). Current compliant candidate with
 *     -O2 -G8 -ffunction-sections: 96 bytes, 0/28 USA v1.01 places. An earlier
 * 100-byte draft matched only after declaring D_001A7A0A volatile, but its
 * uses elsewhere are ordinary global accesses and that qualifier is unsupported.
 * This version models the byte as ordinary small data; its load remains four
 * bytes later than retail, which puts that load in the prior branch delay slot.
 * A separate ordinary-memory `NOT_SDA` probe still measured 96 bytes: the
 * compiler hoisted its address materialization ahead of the second test, so it
 * did not reproduce retail's adjacent `lui`/`lbu` after that test. Reading the
 * byte into a local before the outer test also remained 96 bytes and moved the
 * load into the outer branch delay slot. Other known structure: the 0x1F2848 store precedes the nested tests, the four
 * stores use one sda int[4], and the two per-placement $gp words use ref_ names.
 * 29 October 2026 scheduler probes: both `-fno-schedule-insns` and
 * `-fno-schedule-insns2` remain 96/100 bytes, 0/28. Each keeps the ordinary
 * byte load in a branch delay slot rather than after the test as retail does. */
/* A 29 October early-guard form (`if (!outer) return 0;` followed by the
 * stores and tests) compiles to 104 bytes, 0/28 in a temporary G8 unit. It
 * moves the initial store after the outer guard and adds a separate return;
 * this is farther from the 100-byte retail layout than the retained 96-byte
 * candidate. */
#include "common.h"

extern int D_001A8CFC;
extern int ref_002D08C8_01 __attribute__((sda));
extern int D_001F2848[];
extern int D_001ABA0C[4] __attribute__((sda));
extern int ref_002D08C8_02 __attribute__((sda));
extern unsigned char D_001A7A0A __attribute__((sda));

int func_002D08C8(void)
{
    if (D_001A8CFC != 0) {
        D_001F2848[0] = 1;
        if (ref_002D08C8_01 != 0)
            D_001ABA0C[1] = 1;
        if (ref_002D08C8_02 != 0)
            D_001ABA0C[2] = 1;
        if (D_001A7A0A != 0) {
            D_001ABA0C[0] = 1;
            D_001ABA0C[3] = 1;
        }
    }
    return 0;
}
