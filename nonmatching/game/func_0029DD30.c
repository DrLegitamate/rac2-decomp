/* Near miss: the candidate uses the shared 0x00140000 base and measured
 * negative offsets of -0x6A48 and -0x6898. Current-master -G8 compiles it to
 * 132 bytes against 140; 0/28 USA v1.01 placements. The compiler shares the
 * base and simplifies the branch structure, unlike retail's independent
 * address materializations and branch-likely layout. The retained attempt
 * therefore does not validate the relocation-derived address for this body.
 * An isolated 29 October explicit-goto form with repeated volatile reads
 * also compiles to 132/140 bytes and 0/28. It still uses ordinary bnez/bltz
 * branches and shares the base; the explicit paths do not recover retail's
 * branch-likely layout.
 * Keep the marker in src/ until the complete body matches.
 */
#include "common.h"

extern char D_00140000[];
extern u16 ref_L00_0030EDB0_00[];

typedef struct {
    u8 pad[0x1D];
    volatile u8 value;
} Flag_29DD30;

typedef struct {
    u8 pad[0x5C];
    volatile s32 value;
} Word_29DD30;

int func_0029DD30(void)
{
    Flag_29DD30 *flag = (Flag_29DD30 *)(D_00140000 - 0x6A48);
    Word_29DD30 *word = (Word_29DD30 *)(D_00140000 - 0x6898);

    if (flag->value == 0 && word->value >= 0) {
        ref_L00_0030EDB0_00[0] = 0x1F;
        return 0;
    }
    if (flag->value == 0) {
        if (word->value >= 0)
            return 0;
        ref_L00_0030EDB0_00[0] = 0x1F;
        return 2;
    }
    if (word->value < 0)
        return 0;
    ref_L00_0030EDB0_00[0] = 0x20;
    return 1;
}
