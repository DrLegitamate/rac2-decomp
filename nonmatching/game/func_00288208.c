/* func_00288208 (near miss, boot 0x00288208, 252 bytes, 28 places).
 *
 * Traced from the retail bytes: this is one of the four 0xE0-byte class-record
 * updaters in game/002880E0.c (the record table is D_00239BA0 in the boot and
 * each level's own copy at other addresses, so every D_ name here is a plain
 * address and the placement reads its value per program).
 *
 * Retail shape:
 *   - func_00288188(a0) gates the whole body; both early exits share the
 *     epilogue, so it returns void;
 *   - a five-halfword pending row (stride 10 bytes, the compared value at +6,
 *     terminator -1) is scanned from 0x25E32E; a match returns at once;
 *   - then the record's word at +0xC and func_002880E0 decide;
 *   - finally a0 is put into the first empty or equal slot of the eight-word
 *     array at 0x1A73B8.
 *
 * Measured: -O2 -G0 -ffunction-sections, 248 bytes against retail's 252 and
 * 0 of 28 places.  The pending scan and both early exits match; only the
 * eight-slot append loop at the end differs, where retail's two-way
 * beql/bnel if-conversion (comparing $v0 with the id while the delay slot
 * loads the next `slti`) is not reproduced by the plain break loop below.
 * Rechecked 28 Oct 2026: the index form remains 248 bytes (0/28). A pointer
 * loop and a nested zero-then-id condition both compile to 244 bytes (0/28),
 * so those source shapes do not reproduce retail's counted if-conversion. A
 * direct-return append form is 208/252 bytes, 0/28.
 */

typedef int s32;

typedef unsigned char u8;

typedef struct {
    int word00;
    unsigned char byte04;
    unsigned char pad05[7];
    int word0C;
    unsigned char pad10[0x70];
    int word80;
    unsigned char pad84[4];
    unsigned short half88;
    unsigned char pad8A[8];
    unsigned short half92;
    unsigned char pad94[0x4C];
} ClassRecord;

/* a pending table row: five halfwords, the value compared at +6 */
typedef struct {
    short id;
    short pad0;
    short pad1;
    short value;
    short pad2;
} PendingEntry;

extern ClassRecord D_00239BA0[];

extern unsigned char D_00139568[];

extern unsigned char D_001A7AF8[];

extern int D_00139688[];

extern int D_001A73B8[];

extern PendingEntry D_0025E328[];

extern int func_00288188(int);

extern int func_002880E0(int);

void func_00288208(int a0)
{
    ClassRecord *record;
    short *p;
    int i;

    if (func_00288188(a0) == 0)
        return;
    p = &D_0025E328[0].value;
    if (*p != -1) {
        do {
            if (*p == a0)
                return;
            p += 5;
        } while (*p != -1);
    }
    record = &D_00239BA0[D_00139568[a0]];
    if (record->word0C != 0)
        return;
    if (func_002880E0(a0) != 0)
        return;
    for (i = 0; i < 8; i++) {
        if (D_001A73B8[i] == 0 || D_001A73B8[i] == a0)
            break;
    }
    if (i < 8)
        D_001A73B8[i] = a0;
}
