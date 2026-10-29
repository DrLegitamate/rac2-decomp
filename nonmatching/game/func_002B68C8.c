#include "include_asm.h"

/* Initialises the call state at 0x001A63A8, then runs the two channel helpers.
   Current game-profile probe in the original unit: 108 bytes, 0/1 USA v1.01
   boot placement. The size matches. Retail writes the final -1 to +0x24 after
   all the zeroing stores, in the delay slot of func_002B66F0. With ordinary
   stores, cc1 schedules it before the +0x3C mode store; making it volatile
   keeps it after the other stores but still leaves it in the same wrong early
   position rather than the call delay slot. Making every store volatile keeps
   order but leaves a nop in that slot. Do not add artificial volatile reads,
   barriers or fake dependencies to force the schedule. */
extern void func_0026FEB8(void *);
extern char D_001AA198[];
extern void func_002B6938(void);

void func_002B68C8(void)
{
    char *state;
    short mode;

    func_0026FEB8(D_001AA198);
    state = D_001A63A8;
    mode = -1;
    *(short *)(state + 0x3C) = mode;
    state[0x40] = 0x20;
    state[0x41] = 0;
    state[0x42] = 0;
    state[0x43] = 0;
    *(u32 *)(state + 0x44) = 0;
    *(short *)(state + 0x4E) = 0;
    *(u32 *)(state + 0x68) = 0;
    *(short *)(state + 0x72) = 0;
    *(u32 *)(state + 0x8C) = 0;
    *(short *)(state + 0x96) = 0;
    *(int *)(state + 0x24) = mode;
    func_002B66F0();
    func_002B6938();
}
