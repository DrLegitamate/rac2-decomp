/* func_002A0250: Opus closer M1 near miss, 26 October 2026; replayed 28 October.
   Profile: -O2 -G8 -ffunction-sections, own -g8 unit.
   Current-master USA v1.01: 172/172 bytes, 0/28; first mismatch +0x60.
   Naming the u16 at 0x10FFB0 as `D_0010FFB0[]` gives the retail head exactly.
   Left: in the tail retail stores the old packet pointer early and increments
   it in place in $v0; 1,080 statement orders and 192 type combinations did
   not move it. */
#include "common.h"
extern char D_0010FFC0[];
extern unsigned short D_0010FFB0[];
extern char D_00100080[];
extern int ref_002A0250_00;
extern char *ref_002A0250_01;
extern int ref_002A0250_02;
extern int ref_002A0250_03;
extern char *ref_002A0250_04;
extern int ref_002A0250_05;
extern int ref_002A0250_06;
extern int ref_002A0250_07;
extern int D_001A72D0;
extern int D_001A72D4;
extern void func_002FC410(unsigned int, unsigned int);
extern void func_002FC070(int);
extern void func_002FC560(unsigned int, unsigned long long);

void func_002A0250(void)
{
    char *p;

    func_002FC410((unsigned int)D_0010FFC0, D_0010FFB0[0]);
    ref_002A0250_00 = 6;
    func_002FC070((int)D_00100080);
    func_002FC560(0x47, 0x5360B);
    p = ref_002A0250_01;
    ref_002A0250_04 = p;
    ref_002A0250_06 = ref_002A0250_02 + 0xFFFF0000;
    ref_002A0250_05 = ref_002A0250_03;
    D_001A72D0 = D_001A72D4;
    ref_002A0250_01 = p + 0x10;
    ref_002A0250_07 = 0;
}
