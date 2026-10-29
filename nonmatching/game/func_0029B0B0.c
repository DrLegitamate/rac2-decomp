/* Near miss: func_0029B0B0 (184 bytes in every program), FillSaveSlotInfo.
 *
 * The function fills one entry of the save-slot table with fields read out of
 * a save header.  What the retail bytes say:
 *
 *  - the table is at 0x0013F3E0, the stride of a slot is 0xA0 and the stride
 *    of a directory inside a slot is 0x1C (the slot entry is
 *    0x0013F3E0 + slot * 0xA0 + dir * 0x1C);
 *  - the header passed in a0 is read at +0x10 (int), +0x1C (int), +0x2E
 *    (byte), +0x64 (int) and +0x70 (8 bytes);
 *  - the entry receives them at +0x30, +0x34, +0x38, +0x3C and +0x40, and
 *    the flag "func_0029AF58(a0) == 0" at +0x48;
 *  - the 16 bytes are copied with one R5900 unaligned 16-byte idiom
 *    (ldl/ldr + sdl/sdr).
 *
 * The original 16-byte Quad candidate was wrong: retail copies only eight
 * bytes at +0x70 into the slot's +0x40 field. The retained candidate below
 * uses a packed eight-byte object, which compiles to the same four-instruction
 * `ldl`/`ldr`/`sdl`/`sdr` copy sequence as retail. On 28 October 2026, a current
 * USA v1.01 checker probe measured 148 bytes versus 184 and 0/28 placements.
 * The remaining differences include the function's frame/register allocation,
 * table base materialization, and the setup and order of its field stores. The
 * previous 192-byte measurement and claim that the unaligned copy was
 * unreachable described the superseded 16-byte candidate and are withdrawn.
 * The current caller passes the header as `char *`; keeping that actual pointer
 * type instead of an `int` plus cast leaves the candidate at 148 bytes and
 * 0/28, while changing argument/register allocation.
 * A 29 October dedicated-unit variant that explicitly advances the header
 * pointer to `src + 0x10` before reading the fields compiles to 152 bytes,
 * 0/28. It changes the table/index register assignments and source pointer
 * placement, but still lacks retail's saved-register layout, retained output
 * field pointers, and 32 bytes of code.
 */
extern char D_0013F3E0[];

extern int func_0029AF58(char *p);

typedef struct __attribute__((packed)) { unsigned long long value; } Word64;

void func_0029B0B0(char *src, int a1, int a2)
{
    int flag = func_0029AF58(src);
    char *rec = (char *)D_0013F3E0 + a1 * 0xA0 + a2 * 0x1C;
    int *f1 = (int *)(rec + 0x30);
    int *f2 = (int *)(rec + 0x34);
    int *f3 = (int *)(rec + 0x38);
    int *f4 = (int *)(rec + 0x3C);

    *(int *)(rec + 0x48) = flag == 0;
    *f1 = *(int *)(src + 0x10);
    *f2 = *(int *)(src + 0x1C);
    *f3 = *(unsigned char *)(src + 0x2E);
    *f4 = *(int *)(src + 0x64);
    *(Word64 *)(rec + 0x40) = *(Word64 *)(src + 0x70);
}
