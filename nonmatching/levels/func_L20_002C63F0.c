/* Retained exact-C reconstruction: 684/704 bytes.
 * Profile: -O2 -G0 -ffunction-sections.
 * US and US2 0/1; PAL absent. The old draft incorrectly replaced the live distance return with 0.53 and inverted its comparison; it also required the wrong state-byte branch. These guards, three float return contracts and the 0.35000002 literal are corrected. Separate real hero views recover the caller-saved first-stage pointer, but branch/store scheduling and address lifetimes remain different. Earlier size observations are not semantic validation.
 * No strict linked match. Reopen with independent source, allocation or
 * compiler evidence for the remaining difference; do not repeat tied forms.
 */
#include "common.h"
extern char D_00189E20[];
extern float func_00282E80(void *, void *);
extern float func_002AA2E8(f32 *, f32, f32);
extern float func_002AA3A8(f32 *, f32 *, f32, f32, f32, f32);
extern char D_0018A070[];

void func_L20_002C63F0(void)
{
    {
    char *D = D_00189E20;
    u8 state = *(u8 *)(D + 0x22B4);
    s32 x;

    switch (state) {
    case 1:
        *(f32 *)(D + 0x258) = 0.59999996f;
        *(f32 *)(D + 0x260) = 0.3f;
        *(f32 *)(D + 0x25C) = 0.45000002f;
        break;
    case 0:
    case 4:
        *(f32 *)(D + 0x258) = 0.8f;
        *(f32 *)(D + 0x260) = 0.45f;
        *(f32 *)(D + 0x25C) = 0.7f;
        break;
    }
    if (*(s32 *)(D + 0x229C) == 4) {
        if (*(s16 *)(D + 0x4AC) < *(s32 *)(D + 0x1B8)) {
            if (*(u8 *)(D + 0x49E) == 0)
                *(f32 *)(D + 0x25C) = *(f32 *)(D + 0x4B8);
        }
    } else if (*(s32 *)(D + 0x2294) == 6) {
        *(f32 *)(D + 0x25C) = 0.5f;
    } else if (*(s32 *)(D + 0x2294) == 4) {
        *(f32 *)(D + 0x258) = 0.35000002f;
    } else {
        x = *(s32 *)(D + 0x229C) - 0x11;
        if ((u32)x < 2) {
            *(s32 *)(D + 0x25C) = 0;
            *(s32 *)(D + 0x258) = 0;
        } else if (*(u8 *)(D + 0x1492) != 0 && *(s32 *)(D + 0x340) != 0) {
            *(f32 *)(D + 0x258) = 0.8f;
            *(f32 *)(D + 0x25C) = 0.9f;
        } else if (*(s32 *)(D + 0x2294) == 0x7C) {
            *(f32 *)(D + 0x260) = 0.8f;
        }
    }
    }
    {
    char *D = D_00189E20;
    if (*(u8 *)(D + 0x287) != 0 &&
        *(s32 *)(D + 0x22A4) != 0x12 && *(s32 *)(D + 0x22B0) != 0x12 &&
        (*(u8 *)(D + 0x22B4) != 0 || !(*(f32 *)(D + 0x254) < 0.53f)) &&
        *(s32 *)(D + 0x229C) != 0x11 && *(u8 *)(D + 0x1494) == 0) {
        float distance = func_00282E80(D + 0x240, D + 0x80);
        if (*(f32 *)(D + 0x264) * 0.5f < distance) {
            char *E = D_0018A070;
            func_002AA2E8((f32 *)E, *(f32 *)(D + 0x258), 0.02f);
            func_002AA2E8((f32 *)(E + 0x4), *(f32 *)(D + 0x25C), 0.02f);
            func_002AA3A8((f32 *)(E + 0x14), (f32 *)(E + 0x18),
                          *(f32 *)(D + 0x260), 0.02f, 0.3f, 0.06666667f);
        }
    }
    }
}
