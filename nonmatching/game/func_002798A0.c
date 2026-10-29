/* Publication review uses the catalogue data name D_001B7F80; historical
 * measurements below precede that naming correction. This draft is not linked.
 * Current-master USA v1.01 standalone replay on 29 October 2026: 224/228 bytes,
 * 0/28 placements. The diff starts with the table-base/register assignment and
 * later reaches the known same-group branch-direction mismatch. A 29 October
 * explicit early return when adjacent records have different keys emitted the
 * same 224 bytes and `beq` to the same-group path; retail branches the other
 * way around that path. */
typedef struct {
    char pad000[0x20];
    unsigned short idx;
    unsigned short idx2;
} OozlaIndex_001B7F80;

typedef struct {
    int key;
    int start;
    int end;
    char pad00C[0x10];
    int ptr;
    char pad020[8];
} OozlaEntry_001B8308;

typedef struct {
    OozlaEntry_001B8308 e[32];
    int count;
} OozlaTable_001B8308;

extern char D_001B7F80[];
extern OozlaTable_001B8308 D_001B8308;

int func_002798A0(int value, int *out_index, int *out_offset)
{
    char *table;
    char *start_bytes;
    char *end_bytes;
    int index;
    int next_index;

    *out_index = (short)((OozlaIndex_001B7F80 *)D_001B7F80)->idx;
    *out_offset = (short)((OozlaIndex_001B7F80 *)D_001B7F80)->idx2 + value;

    index = *out_index;
    if (index < 0)
        return 0;
    if (index >= D_001B8308.count)
        return 0;

    table = (char *)(void *)&D_001B8308;
    start_bytes = table + 4;
    end_bytes = table + 8;

    for (;;) {
        int row = index * 0x28;
        int start = *(int *)(start_bytes + row);
        int end = *(int *)(end_bytes + row);
        int offset = *out_offset;
        int next_offset;

        if (end >= start + offset)
            return 1;

        next_index = index + 1;
        if (next_index >= *(int *)(table + 0x500))
            return 0;
        if (*(int *)(table + row) == *(int *)(table + next_index * 0x28))
            goto same_group;
        return 0;

    same_group:
        next_offset = offset - 1;
        next_offset -= end - start;
        *out_offset = next_offset;
        next_index = *out_index + 1;
        *out_index = next_index;
        if (next_index < 0)
            return 0;
        index = next_index;
        if (index < *(int *)(table + 0x500))
            continue;
        return 0;
    }
}
