/* Retained reconstruction, USA v1.01, game -O2 -G8.
 * The indexed form is 640/640 bytes; the tail from +0x120 is exact, but
 * the first loop uses index arithmetic instead of retail's pointer induction.
 * Direct pointer induction produces 648 bytes, hoisting the pointer before the
 * guard and duplicating the state constant; explicit do/while also hoists the
 * object-position pointer and adds a callee-save. No fabricated ABI or accesses.
 * Next: diagnose the loop strength-reduction/allocation decision from dumps.
 */
#include "common.h"

extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_002AF000(float *, float, float, float);
extern void func_00282CC0(float *, float *, float *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00283248(float, float);
extern float func_00282E80(float *, float *);
extern float func_00282E48(float *, float *);
extern float func_00283BE0(float, float);
extern void func_L00_002E6EF8(void (*)(void), void *);
extern void func_L11_00456EA0(void);

void func_L11_00456C20(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float difference[4];
    float *point;
    float radius, heading, pitch, random_heading;
    int i, j;

    if (object[0x20] == 0) {
        if (*(int *)(state + 0x80) > 8)
            *(int *)(state + 0x80) = 8;
        object[0x20] = 1;
        for (i = 0; i < *(int *)(state + 0x80); i++) {
            float initial_radius, initial_heading;
            point = (float *)(state + i * 16);
            initial_radius = func_002A7878(*(float *)(state + 0x84), *(float *)(state + 0x88));
            initial_heading = func_002A7940();
            func_002AF000(point, initial_radius, initial_heading, func_002A7940());
            func_00282CC0(point, (float *)(object + 0x10), point);
        }
    }
    if (object[0x20] == 1) {
        func_L00_002E6EF8(func_L11_00456EA0, object);
        for (j = 0; j < *(int *)(state + 0x80); j++) {
            point = (float *)(state + j * 16);
            func_00282CF0(difference, (float *)(object + 0x10), point);
            heading = func_00283248(point[0] - *(float *)(object + 0x10),
                                   point[1] - *(float *)(object + 0x14));
            radius = func_00282E80((float *)(object + 0x10), point);
            pitch = func_00283248(radius, point[2] - *(float *)(object + 0x18));
            heading = func_00283BE0(heading, *(float *)(state + 0x9C) * 0.01745329424738884f);
            random_heading = func_002A78D8(*(float *)(state + 0xA4), *(float *)(state + 0xA0));
            pitch = func_00283BE0(pitch, random_heading * 0.01745329424738884f);
            if (pitch > *(float *)(state + 0x8C))
                pitch = *(float *)(state + 0x8C);
            if (pitch < *(float *)(state + 0x90))
                pitch = *(float *)(state + 0x90);
            radius = func_00282E48((float *)(object + 0x10), point);
            radius += func_002A78D8(*(float *)(state + 0x98) * 0.01666666753590107f,
                                  *(float *)(state + 0x94) * 0.01666666753590107f);
            if (radius > *(float *)(state + 0x88))
                radius = *(float *)(state + 0x88);
            if (radius < *(float *)(state + 0x84))
                radius = *(float *)(state + 0x84);
            func_002AF000(point, radius, heading, pitch);
            func_00282CC0(point, (float *)(object + 0x10), point);
        }
    }
}
