/* Batch 3 (2026-10-28) handoff notes:
draft.c matches 2/2 (us, us2) but only with a static inline accessor resident_block() returning D_00189E20 (rejected: it exists only to stop CSE).
Structure: five separate else-if arms, the K==0x40 arm split in two (">0.05" then "==0") so the K==0x41 test is a join and reloads.
Without the accessor the address of D_00189E20 stays in a register (85 lines differ); retail rebuilds lui-hi copy + addiu at each arm.
*/

extern char D_00189E20[];
extern void func_L00_002D2168(int, int, float);
/* The resident game block, re-read at each use. */
static __inline__ char *resident_block(void) { return D_00189E20; }

void func_L16_00395858(char *object)
{
    char *state = *(char **)(object + 0x68);
    if ((*(int *)(resident_block() + 0xC28) & 2) && *(unsigned char *)(*(char **)(resident_block() + 0x2290) + 0x43) == 0x44)
        func_L00_002D2168(0x3f, 0, 7.0f);
    else if (*(unsigned char *)(*(char **)(resident_block() + 0x2290) + 0x43) == 0x3f && *(float *)(state + 0x30) != 0.0f)
        func_L00_002D2168(0x40, 0, 10.0f);
    else if (*(unsigned char *)(*(char **)(resident_block() + 0x2290) + 0x43) == 0x40 && *(float *)(state + 0x30) > 0.05000000447f)
        func_L00_002D2168(0x41, 0, 10.0f);
    else if (*(unsigned char *)(*(char **)(resident_block() + 0x2290) + 0x43) == 0x40 && *(float *)(state + 0x30) == 0.0f)
        func_L00_002D2168(0x3f, 0, 10.0f);
    else if (*(unsigned char *)(*(char **)(resident_block() + 0x2290) + 0x43) == 0x41 && *(float *)(state + 0x30) < 0.05000000447f)
        func_L00_002D2168(0x40, 0, 10.0f);
}
