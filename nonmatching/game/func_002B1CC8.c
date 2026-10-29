/* func_002B1CC8 - 612 bytes (153 instructions), 28 places (the boot and all 27
   levels), retail at 0x002B1CC8 in src/game/002B1C20.c (-O2 -G8).

   Measured near miss: 624 bytes (156 instructions), 12 bytes over, so 0 of 28
   places match. The 16-byte copies, the call sequence, the table walk, the
   distance test, the candidate store and the bubble sort follow the retail's
   calls and control flow. Remaining differences:

   1. Register allocation. The retail keeps the owner in $s5, the output in
      $s6 and the constant 22 in $s7. This C puts the output in $s7 and the
      constant in $fp, which costs one extra saved register (`sd/ld $fp`) and
      a copy of the candidate pointer.
   2. The tail of the sort and the loop exit are shaped differently, with a
      few extra register moves.

   Tried, each still 624 bytes: the table read through a pointer that walks
   D_001BF000 (the retail's $s0), the candidate store through a pointer
   ($s2), the table entry reloaded for each use instead of kept in a local,
   and a for loop in place of the retail's loop with the test in the delay
   slot. */

#include "common.h"

typedef struct { float x, y, z, w; } Rac2Vec4;
typedef struct { char reserved_00[0x46]; short kind; } Rac2Desc;
typedef struct {
    char reserved_00[0x10];
    Rac2Vec4 pos;
    char reserved_20[4];
    Rac2Desc *desc;
} Rac2Obj;

extern int D_001BF000[];
extern float func_00283248(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283C80(float, float);
extern float func_00282E20(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277F48(float, void *, int, void *, int);
extern int func_002ABB78(void *);

int func_002B1CC8(Rac2Obj *owner, Rac2Vec4 *out, Rac2Vec4 *in, float scale, float threshold)
{
    Rac2Vec4 local, target;
    float list[16];
    float *lp;
    int *tp;
    float radius, dist, median, length;
    int count, n, i, j;

    qcopy(out, in);
    qcopy(&local, in);
    local.z = 0.0f;
    func_00282F20(&local, &local, scale);
    func_00282CC0(&target, &owner->pos, &local);
    radius = func_00283248(local.x, local.y);
    count = func_00277F48(scale, &target, 0, owner, 0);
    if (count == 0)
        return 0;
    n = 0;
    lp = list;
    tp = D_001BF000;
    for (i = 0; i < count && i < 16; i++, tp++) {
        Rac2Obj *obj;
        if (func_002ABB78((void *)*tp) == 0) {
            Rac2Desc *desc = ((Rac2Obj *)*tp)->desc;
            if (desc == 0 || desc->kind != 22)
                continue;
        }
        obj = (Rac2Obj *)*tp;
        dist = func_00283248(obj->pos.x - owner->pos.x, obj->pos.y - owner->pos.y);
        if (func_00283C80(radius, dist) < threshold) {
            *lp++ = dist;
            n++;
        }
    }
    if (n == 0)
        return 1;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (list[j + 1] < list[j]) {
                float t = list[j];
                list[j] = list[j + 1];
                list[j + 1] = t;
            }
    median = list[n >> 1];
    length = func_00282E20(out);
    out->x = func_00283180(median) * length;
    out->y = func_00283198(median) * length;
    return 1;
}
