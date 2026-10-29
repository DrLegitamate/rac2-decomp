/* func_002D8338: retained near miss, profile-corrected 29 October 2026.
 * The function reads D_001B1840 through $gp, so a usable definition belongs
 * in a -G8 sibling of 002D5E98.c. In a temporary `src/game/002D8338-g8.c`
 * with the same -G8 profile, the retained state<2 / state-0-first dispatch is
 * 360/372 bytes and 0/28 USA v1.01 placements. Other G8 probes measured
 * 336 bytes (switch 1,0 and explicit goto), 344 bytes (if/else), and 352 bytes
 * (switch 0,1); none matches. The earlier 344-360 byte figures were from the
 * containing -G0 unit and are not profile-valid. The retained form is closest
 * in size, but dispatch, saved-register setup, table traversal and state-update
 * scheduling still differ. PAL/USA v2.00 images are absent, so no checks ran.
 */

/* in src/game/002D5E98.c replacing the INCLUDE_ASM; uses D_001A63AC, D_001F2958, D_0014B540, D_001F2840, D_001B1840(sda), func_002B7B18 already declared above */
extern unsigned char D_001A7BB4;
extern void func_00282AB0(char *, char *, int);
extern char D_00254E78[];

int func_002D8338(char *object)
{
    int state = *(int *)(object + 0x50);

    if (state < 2) {
        if (state == 0) {
            if (D_001A63AC == 0) {
                if (func_002B7B18(D_001F2958,
                                  D_0014B540.start + D_0014B540.offset,
                                  D_0014B540.length) != 0)
                    *(int *)(object + 0x50) = 1;
                else
                    *(int *)(object + 0x50) = 3;
            }
        } else if (state == 1) {
            if (D_001A63AC == 0) {
                char *base = (char *)&D_001F2840;
                char *data = *(char **)(base + 0x118);
                int *entry = (int *)(data + ((int *)data)[D_001A7BB4]);
                int count = entry[0];
                int size = entry[1];
                char *q;
                int i;

                func_00282AB0(data, (char *)(entry + 2), ((size + 3) & -4) - 8);
                *(int *)(object + 0x54) = D_001B1840;
                *(int *)(object + 0x38) = *(int *)(D_00254E78 + 0x2C);
                *(int *)(D_00254E78 + 0x2C) = count;
                D_001B1840 = *(int *)(base + 0x118);
                q = *(char **)(base + 0x118);
                for (i = 0; i < *(int *)(D_00254E78 + 0x2C); i++)
                    *(int *)(q + i * 16) += (int)(q - 8);
                *(int *)(object + 0x10) &= ~4;
                *(int *)(object + 0x50) = 2;
            }
        }
    }
    return 0;
}
