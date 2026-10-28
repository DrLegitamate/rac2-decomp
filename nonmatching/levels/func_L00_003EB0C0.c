/* Game -O2 -G0: 752/760 bytes, 0/11 USA places.
 * The local transform is a 3x4 matrix (48 bytes), not 4x4. The sentinel
 * comparison lets this compiler reuse -1 for the FF byte store, one word
 * shorter; the list loop has a different saved-register/constant schedule.
 * Explicit terminal capture restores the loop load/branch/increment shape.
 * no-cse-follow-jumps does not repair the constant reuse.
 * Next: compare the record identity type and the original list-loop scope.
 */
#include "common.h"
extern void func_L00_00323448(void *, void *, int, int, int, int, int, int);
extern void func_0029F338(void *), func_002833F0(void *, void *);
extern float func_00283198(float);
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_002AEF28(void *, void *, void *, float, float, float);
extern void func_00283738(void *, void *, void *), func_002AB6D8(void *, void *);
extern void func_L00_00323958(void *, void *);
extern int D_L00_001C9340;
#define F(offset) (*(float *)(state + (offset)))
#define I(offset) (*(int *)(state + (offset)))

void func_L00_003EB0C0(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float rotation[4], matrix[3][4];
    char *entry, *entries;
    unsigned char terminal;
    switch (object[0x20]) {
    case 0:
        if (*(long long *)state == -1) break;
        object[0x30] = 255;
        func_L00_00323448(object, state + 0x40, 0x50, I(4), I(0), I(8), 7, 0);
        if (!(unsigned char)state[0x8a]) { func_0029F338(object); break; }
        if (I(0x1c) == 0) {
            state[0x8d] = 1;
            *(unsigned short *)(object + 0x34) |= 0x104;
            func_002833F0(object + 0xc0, object + 0xf0);
        }
        if (F(0x20) != 0.0f) F(0x20) *= 0.01745329424738884f;
        F(0x24) = func_00283198(F(0x20)) * F(0x30);
        object[0x20] = 1;
        break;
    case 1:
        if (D_L00_001C9340 != I(0xc)) break;
        if (F(0x34) > 0.0f) func_002AEE70(object, state + 0x20, state + 0x24, F(0x30), F(0x34) * 0.0002908882452175021f, -1.0f);
        if (F(0x3c) > 0.0f) func_002AEF28(object, state + 0x28, state + 0x2c,
                                         F(0x38) * 0.01745329424738884f, F(0x3c) * 0.0002908882452175021f, 0.00581776537001133f);
        if ((unsigned char)state[0x8d]) func_002833F0(object + 0xc0, object + 0xf0);
        entries = (char *)state + 0x40;
        if (I(0x1c) == 0) {
            rotation[0] = F(0x10) * 0.0002908882452175021f;
            rotation[1] = F(0x14) * 0.0002908882452175021f;
            rotation[2] = F(0x18) * 0.0002908882452175021f;
            func_002833F0(matrix, rotation);
            func_00283738(object + 0xc0, object + 0xc0, matrix);
            if (F(0x3c) > 0.0f) func_002AB6D8(object + 0xc0, object + 0xf0);
        } else {
            entry = entries;
            do {
                rotation[0] = F(0x10) * 0.0002908882452175021f;
                rotation[1] = F(0x14) * 0.0002908882452175021f;
                rotation[2] = F(0x18) * 0.0002908882452175021f;
                func_002833F0(matrix, rotation);
                func_00283738(entry, entry, matrix);
                terminal = (unsigned char)entry[0x4a];
                entry += 0x50;
            } while (terminal != 1);
        }
        func_L00_00323958(object, entries);
        break;
    }
}
#undef F
#undef I
