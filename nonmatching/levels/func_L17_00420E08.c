/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 profile: default game profile.
 * Last compiled version: 712/712 bytes. The retained hero predicate was then corrected from retail and was not recompiled. State switch and dynamic table traversal reconstructed; global-load and scalar-store order plus loop-counter allocation differ. A mixed GP/absolute -mno-split-addresses trial hit an assembler assertion; default source remains unqualified.
 * US object comparison only in this retry; no linked strict-build claim.
 * Reopen with a measured allocation, scheduling or source-interface witness.
 */
#include "common.h"
extern float func_002A7940(void);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, void *);
extern int D_001A79F0 MACRO_ADDR;
extern int smolgLevel SDATA(D_001A79F0);
extern unsigned char D_0019B2E8[];
struct SmolgHero { char pad[0x33c]; void *target; char gap[0xe]; short active; };
extern struct SmolgHero D_00189E20;
extern unsigned char *D_L17_001FE880[];
void func_L17_00420E08(unsigned char *m)
{
    unsigned char *p = *(unsigned char **)(m + 0x68);
    int color, i;
    switch (m[0x20]) {
    case 0:
        *(float *)(p + 0xc) = func_002A7940();
        *(float *)(m + 0x18) -= 0.35f;
        if (D_0019B2E8[m[0xb0] + D_001A79F0 * 16] & 0x80) {
            m[0x20] = 2;
            *(int *)(m + 0x78) = 0x80208020;
            m[0xbc] = 2;
            if (*(int *)p != -1) {
                for (i = 0; i < *(int *)D_L17_001FE880[*(int *)p]; i++) {
                    float *entry = (float *)(D_L17_001FE880[*(int *)p] + i * 16 + 0x1c);
                    if (*entry == *(float *)(p + 4)) *entry = 0.0f;
                }
            }
        } else m[0x20] = 1;
        break;
    case 1:
        *(float *)(p + 0xc) = func_00283B98(*(float *)(p + 0xc), 0.10471977f);
        color = func_00283CF0((func_00283198(*(float *)(p + 0xc)) * 4.0f - 3.0f) * 128.0f);
        if (color > 128) color = 128;
        else if (color < 32) color = 32;
        *(int *)(m + 0x78) = ((color << 16) | ((color << 8) | 0x80000000)) | color;
        if (D_00189E20.target == m) {
            if (!D_00189E20.active) goto activate;
        }
        if (*(int *)(p + 8)) {
activate:
            if (D_0019B2E8[m[0xb0] + smolgLevel * 16] & 0x80) {
                m[0xbc] = 1;
                m[0x20] = 2;
                *(int *)(m + 0x78) = 0x80208020;
                func_002E5CF8(0, 0, m);
                if (*(int *)p != -1) {
                    for (i = 0; i < *(int *)D_L17_001FE880[*(int *)p]; i++) {
                        float *entry = (float *)(D_L17_001FE880[*(int *)p] + i * 16 + 0x1c);
                        if (*entry == *(float *)(p + 4)) *entry = 0.0f;
                    }
                }
            }
        }
        break;
    }
}
