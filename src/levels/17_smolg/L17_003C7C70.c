#include "include_asm.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef short s16;
typedef char s8;
typedef float f32;

extern s32 D_L17_001FE880[];

extern void func_2EEAF8(s32);
extern void func_2EEB28(s32);
extern void func_320B58(s32, s32);
extern void func_327E68(s32, s32, s32, s32, f32);
extern s32 func_31B160(s32);
extern f32 func_2EF0B0(s32, s32);

extern s32 D_L17_001B2748 __attribute__((sda));
extern s32 func_2F0108(u32, u32, f32);
extern f32 func_2EF4E0(f32);

extern s32 D_L17_001B2C1C __attribute__((sda));

extern s32 D_L17_001C0018;
extern s32 func_2DF570(s32, s32, s32, s32, s32);

INCLUDE_ASM("asm/levels", func_L17_003C7C70);

void func_L17_003C8248(s32 a0)
{
    f32 t = (f32)(D_L17_001B2748 % 150) * (1.0f / 150.0f);
    f32 ang = (t + t) * 3.1415927f;

    if (ang > 3.1415927f)
        ang = ang - 6.2831855f;
    *(s32 *)(a0 + 0x78) = func_2F0108(0x80464646u, 0x80828282u,
                                      (func_2EF4E0(ang) + 1.0f) * 0.5f);
}

typedef int TI128 __attribute__((mode(TI)));

/* A 16-byte vector: the engine's helpers take and return these, and the copies between
   them are quadword moves. */
typedef union {
    TI128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } f;
} Vec4;

extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern f32 func_00282C48(f32);

/* Turns the vector at a1 into the object's frame, then into the world with the matrix at
   a0 + 0xC0, and reports whether both of the first two coordinates stay below the two
   bounds. */
s32 func_L17_003CC798(u8 *a0, TI128 *a1, f32 f1, f32 f2) {
    Vec4 v[1];
    Vec4 mat[4];
    Vec4 w[1];
    Vec4 out[1];

    v[0].q = *a1;
    func_00283698(mat, a0 + 0xC0);
    func_00282CF0(&out[0].q, &v[0].q, a0 + 0x10);
    w[0].q = out[0].q;
    func_002830C0(&w[0].q, &w[0].q, mat);
    if (func_00282C48(w[0].f.x) < f2) {
        if (func_00282C48(w[0].f.y) < f1)
            return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/levels", func_L17_003CC850);


extern u16 *D_L17_001FB720[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit; the limit
   word is loaded in a branch delay slot, so there it becomes the `$gp` form. The pool base is
   the word D_L17_001B2C1C declared above as an int, reached here as a pointer under a second
   name. */
extern u8 *D_L17_001B2C1C_base[] __asm__("D_L17_001B2C1C") __attribute__((sda));
extern s32 D_L17_001B2C38[] __attribute__((sda));

/* The object's state record up to the group word and the word stored beside it. */
typedef struct {
    u8 pad[0x43C];
    s32 group;
    s32 mode;
} L17GroupState;

/* Walks the id list of the state's group and sets the state's mode word to 0x57 for every id
   that has an entity, stopping at the first that has none. */
void func_L17_003E3148(u8 *a0)
{
    L17GroupState *state = *(L17GroupState **)(a0 + 0x68);
    u16 *p;
    u8 *e;

    for (p = D_L17_001FB720[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= D_L17_001B2C38[0] && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L17_001FB720[state->group]);
         p++) {
        e = D_L17_001B2C1C_base[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        state->mode = 0x57;
    }
}

INCLUDE_ASM("asm/levels", func_L17_003E31E8);




void func_L17_003E47E8(s32 a0) {
    s32 s1 = *(s32 *)(a0 + 0x68);

    func_320B58(a0, s1 + 0x50);
    func_2EEAF8(s1 + 0x3FC);
    func_2EEB28(s1 + 0x402);
    if (*(u16 *)(a0 + 0x96) < 0xFFFF) {
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
    }
    func_327E68(a0, s1 + 0x350, 1, 1, 2.5f);
}




/* Claims the shared slot at state+0x720 for this object (index into the object array):
   taken when free or when its holder is in state 0xFE/0xFD, then in mode 1 handed to the
   nearest candidate; returns 1 once this object holds it in mode 2. func_L17_003E6F20
   releases it. */
INCLUDE_ASM("asm/levels", func_L17_003E6DE8);

void func_L17_003E6F20(s32 a0)
{
    s32 obj = *(s32 *)(a0 + 0x68);
    s32 *p = *(s32 **)(obj + 0x720);

    if (*p == (a0 - D_L17_001B2C1C) >> 8) {
        *p = -1;
        *(s32 *)(*(s32 *)(obj + 0x748)) = 0;
    }
}

s32 func_L17_003E6F58(s32 a0) {
    s32 s0;
    s32 s1 = D_L17_001FE880[*(s32 *)(*(s32 *)(a0 + 0x68) + 0x684)];
    s32 s4 = *(s32 *)s1;
    s32 s2 = 0;

    do {
        s32 off;

        s0 = func_31B160(s4);
        off = (s0 << 4) + 0x10;
        if (func_2EF0B0(a0 + 0x10, s1 + off) > 3.0f) {
            return s0;
        }
    } while (++s2 < 5);
    return s0;
}

s32 func_L17_003E7010(s32 a0) {
    s32 s0 = *(s32 *)(a0 + 0x68);

    if (func_2DF570(a0 + 0x10, s0 + 0x240, 0, a0, 0) == 0)
        return 1;
    return D_L17_001C0018 == *(s32 *)(s0 + 0x250);
}

INCLUDE_ASM("asm/levels", func_L17_003E8A58);

INCLUDE_ASM("asm/levels", func_L17_00417DB0);



INCLUDE_ASM("asm/levels", func_L17_0041E208);

INCLUDE_ASM("asm/levels", func_L17_0041EAA8);

INCLUDE_ASM("asm/levels", func_L17_0041ED58);

/* func_L17_0041F180 is defined in L17_collision.c. */

INCLUDE_ASM("asm/levels", func_L17_0041F478);


/* func_L17_00420758 is defined in L17_collision.c. */

/* func_L17_00420A50 is defined in L17_00420A50-g8.c. */

INCLUDE_ASM("asm/levels", func_L17_00420E08);
