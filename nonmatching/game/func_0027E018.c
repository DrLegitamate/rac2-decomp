/* First C reconstruction of func_0027E018, based on its retail GIF packet body.
 * Current-master isolated qcopy-profile recheck (28 October 2026):
 * `python3 tools/check.py func_0027E018 --diff` produced 368/380 bytes and
 * 0/28 USA v1.01 placements. The source marker and temporary qcopy unit/flags
 * were restored after measurement.
 * A temporary `-G8` qcopy unit, motivated by retail's GP-relative packet-cursor
 * store, measured 340/380 bytes and 0/28; this profile did not close the gap.
 * The source uses the caller's eight integer coordinates/UV values followed by
 * the two stack-passed 64-bit color and texture arguments. Keep this in
 * nonmatching until a linked build passes every placement.
 */
#include "common.h"

typedef int TI128_27E018 __attribute__((mode(TI)));

extern unsigned char *D_001B22A8 __attribute__((sda));
extern volatile int D_001A7350 __attribute__((sda));
extern volatile int D_001A7354 __attribute__((sda));
extern TI128_27E018 D_001AC800;

void func_0027E018(int x, int y, int width, int height,
                   int u, int v, int texWidth, int texHeight,
                   unsigned long long color, unsigned long long texture)
{
    unsigned char *cursor = D_001B22A8;
    unsigned char *packet;
    int sx0, sx1, sy0, sy1;
    unsigned int tu0, tu1, tv0, tv1;
    unsigned long long screenTL, screenTR, screenBL, screenBR;
    unsigned long long texTL, texTR, texBL, texBR;

    *(unsigned int *)(cursor + 0x00) = 0x10000007;
    *(unsigned int *)(cursor + 0x04) = 0;
    *(unsigned int *)(cursor + 0x08) = 0;
    *(unsigned int *)(cursor + 0x0C) = 0x50000007;
    cursor += 0x10;
    D_001B22A8 = cursor;
    qcopy(cursor, &D_001AC800);
    cursor += 0x10;
    D_001B22A8 = cursor;
    packet = cursor;
    *(unsigned long long *)(packet + 0x00) = texture;
    *(unsigned long long *)(packet + 0x08) = 0x154;
    *(unsigned long long *)(packet + 0x10) = color;

    sx0 = (x << 4) + D_001A7350 - 8;
    sx1 = ((x + width) << 4) + D_001A7350 - 8;
    sy0 = (y << 4) + D_001A7354 - 8;
    sy1 = ((y + height) << 4) + D_001A7354 - 8;
    tu0 = (unsigned int)u << 4;
    tu1 = (unsigned int)(u + texWidth) << 4;
    tv0 = (unsigned int)v << 20;
    tv1 = (unsigned int)(v + texHeight) << 20;

    screenTL = (unsigned long long)((long long)sx0 | ((long long)sy0 << 16)) | 0xFFFFF00000000000ULL;
    screenTR = (unsigned long long)((long long)sx1 | ((long long)sy0 << 16)) | 0xFFFFF00000000000ULL;
    screenBL = (unsigned long long)((long long)sx0 | ((long long)sy1 << 16)) | 0xFFFFF00000000000ULL;
    screenBR = (unsigned long long)((long long)sx1 | ((long long)sy1 << 16)) | 0xFFFFF00000000000ULL;
    texTL = tv0 + tu0;
    texTR = tv0 + tu1;
    texBL = tv1 + tu0;
    texBR = tv1 + tu1;

    *(unsigned long long *)(packet + 0x18) = texTL;
    *(unsigned long long *)(packet + 0x20) = screenTL;
    *(unsigned long long *)(packet + 0x28) = texTR;
    *(unsigned long long *)(packet + 0x30) = screenTR;
    *(unsigned long long *)(packet + 0x38) = texBL;
    *(unsigned long long *)(packet + 0x40) = screenBL;
    *(unsigned long long *)(packet + 0x48) = texBR;
    *(unsigned long long *)(packet + 0x50) = screenBR;
    *(unsigned long long *)(packet + 0x58) = 0;
    cursor += 0x60;
    D_001B22A8 = cursor;
}

/* 29 Oct: a volatile global packet-cursor rewrite measured 440/380 in all 28 placements; it was worse than the retained 368-byte candidate. */
