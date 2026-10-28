/* Near miss, not linked. Game -O2 -G8 -ffunction-sections -g -malign-loops=2.
 * 756/756 bytes; local USA v1.01 check: 0/28 placements.
 * Recovered angular-range selection, keyboard selection and repeat timer.
 * The measured mode field retains one read and the branch-specific stores.
 * Remaining: first-table pointer lifetime and keyboard-mode store scheduling.
 * Eight trials: field access views and separate table lifetimes changed the
 * residual; four-byte loop alignment removed a measured padding difference.
 * Reopen with a truthful table/owner lifetime model, not forced registers.
 */
#include "common.h"

typedef struct {
    u8 prefix[0x150];
    volatile int mode;
} SelectionInputView;

extern char D_00138180[];
extern float D_001AE5F4 SDATA(D_001AE5F4);
extern float func_00282C10(float);
extern float func_00283248(float, float);

int func_00349190(char *object)
{
    float x, y, magnitude, angle;
    char *pad;
    float (*ranges)[2];
    int oldSelection, i;
    unsigned int buttons;

    if (--*(int *)(object + 0x154) < 0)
        *(int *)(object + 0x154) = 0;
    if (*(int *)(object + 0x154) == 0) {
        pad = D_00138180;
        x = *(float *)(pad + 0x148);
        y = *(float *)(pad + 0x14C);
        magnitude = func_00282C10(x*x + y*y);
        if (magnitude != 0.0f) {
            x /= magnitude;
            y /= magnitude;
        }
        angle = func_00283248(x, y);
        i = 0;
        if (((SelectionInputView *)object)->mode == 0)
            *(int *)(object + 0x14C) = -1;
        oldSelection = *(int *)(object + 0x14C);
        if (magnitude > D_001AE5F4) {
            ranges = *(float (**)[2])(object + 0x144);
            while (ranges[i][0] != 0.0f || ranges[i][1] != 0.0f) {
                if ((ranges[i][0] < 0.0f) != (ranges[i][1] >= 0.0f)) {
                    if (ranges[i][0] <= angle && angle < ranges[i][1]) {
                        *(int *)(object + 0x14C) = i;
                        ((SelectionInputView *)object)->mode = 1;
                        break;
                    }
                } else if (ranges[i][1] < 0.0f) {
                    if ((ranges[i][0] <= angle && angle <= 3.15916f) ||
                        (-3.15916f <= angle && angle < ranges[i][1])) {
                        *(int *)(object + 0x14C) = i;
                        ((SelectionInputView *)object)->mode = 1;
                        break;
                    }
                } else {
                    if ((ranges[i][0] <= angle && angle < 0.0f) ||
                        (0.0f <= angle && angle < ranges[i][1])) {
                        *(int *)(object + 0x14C) = i;
                        ((SelectionInputView *)object)->mode = 1;
                        break;
                    }
                }
                ++i;
            }
        } else {
            buttons = *(unsigned int *)(pad + 0x1C0);
            if (buttons & 0x1000) {
                *(int *)(object + 0x14C) = 3;
                ((SelectionInputView *)object)->mode = 1;
            } else if (buttons & 0x4000) {
                ((SelectionInputView *)object)->mode = 1;
                *(int *)(object + 0x14C) = 1;
            } else if (buttons & 0x8000) {
                *(int *)(object + 0x14C) = 2;
                ((SelectionInputView *)object)->mode = 1;
            } else if (buttons & 0x2000) {
                *(int *)(object + 0x14C) = 0;
                ((SelectionInputView *)object)->mode = 1;
            }
        }
        if (oldSelection != *(int *)(object + 0x14C))
            *(int *)(object + 0x154) = 10;
    }
    return *(int *)(object + 0x14C);
}
