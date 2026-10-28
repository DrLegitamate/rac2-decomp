/* Current retained result, 28 October 2026: 460/464 bytes in all 28 US placements at the G8
 * profile. Truthful GP/absolute views and a cached owner improve the old 488-byte draft.
 * Failure setup, short-loop padding, scheduling and final clamp remain different. No strict
 * match. Older diagnostic notes below are historical and do not rule out C. */

/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 bounded retry: Default game G8 profile: 460/464 bytes in all 28 primary placements. Truthful GP and absolute views plus a cached owner pointer remove repeated global loads from the old 488-byte diagnostic. Failure-path setup, a short loop pad, register scheduling and final clamp still differ. The two source branches preserve real pointer-to-pointer reloads; no invented array bounds or accesses.
 * Reopen with an independently measured save-profile or allocation witness.
 * No strict linked-build claim. Historical screen-only notes follow the source.
 */
#include "common.h"
struct RecentSlot { unsigned int label; int state; char unknown8[16]; int item; };
struct ItemDescriptor { char unknown0[0x3c]; unsigned short label; char unknown3e[0xa2]; };
struct MenuCell { char unknown0[6]; short item; char unknown8[2]; };
extern unsigned char D_001A7AF8[];
extern unsigned char D_00139568[];
extern struct ItemDescriptor D_00239BA0[];
extern struct RecentSlot **D_001B18D4[] __attribute__((sda));
extern struct RecentSlot **recent_slots SDATA(D_001B18D4);
extern int func_002E5E58(int, int, void *);
void func_003407F8(unsigned char *state, struct MenuCell *cells, int columns)
{
    int item = cells[*(int *)(state + 0x814) + *(int *)(state + 0x818) * columns].item;
    if (!item) goto invalid;
    if (!D_001A7AF8[item]) goto invalid;
    if (D_00239BA0[D_00139568[item]].label == 0xea7e) goto invalid;
    {
        int next = *(int *)(state + 0x7cc) == 7 ? 0 : *(int *)(state + 0x7cc) + 1;
        int i;
        for (i = 0; i < 8; i++) {
            if ((*recent_slots)[i].item == item) break;
        }
        if (i < 8) {
            struct RecentSlot **list = D_001B18D4[0];
            (*list)[i].item = 0;
            (*list)[i].label = D_00239BA0[D_00139568[(*list)[i].item]].label;
        }
        {
            struct RecentSlot **list = D_001B18D4[0];
            (*list)[next].label = D_00239BA0[D_00139568[item]].label;
            (*list)[next].item = item;
            (*list)[next].state = 0;
        }
        func_002E5E58(4, 0, 0);
        goto complete;
    }
invalid:
    func_002E5E58(5, 0, 0);
complete:
    {
        int next = *(int *)(state + 0x7cc) + 1;
        if (next > 7) next = 0;
        *(int *)(state + 0x7cc) = next;
    }
}

/* func_003407F8 - 464 bytes.  Worker attempt, 27 October 2026 (draft below).

   488 B vs 464. Logic decoded: recent-items ring (8 slots of 0x1C at
   **D_001B18D4, ring index state+0x7CC): if item invalid/EA7E flag ->
   func_002E5E58(5,0,0) else remove existing slot of same item (zero +0x18, +0
   = name of D_00139568[0]) then write item at next slot and
   func_002E5E58(4,0,0); finally ring index = idx+1>7?0:idx+1.
   Key diff: retail reads D_001B18D4 via $gp (lw 0x28E4($gp)) in the search
   but via lui/lw into a register in the later block (list = D_001B18D4, then
   lw 0(list) before every access); the call func_002E5E58(5,0,0) arg a0=5 is
   in the delay slot of the first beqz. t2/t3 swapped, 6 insns longer. Tried
   sda incomplete array. */

/* in src/game/0033F030.c (needs MenuState, MenuEntry, func_002E5E58 from the file); remove the INCLUDE_ASM; must come after the typedefs */
