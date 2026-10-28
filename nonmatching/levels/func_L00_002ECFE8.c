/* Current retained result, 28 October 2026: 544/552 bytes at game -O2 -G0. Packet, basis,
 * corners, UV/color setup and the point loop are reconstructed. Reviewed clears and explicit
 * corner pointers improve induction; allocation, initialization order and clear-loop condition
 * still differ. No strict match. Older diagnostic notes below are historical and do not rule
 * out C. */

/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 profile: -O2 -G0 -ffunction-sections.
 * 544/552 compiled/retail bytes. Reconstructs the 0x90-byte packet, basis vectors, quad corner/UV/color setup and dynamic point loop. qzero/qzero_nc and explicit corner pointers improve loop induction but allocation, initialization order and the clear-loop condition still differ.
 * US object comparison only in this retry; no linked strict-build claim.
 * Reopen with a measured allocation, scheduling or source-interface witness.
 */
#include "common.h"
struct BeamCorner { float x, y, z, w; };
struct BeamPacket { struct BeamCorner corner[4]; unsigned int color[4]; float uv[4][2]; long state[4]; };
extern unsigned char D_L00_001B8DC0[];
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00281DE8(void *, int, int, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
void func_L00_002ECFE8(unsigned char *m, float (*points)[4], int count, unsigned int near_color, unsigned int far_color, int texture, float width, float height, float scroll)
{
    float forward[4], direction[4], side[4], position[4];
    struct BeamPacket packet;
    int i;
    func_00282D30(forward, m + 0xc0, -1.0f);
    func_00282CF0(direction, D_L00_001B8DC0, m + 0x10);
    func_00282DD8(side, direction, forward);
    func_00282F20(side, side, width);
    func_00282F20(forward, forward, height);
    *(unsigned int *)(forward + 3) = 0;
    *(unsigned int *)(direction + 3) = 0;
    *(unsigned int *)(side + 3) = 0;
    func_00281DE8(&packet, texture, 1, 128);
    packet.uv[0][0] = scroll;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = scroll;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = scroll + 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = scroll + 1.0f;
    packet.uv[3][1] = 1.0f;
    {
        struct BeamCorner *corner = packet.corner;
        unsigned int *color = packet.color;
        for (i = 0; i < 4; i++, corner++, color++) {
            unsigned int value = near_color;
            qzero_nc(&packet.corner[i]);
            corner->x = i < 2 ? 0.0f : 1.0f;
            corner->y = 0.0f;
            corner->z = i & 1 ? 1.0f : -1.0f;
            corner->w = 1.0f;
            if (1 < i) value = far_color;
            *color = value;
        }
    }
    if (count > 0) {
        int remaining = count;
        float (*next)[4] = points;
        do {
        func_00283098(position, *next++, m + 0xc0);
        func_00282CC0(position, position, m + 0x10);
        position[3] = 1.0f;
        func_00280B90(&packet, forward, 0);
        } while (--remaining);
    }
}

/* from src/levels/shared/L00_002E5918.c: not written this wave. Retail 552 bytes, 27 place(s), first word at L00:002ecfe8.
 * Rule: MMI/LQ/SQ (op 0x1f).
 * No C attempt was made (wave-5 tour-2 discard rule).
 * Retail opens with:
 *   0x002ecfe8  addiu       $sp, $sp, -0x140
 *   0x002ecfec  swc1        $f23, 0x138($sp)
 *   0x002ecff0  sd          $s3, 0xE8($sp)
 *   0x002ecff4  sd          $fp, 0x110($sp)
 *   0x002ecff8  daddu       $s3, $a0, $zero
 *   0x002ecffc  swc1        $f21, 0x128($sp)
 * Kept as data for the maintainers. */
