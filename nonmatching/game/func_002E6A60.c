/* func_002E6A60 (276 bytes, boot 0x2E6A60, 28 places)
 *
 * First integrated compile, USA v1.01, 28 October 2026: 292 bytes, 0/28
 * placements. The output copy, global-address setup and argument lifetimes
 * inflate the frame to 0x70 against retail's 0x40; helper and FPU register
 * assignments differ, as does the order of the matrix negations and stores.
 * This is a semantic draft, not a near match. Reopen with a source lifetime
 * that reduces the frame and produces retail's helper-call and float order.
 * A fresh explicit-negation/store-order form plus a mode(TI) record copy
 * (2026-10-28) measured 308 bytes, 0/28, worse than the retained 292-byte
 * candidate; it increased rather than reduced frame/code pressure.
 *
 * The body: it takes no argument.  It reads two words out of the table at
 * 0x1B8840 (the word at +0x38 and the word at +0x68), scales the first by 32 and
 * adds it to the second, and so gets a 32-byte record.  It then
 *   - loads the float at +0x1C of the record and calls func_27AB40 with it,
 *     storing the float at 0x1B90F0,
 *   - copies the first 16 bytes of the record to 0x1B5340 (an `lq`/`sq` pair),
 *   - calls func_129178, func_1292C0, func_129368 and func_129218, each with
 *     the frame pointer as both of its first two arguments and a float taken
 *     from the record (+0x10, +0x14, +0x18 of the record and +0x20 of the
 *     record + 0x10),
 *   - negates nine of the twelve floats the calls left in the frame and stores
 *     them at 0x1B5200 + 0x370, +0x374, +0x378, +0x380, +0x384, +0x388, +0x390,
 *     +0x394 and +0x398 - the two gaps are the fourth float of the first two
 *     rows of the 3x4 matrix the calls filled.
 *
 * What has to be reproduced: the nine negations in the retail's order and in the
 * retail's FPU registers (the retail negates f4, f5, f6, f2, f3, f1 and then
 * loads f7, f8 and f0), the order of the nine stores (the retail stores
 * 0x370, 0x398, 0x380, 0x390, 0x374, 0x384, 0x394, 0x378, 0x388 - not the
 * address order), the `lq`/`sq` copy and the five calls with their float
 * arguments.
 *
 * What would unblock it: the float expression tree that keeps the retail's
 * FPU registers (the same problem as the level 20 wave's float families), and
 * the `lq`/`sq` copy, whose destination is a symbol (0x1B5340) and whose source
 * is a computed address.
 */
typedef float f32;
typedef unsigned char u8;

extern int ref_L00_001B8840_00[];      /* the table at 0x1B8840 */
extern f32 ref_L00_001B90F0_00;         /* the float at 0x1B90F0 */
extern int ref_L00_001B5340_00[];       /* the copy's destination at 0x1B5340 */
extern f32 ref_L00_001B5200_00[];        /* the nine floats at 0x1B5200 + 0x370 */

extern void func_27AB40(f32);
extern void func_129178(void *, void *);
extern void func_1292C0(void *, void *, f32);
extern void func_129368(void *, void *, f32);
extern void func_129218(void *, void *, f32);

void func_002E6A60(void)
{
    int *table = ref_L00_001B8840_00;
    u8 *rec;
    f32 m[12];
    int i;

    rec = (u8 *)table[0x68] + (table[0x38] << 5);
    func_27AB40(*(f32 *)(rec + 0x1C));
    ref_L00_001B90F0_00 = *(f32 *)(rec + 0x1C);
    for (i = 0; i < 4; i++)
        ref_L00_001B5340_00[i] = *(int *)(rec + 4 * i);
    func_129178(&m[0], &m[0]);
    func_1292C0(&m[0], &m[0], *(f32 *)(rec + 0x10));
    func_129368(&m[0], &m[0], *(f32 *)(rec + 0x14));
    func_129218(&m[0], &m[0], *(f32 *)(rec + 0x18));
    for (i = 0; i < 12; i++)
        m[i] = -m[i];
    ref_L00_001B5200_00[0xDC] = m[8];   /* +0x370 */
    ref_L00_001B5200_00[0xDD] = m[9];   /* +0x374 */
    ref_L00_001B5200_00[0xDE] = m[10];  /* +0x378 */
    ref_L00_001B5200_00[0xE0] = m[0];   /* +0x380 */
    ref_L00_001B5200_00[0xE1] = m[1];   /* +0x384 */
    ref_L00_001B5200_00[0xE2] = m[2];   /* +0x388 */
    ref_L00_001B5200_00[0xE4] = m[4];   /* +0x390 */
    ref_L00_001B5200_00[0xE5] = m[5];   /* +0x394 */
    ref_L00_001B5200_00[0xE6] = m[6];   /* +0x398 */
}
