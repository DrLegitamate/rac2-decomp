/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 bounded retry: Default game G0 profile: 312/312 bytes. Only the two 300/1 integer constants and their stores use swapped v0/v1; all other measured instructions agree. Named state fields, scalar ordering, a heading temporary, -fno-gcse and -fno-regmove did not qualify. Return from func_002AB1F0 is the actual integer address value and is explicitly cast before dereference.
 * Reopen with an independently measured save-profile or allocation witness.
 * No strict linked-build claim. Historical screen-only notes follow the source.
 */
#include "common.h"
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_002AB1F0(void *);
extern void func_002A75E0(void *, int, int, int, int);
extern void func_002A7470(void *, int, int, int);
struct LaunchState {
    float direction[4];
    char gap10[8];
    float radius, height;
    char gap20[4];
    unsigned int flags;
    char gap28[4];
    short lifetime;
    char gap2e[14];
    unsigned char active;
    char gap3d;
    short delay;
    float heading;
    int age;
};
void func_L08_0032C0D8(unsigned char *m, struct LaunchState *p, int animation, int flags, int frames, float angle)
{
    int effect;
    p->direction[0] = func_00283180(angle) * p->radius;
    p->direction[1] = func_00283198(angle) * p->radius;
    p->direction[2] = p->height;
    p->direction[3] = 1.0f;
    {
        float heading = func_00283B98(angle, 3.141593f);
        short lifetime = 300;
        p->age = 0;
        p->delay = 0;
        p->heading = heading;
        p->lifetime = lifetime;
        p->active = 1;
    }
    effect = func_002AB1F0(m);
    if (effect && *(float *)effect == 0.0f) {
        p->flags |= 0x20;
        *(int *)(m + 0x98) = 0;
    }
    if (p->flags & 2) func_002A75E0(m, animation, frames, flags, 1);
    else func_002A7470(m, animation, frames, flags);
}

/* func_L08_0032C0D8 - 312 bytes, 2 place(s), level 08_tabora, retail at
   0x0032c0d8. Screened with tools/w10_screen.py: 6 call(s)
   [func_00283180@0032C10C, func_00283198@0032C120, func_00283B98@0032C154,
   func_002AB1F0@0032C178, func_002A75E0@0032C1CC, func_002A7470@0032C1E4];
   data addresses materialised [0x40490000]; float constants [0x3f800000];
   $gp-relative small data: no   saves: -; callee-saved registers saved [-];
   words plain C cannot emit [-]. Head: addiu $sp, $sp, -0x40 ; swc1 $f20,
   0x30($sp) ; sd $s0, 0x0($sp) ; mov.s $f20, $f12 ; sd $s1, 0x8($sp) ;
   daddu $s0, $a1, $zero. Not matched in this wave: the body is straight-
   line code whose register allocation and the materialisation of its
   constant addresses have to be reproduced word for word. What would
   unblock it: the exact source expression tree, so this cc1 picks the same
   registers in the same order. */
