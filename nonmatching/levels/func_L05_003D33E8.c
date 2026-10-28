/* Retained reconstruction, USA v1.01, game -O2 -G8.
 * Typed history/rate arrays reproduce the complete inner 137-vector loop.
 * 844/832 bytes remain: prologue order, history-position address association,
 * component-address materialization and final scalar-array scheduling differ.
 * Explicit component pointers produce 816 bytes by hoisting another base.
 * No strict linked match.
 */
#include "common.h"

extern float func_002A7878(float, float);
extern void func_00282C88(void *);
extern int func_001163B0(void);
extern float D_L05_0023F920[][4][137][4];
extern float D_L05_0024A460[][4][137];
typedef struct { float x, y, z, w; } Position;
extern Position D_L05_0024D020[][4];
extern int D_L05_0024CFD0[][4];
extern int D_L05_0024CF30[][4];
extern int D_L05_0024CF80[][4];
extern float D_L05_001B2F58[];
extern int D_L05_001B2F70[];
extern float D_L05_001B2F88[];
extern int D_L05_001B2FE8[];
extern int D_L05_001B2FA0[];
extern float D_L05_001B2FB8[];
extern float D_L05_001B2FD0[];

void func_L05_003D33E8(unsigned char *object)
{
    int *index = *(int **)(object + 0x68);
    int i, j;
    float speed;
    unsigned char *base;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 137; j++) {
            speed = func_002A7878(0.5f, 4.0f);
            func_00282C88(D_L05_0023F920[*index][i][j]);
            D_L05_0024A460[*index][i][j] = speed;
        }
        base = (unsigned char *)&D_L05_0024D020[*index][i];
        /* This history slot and the actor position do not contain the private index. */
        qcopy_nc(base, object + 0x10);
        D_L05_0024CFD0[*index][i] = 6;
        D_L05_0024CF30[*index][i] = func_001163B0() % 128 + 128;
        D_L05_0024CF80[*index][i] = func_001163B0() % 2 + 6;
        speed = func_002A7878(0.0f, 0.5f);
        D_L05_0024D020[*index][i].x += speed + -0.25f;
        speed = func_002A7878(0.0f, 0.5f);
        D_L05_0024D020[*index][i].y += speed + -0.25f;
        speed = func_002A7878(0.0f, 0.5f);
        D_L05_0024D020[*index][i].z += speed + -0.25f;
    }
    D_L05_001B2F58[*index] = 0.01f;
    D_L05_001B2F70[*index] = 128;
    D_L05_001B2F88[*index] = 0.1f;
    D_L05_001B2FE8[*index] = 6;
    D_L05_001B2FA0[*index] = 128;
    D_L05_001B2FB8[*index] = 0.0f;
    D_L05_001B2FD0[*index] = 0.0f;
}
