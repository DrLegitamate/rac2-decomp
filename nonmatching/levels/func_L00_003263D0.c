/* Batch 3 (2026-10-28) handoff notes:
Best C: draft.c (variant 'alpha inline at the sb store'), size 592/592. Needs cflags line -O2 -G0 -ffunction-sections -frac2-zero-ti-por. Remaining: register allocation only. Retail keeps fixed_rotation (t2) spilled at sp+0x50 and has count=fp, color=s7, payload=s6, r=s4,b=s3,g=s2, alpha/colored=s1 (alpha = srl s1,s7,24 computed in the delay slot of the random-range call, BEFORE it, and kept in s1 across the func_3120B8 call). Ours (alpha at the store) keeps fixed_rotation in fp. With alpha computed early as in the old draft, loop.c hoists the srl out of the loop and spills it (600 B); retail did not hoist it. Reopen: find the source form where alpha stays inside the loop in a saved reg.

Differing lines:
  003263D4  sd          $s6, 0x90($sp)               | sd          $s7, 0x98($sp)
  003263D8  sd          $s7, 0x98($sp)               | swc1        $f24, 0xD0($sp)
  003263DC  daddu       $s6, $t1, $zero              | daddu       $s7, $t1, $zero
  003263E0  sd          $fp, 0xA0($sp)               | swc1        $f23, 0xC8($sp)
  003263E4  daddu       $s7, $a2, $zero              | mov.s       $f24, $f12
  003263E8  swc1        $f24, 0xD0($sp)              | swc1        $f22, 0xC0($sp)
  003263EC  daddu       $fp, $t2, $zero              | mov.s       $f23, $f13
  003263F0  swc1        $f23, 0xC8($sp)              | swc1        $f21, 0xB8($sp)
  003263F4  mov.s       $f24, $f12                   | mov.s       $f22, $f14
  003263F8  swc1        $f22, 0xC0($sp)              | sd          $s0, 0x60($sp)
  003263FC  mov.s       $f23, $f13                   | mov.s       $f21, $f15
  00326400  swc1        $f21, 0xB8($sp)              | sd          $s1, 0x68($sp)
  00326404  mov.s       $f22, $f14                   | sd          $s2, 0x70($sp)
  00326408  sd          $s0, 0x60($sp)               | sd          $s3, 0x78($sp)
  0032640C  mov.s       $f21, $f15                   | sd          $s4, 0x80($sp)
  00326410  sd          $s1, 0x68($sp)               | sd          $s5, 0x88($sp)
  00326414  sd          $s2, 0x70($sp)               | sd          $s6, 0x90($sp)
  00326418  sd          $s3, 0x78($sp)               | sd          $fp, 0xA0($sp)
  0032641C  sd          $s4, 0x80($sp)               | sd          $ra, 0xA8($sp)
  00326420  sd          $s5, 0x88($sp)               | swc1        $f25, 0xD8($sp)
  00326424  sd          $ra, 0xA8($sp)               | swc1        $f20, 0xB0($sp)
  00326428  swc1        $f25, 0xD8($sp)              | sw          $a0, 0x40($sp)
  0032642C  swc1        $f20, 0xB0($sp)              | sw          $a1, 0x44($sp)
  00326430  sw          $a0, 0x40($sp)               | sw          $a3, 0x48($sp)
  00326434  sw          $a1, 0x44($sp)               | sw          $t0, 0x4C($sp)
  00326438  sw          $a3, 0x48($sp)               | blez        $a2, . + 4 + (0x67 << 2)
  0032643C  blez        $s7, . + 4 + (0x66 << 2)     | sw          $t2, 0x50($sp)
  00326440  sw          $t0, 0x4C($sp)               | addiu       $v0, $sp, 0x20
  00326444  addiu       $v0, $sp, 0x20               | mtc1        $zero, $f20
  00326448  mtc1        $zero, $f20                  | lui         $at, 0x3C88

UPDATE: draft.c now: one local `t` reused for alpha then the colored flag (stops loop.c hoisting the srl), and `for (i = 0; i < count; i++)` with i unused in the body (gives retail's `blez a2` then `daddu fp,a2,zero` count copy, count in fp, color in s7). 596 B vs 592, 39 masked lines. Left: t lands in s2 and g in s1 (retail t=s1, g=s2); sb 0x23 sits before the bne (retail: in its delay slot); packing sll/or order. Declaration order and the order of the r/t/b/g statements (120 permutations) change nothing.
*/

#include "common.h"
typedef int TI __attribute__((mode(TI)));
typedef union { TI q; float f[4]; } Vector;
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern char *func_00273730(char *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void func_L00_0039B288(char *);
extern void func_002A0488(char *, unsigned long, unsigned long, unsigned long);

void func_L00_003263D0(char *owner, void *origin, int count, int mode,
                      void *velocity_origin, int color, Vector *fixed_rotation,
                      float radius, float speed, float low_scale, float high_scale)
{
    Vector velocity, position, rotation, random_rotation;
    char *effect, *payload;
    int kind, variant;
    int r, g, b, t;
    int i;
    float life;
    for (i = 0; i < count; i++) {
        func_002A7A00(&velocity, 0.0f, speed * 0.016666668f);
        func_00282CC0(&velocity, &velocity, velocity_origin);
        func_002A7A00(&position, 0.0f, radius);
        func_00282CC0(&position, &position, origin);
        random_rotation.q = 0;
        random_rotation.f[0] = func_002A7940();
        random_rotation.f[2] = func_002A7940();
        rotation.q = random_rotation.q;
        if (fixed_rotation != 0)
            qcopy(&rotation, fixed_rotation);
        kind = mode ? 2 : 1;
        variant = func_002A77E0(4);
        life = func_002A7878(10.0f, 20.0f);
        effect = func_00273730(owner, kind, 0x43e, variant, &position, &rotation, &velocity, 0xff, 180.0f, life);
        if (effect != 0) {
            *(void (**)(char *))(effect + 0x64) = func_L00_0039B288;
            r = color & 0xff;
            t = (unsigned int)color >> 24;
            *(float *)(effect + 0x2c) = *(float *)(*(char **)(effect + 0x24) + 0x24) * func_002A7878(low_scale, high_scale);
            b = (color >> 16) & 0xff;
            g = (color >> 8) & 0xff;
            payload = *(char **)(effect + 0x68);
            func_002A0488(effect, r, g, b);
            ((unsigned char *)effect)[0x23] = t;
            t = (r != g || r != b);
            *(u32 *)(payload + 0x50) = (t << 24) | (b << 16) | (g << 8) | r;
        }
    }
}
