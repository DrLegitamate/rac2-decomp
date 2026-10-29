/* func_003202E8 - 612 bytes, 28 places (the boot and all 27 levels). Near miss: 620 of 612 bytes in the
 * boot place, two instructions long (no place matches). Compiled in src/game/0031F210.c (-G0). Remaining
 * differences, against retail:
 *   - the frame and the save/restore set match, and the vector zero/copy use qzero/qcopy as retail does (sq v0 vs sq $0 aside, the zero store uses $0 here).
 *   - D_001A8CA0 is read twice: retail reloads lui/lw at each test; here the second read reuses a hoisted address in $fp.
 *   - the table bases D_00139568 and D_00239BA0 are hoisted to $s6/$s7 as in retail (declared as locals here).
 *   - the 0xE0 * kind multiply and the D_001A7A0A test are emitted in another order; the first call
 *     (func_0026F7A0 with the id) is discarded at the top, as retail does.
 *   - the callback pointer is a reference to func_0031FC28 (retail stores the literal 0x31FC60; the
 *     catalogue puts the function at 0x31FC60, so that symbol name needs checking).
 *   - pos/id/arg2/arg3 land in s3/s2/s1/s4 here, retail s3/s2/s4/s5: the argument order drives the allocation.
 * func_0026F7A0 is declared without a parameter list because retail passes it an argument it ignores.
 */
#include "include_asm.h"
#include "common.h"

extern unsigned int func_0026F7A0();
extern void func_0031FC28(void);
extern void func_002AFFD8(void *, void *, int);
extern float func_00282E20(void *);
extern void func_002A7A00(void *, float, float);
extern float func_002A7878(float, float);
extern void func_002AFEB8(void *, void *, void *, int, float);
extern void *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern float func_002B0360(void *);
extern void func_002A0F48(void *);
extern void func_002AB650(void *);
extern char D_00189E20[];
extern unsigned char D_00139568[];
extern char D_00239BA0[];
extern unsigned char D_001A7A0A;
extern int D_001A8CA0;

char *func_003202E8(float *pos, int id, int arg2, int arg3)
{
    float a[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    unsigned char *map = D_00139568;
    char *slots = D_00239BA0;
    char *p;
    char *data;
    float size;
    float life;

    func_0026F7A0(id);
    qzero(vec);
    vec[2] = func_002A7940();
    qcopy(a, vec);
    if (D_001A8CA0) {
        func_002AFFD8(pos, vec, 1);
        a[1] = func_00283248(vec[2], func_00282E20(vec));
        a[2] = func_00283248(vec[0], vec[1]);
    }
    func_002A7A00(vec, 1.0f / 30.0f, 1.0f / 15.0f);
    func_002AFEB8(*(void **)(D_00189E20 + 0x2290), vec, vec, 0,
                  func_002A7878(4.0f, 8.0f) * (1.0f / 60.0f));
    size = func_002A7878(180.0f, 360.0f);
    life = func_002A7878(10.0f, 15.0f);
    p = func_00273730(*(void **)(D_00189E20 + 0x2290), 2, 0xCDB, 0, pos, a, vec, 0xFF, size, life);
    if (p) {
        p[0x20] = 1;
        *(void **)(p + 0x64) = (void *)func_0031FC28;
        data = *(char **)(p + 0x68);
        if (arg2 == -1) {
            unsigned int idx = func_0026F7A0(id);
            unsigned char kind = map[idx];
            *(int *)(data + 0x60) = *(unsigned short *)(slots + 0xE0 * kind + 0x8C);
        } else {
            *(int *)(data + 0x60) = arg2;
        }
        if (D_001A7A0A)
            *(int *)(data + 0x60) <<= 1;
        *(int *)(data + 0x68) = id;
        *(float *)(data + 0x6C) = (float)arg3;
        *(int *)(data + 0x70) = 16;
        if (D_001A8CA0)
            *(float *)(data + 0x78) = func_002B0360(p + 0x10);
        else
            *(float *)(data + 0x78) = *(float *)(p + 0x18);
        func_002A0F48(p);
        func_002AB650(p);
    }
    return p;
}
