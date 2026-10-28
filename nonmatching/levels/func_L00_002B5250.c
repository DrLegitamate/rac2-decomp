/* Retained reconstruction, USA v1.01.
 * Game -O2 -G0: 568/680 bytes after correcting the timer reset and unconditional upper-path interpolation. Repeated interpolation/reset tails merge more aggressively than retail; keep-block-order ties.
 * No strict linked match.
 */
#include "common.h"

extern unsigned char D_00189E20[];
extern float func_00282C48(float);
extern float func_L00_002D3B00(void *);
extern float func_00282E80(void *, void *);
extern void func_002AA458(void *, void *, void *, float, float, float);
extern void func_002AA3A8(void *, void *, float, float, float, float);

void func_L00_002B5250(void)
{
    unsigned char *hero = D_00189E20;
    float delta;
    if (hero[0x22C3] != 0) {
        if (*(short *)(hero + 0x34E) == 0) {
            if (*(float *)(hero + 0x31C) < 0.0f) {
                delta = func_00282C48(*(float *)(hero + 0x31C));
                if (delta < func_00282C48(func_L00_002D3B00(hero + 0xF0)) + 0.01f) {
                    if (hero[0x287] != 0) {
                        if (func_00282E80(hero + 0x240, hero + 0x80) > *(float *)(hero + 0x264) * 0.5f) {
                            qcopy(hero + 0x80, hero + 0x2D0);
                            return;
                        }
                    }
                }
                func_002AA458(hero + 0x80, hero + 0x2D0, hero + 0x344,
                               0.05f, 0.21f, 0.0833333358168602f);
            } else {
                *(int *)(hero + 0x344) = 0;
            }
        } else {
            *(int *)(hero + 0x344) = 0;
        }
    } else {
        if (*(short *)(hero + 0x34E) == 0) {
            if (*(float *)(hero + 0x88) < *(float *)(hero + 0x318)) {
                delta = func_00282C48(*(float *)(hero + 0x88) - *(float *)(hero + 0x318));
                if (delta < func_00282C48(*(float *)(hero + 0xF8)) + 0.01f) {
                    if (hero[0x287] != 0) {
                        if (func_00282E80(hero + 0x240, hero + 0x80) > *(float *)(hero + 0x264) * 0.5f) {
                            *(float *)(hero + 0x88) = *(float *)(hero + 0x318);
                            return;
                        }
                    }
                    func_002AA3A8(hero + 0x88, hero + 0x344,
                                   *(float *)(hero + 0x318), 0.05f, 0.17f, 0.0833333358168602f);
                } else {
                    if (*(float *)(hero + 0x128) < 0.0f) {
                        *(float *)(hero + 0x88) -= *(float *)(hero + 0x128);
                        if (*(float *)(hero + 0x88) > *(float *)(hero + 0x318))
                            *(float *)(hero + 0x88) = *(float *)(hero + 0x318);
                    }
                    func_002AA3A8(hero + 0x88, hero + 0x344,
                                   *(float *)(hero + 0x318), 0.05f, 0.17f, 0.0833333358168602f);
                }
            } else {
                *(int *)(hero + 0x344) = 0;
            }
        } else {
            *(int *)(hero + 0x344) = 0;
        }
    }
}
