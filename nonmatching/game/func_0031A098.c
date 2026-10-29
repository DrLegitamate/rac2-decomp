/* Current-master USA v1.01 near miss: best C candidate is 204 bytes against 188, 0/3 placements.
   Retail loads four aligned vectors before storing them to its 0x40-byte local frame, then copies
   each vector to the output and multiplies its y/z fields by 2. The approved qcopy form is closest.
   Aggregate assignment used ldl/ldr and measured 276 bytes; aligned aggregate assignment measured
   212 bytes. -fno-strength-reduce kept 204 bytes and add.s; this compiler rejects -frounding-math
   and -fno-tree-reassoc. The batched load/store order, mul.s selection and register allocation remain. */
#include "common.h"

typedef struct {
    float x, y, z, w;
} V4_0031A098;

extern V4_0031A098 D_001AFAA0[];

void func_0031A098(void *record)
{
    V4_0031A098 temp[4];
    unsigned char *base = (unsigned char *)record;
    V4_0031A098 *src = temp;
    unsigned char *dst = base;
    int count = 3;

    qcopy(&temp[0], &D_001AFAA0[0]);
    qcopy(&temp[1], &D_001AFAA0[1]);
    qcopy(&temp[2], &D_001AFAA0[2]);
    qcopy(&temp[3], &D_001AFAA0[3]);
    do {
        qcopy(dst, src);
        ((float *)dst)[1] *= 2.0f;
        ((float *)dst)[2] *= 2.0f;
        src++;
        dst += 16;
    } while (count-- != 0);

    *(u64 *)(base + 0x80) = 0x0000FF9000000260ULL;
    *(float *)(base + 0x6C) = 1.0f;
    *(u64 *)(base + 0x70) = 0;
    *(u32 *)(base + 0x50) = 0;
    *(u32 *)(base + 0x54) = 0;
    *(u32 *)(base + 0x58) = 0;
    *(float *)(base + 0x5C) = 1.0f;
    *(float *)(base + 0x60) = 1.0f;
    *(u32 *)(base + 0x64) = 0;
    *(float *)(base + 0x68) = 1.0f;
}
