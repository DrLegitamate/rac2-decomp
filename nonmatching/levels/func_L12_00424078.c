/* Near miss, not linked. Game -O2 -G8 -ffunction-sections -g.
 * 756/756 bytes; local USA v1.01 check: 0/2 placements.
 * Recovered two packed colors, explicit ID count and color-cycle update loops.
 * Remaining: packed-color expression allocation, count-loop peeling and later
 * ID/target pointer allocation. Three trials retained truthful scalar and
 * incomplete-array address views; equal size is not a match.
 * Reopen with measured source lifetimes for packing and ID traversal.
 */
#include "common.h"

extern void func_0026FEB8(const char *, ...);
extern void func_002A7750(void *, int, int);
extern int func_002A8508(int, int);
extern float func_00283CE0(int);
extern int func_L01_0031BC68(int, int, float);
extern const char D_L12_001B2040[];
extern const char D_L12_001B2070[];
extern unsigned short *D_L12_001FB960[];
extern char *D_L12_001B2E9C[] MACRO_ADDR;
extern int D_L12_001B29C8 SDATA(D_L12_001B29C8);

void func_L12_00424078(char *object)
{
    int *state = *(int **)(object + 0x68);
    int i;
    unsigned short *ids;
    char *target;
    int period;
    float phase;
    switch (*(u8 *)(object + 0x20)) {
    case 0: {
        int j = 0;
        int firstColor = state[0] | (state[1] << 8) | (state[2] << 16) | (state[3] << 24);
        int secondColor = state[4] | (state[5] << 8) | (state[6] << 16) | (state[7] << 24);
        state[10] = firstColor;
        state[11] = secondColor;
        state[9] = 0;
        if (state[12] != -1) {
            state[9] = 1;
            while (++j < 4) {
                if (state[12+j] == -1)
                    break;
                ++state[9];
            }
        }
        if (state[9]) {
            func_0026FEB8(D_L12_001B2040, *(short *)(object + 0xB2));
            func_002A7750(object, 2, -1);
        } else {
            func_0026FEB8(D_L12_001B2070, *(short *)(object + 0xB2));
            func_002A7750(object, 1, -1);
        }
        break;
    }
    case 1:
        if (func_002A8508(*(u8 *)(object + 0x21), -1) >= 2) {
            ids = D_L12_001FB960[*(u8 *)(object + 0x21)];
            do {
                target = D_L12_001B2E9C[0] + ((*ids & 0x7FFF) << 8);
                if (*(u8 *)(target + 0x31)) {
                    period = state[8];
                    phase = func_00283CE0(D_L12_001B29C8 % period);
                    phase = phase * 6.2831855f / func_00283CE0(period);
                    *(int *)(target + 0x78) = func_L01_0031BC68(state[10], state[11], phase - 3.1415927f);
                }
            } while ((short)*ids++ >= 0);
        }
    case 2:
        for (i = 0; i < state[9]; ++i) {
            target = D_L12_001B2E9C[0] + (state[12+i] << 8);
            if (*(u8 *)(target + 0x31)) {
                period = state[8];
                phase = func_00283CE0(D_L12_001B29C8 % period);
                phase = phase * 6.2831855f / func_00283CE0(period);
                *(int *)(target + 0x78) = func_L01_0031BC68(state[10], state[11], phase - 3.1415927f);
            }
        }
        break;
    }
}
