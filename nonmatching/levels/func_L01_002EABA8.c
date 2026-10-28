/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections, in place in src/levels/shared/L01_002A7248.c.
 * Retail: 552 bytes; compiled: 552 bytes.
 * Coverage: us: 0/5 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Counts a gadget find for the 12-byte table at 0x18C958 by mode (0: once, 1: timed
 * repeat, 2: first find records the planet, 3: unless already flagged) and shows the
 * message through func_00288E18.
 *
 * Control flow, branch layout and every call match. The saved-register roles differ
 * (about 60 lines): retail gives mode $s0, the gadget index $s1 and the high part of
 * D_00189EA0 $s2; cc1 gives the high part $s0, mode $s1 and the index $s2, and the
 * temporaries in the timed blocks follow.
 * Tried: the entry pointer set early, late or after the limit; the limit as a
 * conditional; an extra local; the player pointer as a local (560 bytes).
 */

/* One 12-byte entry of the gadget table: how many were found, when the last was, and the
   planets they were found on. */
typedef struct {
    unsigned short count;
    unsigned short pad;
    unsigned int time;
    int planets;
} Gadget_2EABA8;

extern Gadget_2EABA8 D_0018C958[];
extern char D_00189EA0[];
extern unsigned int D_001A7390;
extern int D_001A79F0;

extern int func_002ACBC8(void *, int);
extern void func_00288E18(int, int);

void func_L01_002EABA8(int message, int gadget, int mode, int item, int other)
{
    Gadget_2EABA8 *g = &D_0018C958[gadget];
    unsigned int now;
    unsigned int last;
    int limit;

    limit = 0xFFFF;
    if (mode == 0)
        limit = 1;
    if (g->count >= limit)
        return;
    if (other != -1 && func_002ACBC8(D_00189EA0, other) != 0) {
        g->count = 0xFFFF;
        return;
    }
    if (func_002ACBC8(D_00189EA0, item) == 0)
        return;
    switch (mode) {
    case 0:
        func_00288E18(message, gadget);
        break;
    case 1:
        now = D_001A7390;
        last = D_0018C958[gadget].time;
        if (now - last >= 0x439 || last == 0) {
            func_00288E18(message, gadget);
        } else if (last < now) {
            D_0018C958[gadget].time = now;
        }
        break;
    case 2:
        if (D_0018C958[gadget].count != 0) {
            now = D_001A7390;
            last = D_0018C958[gadget].time;
            if (now - last >= 0x439 || last == 0) {
                func_00288E18(message, gadget);
            } else if (last < now) {
                D_0018C958[gadget].time = now;
            }
        } else {
            D_0018C958[gadget].count++;
            now = D_001A7390;
            if (D_0018C958[gadget].time < now)
                D_0018C958[gadget].time = now;
            D_0018C958[gadget].planets = D_0018C958[gadget].planets | (1 << D_001A79F0) | 0x80000000;
        }
        break;
    case 3:
        if (D_0018C958[gadget].planets >= 0)
            func_00288E18(message, gadget);
        break;
    }
}
