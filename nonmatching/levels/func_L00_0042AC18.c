/* Near miss, not linked. Game -O2 -G0 -ffunction-sections.
 * 380/380 bytes; USA v1.01: 0/4; USA v2.00: 0/4; PAL: no row.
 * Ordinary multiplication emits the measured R5900 three-operand mult directly;
 * the former no-C screen was incorrect. Bit-flag lifetime recovers the prologue
 * and movn selection. Five trials leave two address/handle register allocations
 * different. Reopen with measured sound-record pointer lifetimes.
 */
#include "common.h"

extern float func_00282E48(void *, void *);
extern int func_00282948(char *);
extern int func_L00_0035F640(int, int, int, int);
extern int func_002A77E0(int);
extern void func_002E59F8(int);
extern float D_L00_001B8DC0[];
extern char D_00188660[];
extern char (*D_L00_001B19EC)[32] __attribute__((sda));

void func_L00_0042AC18(char *object)
{
    int *state = *(int **)(object + 8);
    float distance;
    char *sound;
    int kind = 0;
    if (state[0] >= 0) {
        distance = func_00282E48(D_L00_001B8DC0, object + 0x40);
        if (distance < *(float *)(object + 0xC)) {
            sound = D_00188660 + state[4] * 0x70;
            if (*(u8 *)(D_L00_001B19EC[state[0]] + 0x18))
                kind |= 4;
            if (*(char **)(sound + 0x8C) != object || *(u8 *)(sound + 0x74) == 0) {
                if (func_00282948((char *)&state[3])) {
                    state[4] = func_L00_0035F640(state[0], kind, (int)object, 0x400);
                    if (state[2] > 0)
                        state[3] = (int)((state[1] + func_002A77E0(state[2] - state[1])) * 60.0f);
                }
            }
        } else if (distance > *(float *)(object + 0xC) + 1.0f) {
            int handle = state[4];
            if (handle != -1) {
                sound = D_00188660 + handle * 0x70;
                if (*(char **)(sound + 0x8C) == object && *(u8 *)(sound + 0x74))
                    func_002E59F8(handle);
            }
            state[4] = -1;
        }
    }
}
