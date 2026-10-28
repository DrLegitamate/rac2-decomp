/* Retained reconstruction, USA v1.01.
 * Game -O2 -G0: 852/832 bytes. The four 137-vector histories and their random rates are reconstructed, but loop induction, source/index GPRs and quadword-copy dependencies differ. Next useful experiment: represent the measured multidimensional arrays and qualify non-clobbering copy dependencies.
 * No strict linked match.
 */
#include "common.h"

extern float func_002A7878(float, float);
extern void func_00282C88(void *);
extern int func_001163B0(void);
extern unsigned char D_L05_0023F920[];
extern unsigned char D_L05_0024A460[];
extern unsigned char D_L05_0024D020[];
extern unsigned char D_L05_0024CFD0[];
extern unsigned char D_L05_0024CF30[];
extern unsigned char D_L05_0024CF80[];
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
            func_00282C88(D_L05_0023F920 + *index * 0x2240 + i * 0x890 + j * 16);
            *(float *)(D_L05_0024A460 + *index * 0x890 + i * 0x224 + j * 4) = speed;
        }
        base = D_L05_0024D020 + *index * 64 + i * 16;
        qcopy(base, object + 0x10);
        *(int *)(D_L05_0024CFD0 + *index * 16 + i * 4) = 6;
        *(int *)(D_L05_0024CF30 + *index * 16 + i * 4) = func_001163B0() % 128 + 128;
        *(int *)(D_L05_0024CF80 + *index * 16 + i * 4) = func_001163B0() % 2 + 6;
        speed = func_002A7878(0.0f, 0.5f);
        *(float *)(D_L05_0024D020 + *index * 64 + i * 16) += speed - 0.25f;
        speed = func_002A7878(0.0f, 0.5f);
        *(float *)(D_L05_0024D020 + *index * 64 + i * 16 + 4) += speed - 0.25f;
        speed = func_002A7878(0.0f, 0.5f);
        *(float *)(D_L05_0024D020 + *index * 64 + i * 16 + 8) += speed - 0.25f;
    }
    D_L05_001B2F58[*index] = 0.01f;
    D_L05_001B2F70[*index] = 128;
    D_L05_001B2F88[*index] = 0.1f;
    D_L05_001B2FE8[*index] = 6;
    D_L05_001B2FA0[*index] = 128;
    D_L05_001B2FB8[*index] = 0.0f;
    D_L05_001B2FD0[*index] = 0.0f;
}
