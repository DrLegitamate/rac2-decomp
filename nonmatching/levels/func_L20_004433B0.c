/* Current retained result, 28 October 2026: 344/344 bytes. Object, table-high and best-entry
 * pointers occupy s4/s5/s3 instead of s3/s4/s5. The pointer return remains truthful; caller
 * experiments were restored. No strict match. Older diagnostic notes below are historical and
 * do not rule out C. */

/* 28 October 2026: first full C attempt, 344/344 bytes at
 * -O2 -G8 -ffunction-sections. The object/table-high/best registers
 * cycle s4/s5/s3 instead of s3/s4/s5; table setup also schedules
 * differently. Branch-local first index reads and moving the loop
 * reload before the condition label close the length/branch residues.
 * Three compiles. Actual helper returns checked. Pointer result remains
 * truthful; a future promotion must update the caller declaration
 * and make its stored-address cast explicit. No local/strict match.
 * Prior diagnostic-only notes follow, then the retained source. */
/* func_L20_004433B0 (344 bytes, level 20): NOT ATTEMPTED in this wave; the body is
 * recovered below and the blockers are measured.
 *
 * THE BODY
 *
 *   int func_L20_004433B0(char *arg0)      /* it returns a POINTER: the best object * /
 *   {
 *       char *state = *(char **)(arg0 + 0x68);          /* $s2 * /
 *       char *obj   = (char *)D_L20_001B2F9C + (*(int *)(state + 0x238) << 8);
 *                                                        /* $s0 * /
 *       ...
 *   }
 *
 *   - the frame is 0x50 and the saved registers are $s0..$s5, $ra and $f20 (200.0f);
 *   - $s2 = arg0, $s3 = arg0, $s4 = &D_L20_001FBB20, $s5 = the best object so far;
 *   - `jal f_00449AC8(obj)` and `jal f_00449AD8(obj)`: if EITHER returns non-zero the
 *     walk starts, otherwise the function returns `obj` itself (the `b .L004434E0`
 *     with `daddu $v0,$s0,$zero` in its delay slot).  Both `bnel`s have the load of
 *     `state->0x218` in their delay slot, and the delay slot of a branch-likely is
 *     annulled when the branch is NOT taken, so the index is read only on the paths
 *     that need it: the source has the read INSIDE the `if` of each test;
 *   - the walk: `rec = D_L20_001FBB20[idx]`, and for every entry
 *       obj = D_L20_001B2F9C + ((word & 0x7FFF) << 8);
 *       if (obj == 0) stop;
 *       if (func_003BA3F8(obj) != 0) skip;
 *       f = func_00282E80(obj + 0x10, arg0 + 0x10);
 *       if (f < f20) { f20 = f; best = obj; }
 *     with `rec += 2` at the end of the body;
 *   - the condition block: `(idx & 0xFF) == 0xFF` stops, `D_L20_001B2FB8 < idx` stops,
 *     `rec == 0` stops, then `if (*(s16 *)(rec - 1) >= 0) goto body;` and
 *     `if (rec == (u16 *)D_L20_001FBB20[idx]) goto body;` - the two SEPARATE
 *     `if (...) goto body;` statements are what produce the retail's `bgezl` and
 *     `beql` pair (with one `||` this cc1 emits a plain `bnez`);
 *   - both branch-likelys carry `lhu $v0,0x0($s1)` in their delay slot, so the word
 *     must be read at the TOP of the body, like in func_L20_00440398.
 *
 * THE BLOCKERS
 *
 *   1. the unit has to be a -G8 unit: the limit is read through $gp
 *      (`lw $v0,0x3FC8($gp)` = D_L20_001B2FB8 at gp+0x3FC8), and the retail loads
 *      D_L20_001B2F9C absolutely (`lui`+`lw`, base == dest);
 *   2. the register allocation of the whole body (the same wall as
 *      func_L20_00440398, which is now down to "only the register allocation");
 *   3. the return type: func_L20_00442C10 declares it as `int` and stores the result
 *      as an int, but the retail returns a pointer - the C has to keep the `int`
 *      prototype or the file does not compile.
 */

#include "common.h"

typedef struct { char reserved00[0x20]; unsigned char state; } Level16VendorMoby;
extern int func_L03_003CA138(unsigned char *);
extern unsigned int func_L20_00449AD8(char *);
extern int func_00312B58(Level16VendorMoby *);
extern float func_00282E80(void *, void *);
extern char *D_L20_001B2F9C;
extern unsigned short *D_L20_001FBB20[];
extern int D_L20_001B2FB8 __attribute__((sda));

char *func_L20_004433B0(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *candidate = D_L20_001B2F9C + (*(int *)(state + 0x238) << 8);
    char *best;
    unsigned short *record;
    int index;
    float closest;
    if (func_L03_003CA138((unsigned char *)candidate)) {
        index = *(int *)(state + 0x218);
    } else if (func_L20_00449AD8(candidate)) {
        index = *(int *)(state + 0x218);
    } else {
        return candidate;
    }
    record = D_L20_001FBB20[index];
    best = 0;
    closest = 200.0f;
    goto condition;
body:
    candidate = D_L20_001B2F9C + ((*record & 0x7FFF) << 8);
    if (!candidate) return best;
    if (!func_00312B58((Level16VendorMoby *)candidate)) {
        float distance = func_00282E80(candidate + 0x10, object + 0x10);
        if (distance < closest) {
            closest = distance;
            best = candidate;
        }
    }
    record++;
    index = *(int *)(state + 0x218);
condition:
    if ((index & 255) == 255 || D_L20_001B2FB8 < index || !record) return best;
    if (((short *)record)[-1] >= 0) goto body;
    if (record == D_L20_001FBB20[index]) goto body;
    return best;
}
