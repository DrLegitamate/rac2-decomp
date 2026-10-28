/* Batch 3 (2026-10-28) handoff notes:
# func_L10_0039D5E0 (324 B, 2 places) -- w5 handoff, 10 differing lines (was 11 in the nonmatching/ draft)

draft.c compiles in place in src/levels/shared/L10_0037D200.c (default -G8 flags of that file, size exact) after replacing that file's own `typedef unsigned char u8;` by `#include "common.h"` (needs qcopy, s32, u16) and declaring `extern short D_L10_001B2DB8[];` (unsized: absolute lui/addiu like retail). Store order in the draft is the best of a swap hill-climb (the order kind, duration, first, second, third, width, height, fade, texture, jitter gives 11, a few swaps give 10; random shuffles of the 10 state stores: 15..60). 
Remaining: the saved-register assignment of three once-used inputs: retail s0 = kind(a3), s1 = third(t2), s2 = first(t0), s3 = second(t1), s4 = duration(a2), s5 = texture(t3), s6 = direction(a1), s7 = position(a0), f20 = width, f21 = height, f22 = fade, f23 = jitter; ours swaps duration/second and then the tail: retail does `addiu a0,-1 ; addiu v1,2 ; lui v0,0x1B ; addiu v0,v0,0x2DBC` (constants before the lui), ours lui first.

## check.py --diff (masked, differing lines only; ours | retail)
```
10_hrugis_cloud: instruction at +0x2c differs
  0039D60C  daddu       $s3, $a2, $zero              | daddu       $s3, $t1, $zero
  0039D614  daddu       $s4, $t1, $zero              | daddu       $s4, $a2, $zero
  0039D67C  sw          $s3, 0x10($v1)               | sw          $s4, 0x10($v1)
  0039D684  sw          $s1, 0x1C($v1)               | sw          $s3, 0x18($v1)
  0039D688  sw          $s4, 0x18($v1)               | sw          $s1, 0x1C($v1)
  0039D6B4  lui         $v0, 0x0                     | addiu       $a0, $zero, -0x1
  0039D6B8  addiu       $a0, $zero, -0x1             | addiu       $v1, $zero, 0x2
  0039D6BC  addiu       $v0, $v0, 0x0                | lui         $v0, 0x1B
  0039D6C0  addiu       $v1, $zero, 0x2              | addiu       $v0, $v0, 0x2DBC
  0039D6C4  addiu       $v0, $v0, 0x4                | nop
15_gorn: instruction at +0x2c differs
func_L10_0039D5E0: 0 of 2 places match (src/levels/shared/L10_0037D200.c)
masked diff lines: 10
```
*/

/* needs #include "common.h" in L10_0037D200.c (replacing its own u8 typedef) */
typedef int Quad __attribute__((mode(TI)));
extern void *func_0029EFD0(s32);
extern short D_L10_001B2DB8[];

/* Creates a strip-effect object with its supplied vectors and rendering parameters. */
void *func_L10_0039D5E0(void *position, void *direction, s32 duration, s32 kind,
                       s32 first, s32 second, s32 third, s32 texture,
                       float jitter, float width, float height, float fade) {
    u8 *object = func_0029EFD0(0x133E);
    char *state;
    int i;
    if (object) {
        state = *(char **)(object + 0x68);
        object[0x30] = 255;
        *(u16 *)(object + 0x32) = 255;
        object[0x31] = 1;
        object[0x20] = 0;
        *(s32 *)(state + 0x2C) = kind;
        *(s32 *)(state + 0x10) = duration;
        *(s32 *)(state + 0x14) = first;
        *(s32 *)(state + 0x1C) = third;
        *(s32 *)(state + 0x18) = second;
        *(float *)(state + 0x20) = width;
        *(float *)(state + 0x24) = height;
        *(float *)(state + 0x28) = fade;
        *(s32 *)(state + 0x30) = texture;
        *(float *)(state + 0x34) = jitter;
        qcopy(state, direction);
        qcopy((object + 0x10), position);
        for (i = 2; i >= 0; i--) D_L10_001B2DB8[i] = -1;
    }
    return object;
}
