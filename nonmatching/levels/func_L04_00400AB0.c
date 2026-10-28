/* Game -O2 -G0, 648/664 bytes, 0/2 USA places. Both nearest-point
 * scans reconstruct exactly through +0x104; route selection merges the
 * table base across class branches and allocates the three route loads differently.
 * Next: preserve the actual route-record types before reconsidering block options.
 */
#include "common.h"
extern char *D_L04_001FE340[];
extern void func_00282CF0(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern char ref_L04_00400AB0_0[];
extern int D_001A79F0 SDATA(D_001A79F0);
int func_L04_00400AB0(char *object, char *path, int restrict_route)
{
    float delta[4];
    float best = 99999.0f;
    float distance;
    int nearest = 0, i, j, index, count, first_index, second_index, third_index;
    char *point;
    char *state;
    char *first, *second, *third;
    for (i = 0; i < *(int *)path; i += 5) {
        func_00282CF0(delta, object + 0x10, path + 0x10 + i * 16);
        distance = func_L00_002EE290(delta);
        if (distance < best) {
            best = distance;
            nearest = i;
        }
    }
    count = *(int *)path;
    for (j = -5; j < 5; j++) {
        index = nearest + j;
        if (index < 0) index += count;
        else if (index >= count) index -= count;
        func_00282CF0(delta, object + 0x10, path + 0x10 + index * 16);
        distance = func_L00_002EE290(delta);
        if (distance < best) {
            nearest = index;
            best = distance;
        }
    }
    if (restrict_route) {
        if ((int)ref_L04_00400AB0_0 == 40 || D_001A79F0 == 4) {
            state = *(char **)(object + 0x68);
            if (*(short *)(object + 0xaa) == 0xbbc) index = *(int *)(state + 0x6f8);
            else index = *(int *)(state + 0x6c);
            if (path == D_L04_001FE340[index] && nearest >= 105 && nearest <= 123) nearest = 124;
        } else if (D_001A79F0 == 11) {
            state = *(char **)(object + 0x68);
            if (*(short *)(object + 0xaa) == 0xbbc) {
                third_index = *(int *)(state + 0x6e8);
                first_index = *(int *)(state + 0x6fc);
                second_index = *(int *)(state + 0x6e0);
            } else {
                third_index = *(int *)(state + 0x5c);
                first_index = *(int *)(state + 0x70);
                second_index = *(int *)(state + 0x54);
            }
            third = D_L04_001FE340[third_index];
            first = D_L04_001FE340[first_index];
            second = D_L04_001FE340[second_index];
            if (path == first) {
                if ((unsigned int)(nearest - 12) < 10) nearest = 22;
                else if ((unsigned int)(nearest - 59) <= 11) nearest = 71;
            } else if (path == second) {
                if ((unsigned int)(nearest - 183) < 20) nearest = 203;
                else if ((unsigned int)(nearest - 55) <= 6) nearest = 62;
            } else if (path == third) {
                if ((unsigned int)(nearest - 4) <= 4) nearest = 9;
            }
        }
    }
    return nearest;
}
