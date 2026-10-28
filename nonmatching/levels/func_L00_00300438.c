/* Retained reconstruction, USA v1.01.
 * 444/468 bytes with game -O2 -G0. The float-to-double helper now has its actual double return and the formatter remains variadic. Scalar pair swaps restore the 0x1030 frame; the prior aggregate swap needed an extra 16 stack bytes. Remaining differences are loop copies, induction and allocation; the truthful prototype alone does not match.
 * No strict linked match.
 */
#include "common.h"

typedef struct {
    float a;
    float b;
} F300438Pair;

extern char D_001A95A0[];
extern int func_00283CF0(float);
extern double func_001234F0(float);
extern void func_0026FEB8(const char *, ...);

void func_L00_00300438(int *entries, int count, int limit) {
    F300438Pair s[512];
    int n = 0;
    int i, j, sorted;
    float fl;
    int remaining;

    if (count > 0) {
        do {
            if (entries[0] != 0) {
                s[n].a = (float)entries[1];
                s[n].b = (float)entries[0];
                n++;
            }
            entries += 8;
        } while (--count != 0);
    }
    count = n - 1;
    fl = (float)limit;
    for (i = 0; i < count; i++)
        s[i].b = (s[i + 1].b - s[i].b) * (1.0f / 1024.0f);
    s[count].b = (fl - s[count].b) * (1.0f / 1024.0f);
    do {
        sorted = 1;
        for (j = 0; j < count; j++) {
            if (s[j].b < s[j + 1].b) {
                float a = s[j].a;
                float b = s[j].b;
                s[j].a = s[j + 1].a;
                s[j].b = s[j + 1].b;
                s[j + 1].a = a;
                s[j + 1].b = b;
                sorted = 0;
            }
        }
    } while (!sorted);
    for (remaining = 0; remaining < n; remaining++)
        func_0026FEB8(D_001A95A0, func_00283CF0(s[remaining].a), func_001234F0(s[remaining].b));
}
