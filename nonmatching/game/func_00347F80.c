/* Current-master USA v1.01 replay: 220 bytes versus 224, 0/28 placements.
 * Earlier 224-byte variants also missed, first at +0x4C. A 29 October
 * conditional-expression form of the negative-index clamp emitted the same
 * 220 bytes and the same `movn` sequence; it did not reach retail's `movz`.
 * Making `direction == 0` an explicit early return also emits the same 220
 * bytes and leaves the return-zero instruction in the call setup delay path;
 * it does not reproduce retail's `beqz` delay-slot zero return. */
extern int func_002E5E58(int, int, void *);

int func_00347F80(char *object, int flags)
{
    int direction = 0;
    int index;
    int last;
    int original;
    void **entries;

    if (flags & 0x1000) {
        direction = -1;
    } else if (flags & 0x4000) {
        direction = 1;
    } else if (flags & 0x40) {
        if (*(void **)(object + 0x5C + *(int *)(object + 0x50) * 4) != 0)
            return 1;
    }
    if (direction != 0) {
        original = *(int *)(object + 0x50);
        func_002E5E58(3, 0, 0);
        last = *(int *)(object + 0xB0) - 1;
        entries = (void **)(object + 0x5C);
        index = *(int *)(object + 0x50);
        do {
            index += direction;
            if (last < index)
                index = 0;
            if (index < 0)
                index = last;
            *(int *)(object + 0x50) = index;
        } while (entries[index] == 0 && index != original);
    }
    return 0;
}
