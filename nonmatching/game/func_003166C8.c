/* 28 October 2026: 772/772 bytes at -O2 -G0 -ffunction-sections.
 * MACRO_ADDR on the vector constant removes one saved address and
 * reaches retail size. The first qcopy address is retained across the
 * angular updates, shifting record/index/position allocation. A plain
 * TI first copy is 760 bytes and folds the measured store address.
 * Reopen with measured source lifetime evidence for the base vector.
 * No strict match is claimed. */
#include "common.h"

extern char D_0022AA10[];
extern char D_001B2520[] MACRO_ADDR;
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern char *func_002AB1F0(void *);
extern void func_002B00B0(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00282948(void *);

#define RF(offset) (*(float *)(record + (offset)))
#define RI(offset) (*(int *)(record + (offset)))

void func_003166C8(int type)
{
    float offset[4] __attribute__((aligned(16)));
    int i;
    for (i = 0; i < 3; i++) {
        char *record = D_0022AA10 + i * 0xA0;
        char *position;
        char *owner;
        char *attachment;
        float fraction;
        if (RI(0x8C) != type) continue;
        qcopy(record + 0x20, D_001B2520);
        if (RI(0x94)) {
            RF(0x40) = func_00283B98(RF(0x40), RF(0x4C) * 100.0f);
            RF(0x44) = func_00283B98(RF(0x44), RF(0x50) * 100.0f);
            RF(0x48) = func_00283B98(RF(0x48), RF(0x54) * 100.0f);
            RF(0x64) = func_00283B98(RF(0x64), RF(0x70) * 100.0f);
            RF(0x68) = func_00283B98(RF(0x68), RF(0x74) * 100.0f);
            RF(0x6C) = func_00283B98(RF(0x6C), RF(0x78) * 100.0f);
        } else {
            RF(0x40) = func_00283B98(RF(0x40), RF(0x4C) * 50.0f);
            RF(0x44) = func_00283B98(RF(0x44), RF(0x50) * 50.0f);
            RF(0x48) = func_00283B98(RF(0x48), RF(0x54) * 50.0f);
            RF(0x64) = func_00283B98(RF(0x64), RF(0x70) * 50.0f);
            RF(0x68) = func_00283B98(RF(0x68), RF(0x74) * 50.0f);
            RF(0x6C) = func_00283B98(RF(0x6C), RF(0x78) * 50.0f);
        }
        RF(0x00) = func_00283180(RF(0x40)) * RF(0x58);
        RF(0x04) = func_00283198(RF(0x44)) * RF(0x5C);
        RF(0x08) = -func_00283198(RF(0x48)) * RF(0x60);
        RF(0x10) = func_00283180(RF(0x64)) * RF(0x7C);
        RF(0x14) = func_00283198(RF(0x68)) * RF(0x80);
        RF(0x18) = -func_00283198(RF(0x6C)) * RF(0x84);
        owner = *(char **)(record + 0x90);
        if (owner) {
            attachment = func_002AB1F0(owner);
            if (attachment) {
                func_002B00B0(*(char **)(record + 0x90), offset, 1);
                position = record + 0x30;
                func_00282D30(offset, offset, *(float *)(attachment + 0x10));
                func_00282CC0(position, offset, *(char **)(record + 0x90) + 0x10);
            } else {
                position = record + 0x30;
                qcopy(position, *(char **)(record + 0x90) + 0x10);
            }
            fraction = func_00283CE0(RI(0x94));
            fraction /= func_00283CE0(RI(0x98));
            func_00282D08(position, record + 0x20, position, 1.0f - fraction);
        }
        if (func_00282948(record + 0x94)) {
            if (!RI(0x9C)) RI(0x9C) = 1;
            if (func_00282948(record + 0x88)) RI(0x8C) = 0;
        }
    }
}
