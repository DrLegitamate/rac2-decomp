/* Current-master USA v1.01 recheck: 152/160 bytes, 0/28. Reordering the
 * `count` and `total` declarations leaves the output unchanged. The remaining
 * mismatch includes total/count and input-pointer allocation, loop setup and
 * result-pointer reconstruction. */

typedef int s32;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 pad0[0x10];
    float *result;
    u32 threshold;
    u8 pad1[0xC];
    short rows;
    short columns;
    u8 pad2[0x8];
} Func00280670Record;

extern Func00280670Record ref_L00_00280670_00[];

void func_00280670(u8 *values, int index)
{
    Func00280670Record *record = &ref_L00_00280670_00[index];
    s32 total = record->rows * record->columns;
    s32 count = 0;

    if (total > 0) {
        u32 threshold = record->threshold;
        s32 remaining = total;
        do {
            count += ((*(u32 *)values & 0x00FFFFFF) > threshold);
            values += 4;
        } while (--remaining != 0);
    }

    *ref_L00_00280670_00[index].result = (float)(total - count) / (float)total;
}
