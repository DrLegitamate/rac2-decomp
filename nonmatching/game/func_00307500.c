/* func_00307500 - 496 bytes, 28 places (the boot and all 27 levels). Near miss: 476 of 496 bytes, five
 * instructions short, in every place. Compile with -G8 (it reads a float through $gp at -0x38C, so it
 * belongs in a *-g8.c file in src/ once it matches). Remaining differences, against retail:
 *   - the frame is 0xD0 bytes, retail 0xE0: retail keeps s3 = object+0x68+0x30 live across the calls
 *     and materialises 1.0f into f21 before the first call; here the compiler folds s3 into 0x30(s2)
 *     and loads 1.0f late, and it hoists the 16-byte load from +0x30 into the block before the call.
 *   - retail keeps the 16-byte local at sp+0x10 in s1 for both calls that take it.
 *   - the local vectors sit where retail's do (0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90),
 *     and the dead-looking store to 0x70 survives because it is a member of a struct whose address
 *     escapes to func_00282DD8 (the `pair` struct).
 * Tried: a 12-byte packed table copy (ldl/ldr + lw matches), TI128 vector copies, one as a local float,
 * integer zero stores for the pair's first three words (sw $zero, as retail).
 */
#include "common.h"

/* The 128-bit integer mode is what reaches retail's lq/sq copies. */
typedef int TI128 __attribute__((mode(TI)));

typedef struct { float x, y, z, w; } V4;

typedef struct {
    unsigned char pad00[0x10];
    V4 f10;
    unsigned char pad20[0x10];
    V4 f30;
    unsigned char pad40[0xC];
    short f4C;
    unsigned char pad4E[6];
    unsigned int f54;
    unsigned char pad58[4];
    float f5C;
    unsigned char pad60[4];
    void *f64;
} Child;

typedef struct {
    unsigned char pad00[0x10];
    V4 f10;
    unsigned char f20;
    unsigned char pad21[0x47];
    Child *f68;
    unsigned char pad6C[0x54];
    unsigned char fC0[16];
} Obj;

typedef struct { unsigned long long a __attribute__((packed)); unsigned int b; } Table12;

extern float D_001AEC64 __attribute__((sda));
extern Table12 D_001AEC70;

extern void func_002FE8D8(void *a);
extern void func_0029FCC0(void *a, int b, void *c);
extern void *func_002AF580(void *a, void *b, void *c, int d, int e, int f, int g, void *h,
                           float f12, float f13, float f14, float f15, float f16);
extern void func_00282DD8(void *a, void *b, void *c);
extern void func_00282F20(float f, void *a, void *b);
extern void func_002AB6D8(void *a, void *b);
extern float func_002A78D8(float a, float b);
extern void func_00283B98(float a, float b);
extern float func_002A7878(float a, float b);
extern void func_002AF000(void *a, float b, float c, float d);

void func_00307500(Obj *o)
{
    Child *s2 = o->f68;
    V4 local10;
    V4 local90;
    Table12 local20;
    V4 v30;
    V4 v40;
    V4 v50;
    struct {
        V4 a;
        V4 b;
    } pair;
    V4 v80;
    TI128 zero = 0;
    V4 *s3 = &s2->f30;
    float one = 1.0f;
    float r;

    func_002FE8D8(&o->f10);
    func_0029FCC0(o, 0, &local10);
    if (s2->f64 == 0) {
        local20 = D_001AEC70;
        s2->f64 = func_002AF580(&local10, o->fC0, &local90, 0, 0, 0, 0, &local20,
                                6.2831855f, 6.2831855f, D_001AEC64, 0.0f, 0.0f);
        if (s2->f64 != 0)
            o->f20 = 4;
        s2->f5C = 0.0f;
    }
    if (s2->f64 == 0) {
        if (s2->f4C == 0)
            return;
        *(TI128 *)&v80 = zero;
        v80.z = one;
        *(TI128 *)&v40 = *(TI128 *)s3;
        func_00282DD8(&v50, &v40, &v80);
        func_00282F20(one, &v50, &v50);
        func_00282DD8(&pair.a, &v50, &v40);
        *(unsigned int *)&pair.b.x = 0;
        *(unsigned int *)&pair.b.y = 0;
        *(unsigned int *)&pair.b.z = 0;
        pair.b.w = one;
        func_002AB6D8(&v40, &v30);
        r = func_002A78D8(0.78539825f, 1.5707965f);
        func_00283B98(v30.z, r);
        r = func_002A7878(-0.1f, 0.45f);
        func_002AF000((char *)s2 + 0x20, one, r, r);
    }
    *(TI128 *)&s2->f10 = *(TI128 *)s3;
    s2->f4C = 0;
    s2->f54 = 0;
}
