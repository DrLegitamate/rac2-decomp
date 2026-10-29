/* Near miss for func_00328A20 (boot 0x00328A20, 324 bytes, 28 places: boot and 27
 * levels).  Current-master in-unit check: 348 bytes, `func_00328A20: 0 of 28
 * places match`. The older 344-byte measurement used a conflicting prototype
 * for func_00328F18 and is superseded.
 *
 * Retail body: only when the object state (u8 at +0x20) is 2 or 3:
 *   data = object->0x68;
 *   f = func_00283CE0(data[0x44]) / func_00283CE0(0x14);
 *   func_00328D98(data + 0x30, 0x204080, data[0x58], (char *)0x2E, 1,
 *                 data + 0x20, func_002A7798(1.0f - f) * 0.75f, 0.0f);
 *   func_00328B68(object);
 *   func_00328F18(object + 0x10, 0x7F7F, func_002A7820(0x20, 0x40), 0xB, 2,
 *                 0.125f, 0.0f, 0.3f);
 *   func_00328F18(object + 0x10, 0x103080, func_002A7820(0x20, 0x40), 0xB, 2,
 *                 0.45f, 0.0f, 0.31f);
 *   func_00329488(object);
 * The prototype of func_00328F18 is (ptr, int, int, ptr, int, float, float,
 * float): this is the EE C ABI where integer/pointer arguments 5-8 live in $t0-$t3 and
 * float arguments start at $f12.  Without a prototype in scope at the call, C89
 * default argument promotion passes the floats as doubles and the call is
 * completely different -- the forward declaration is mandatory.
 *
 * Remaining measured difference (344 vs 324, 0x40 vs 0x30 frame): this cc1 keeps
 * object in $s4, data in $s0, data+0x30 in $s2, data+0x20 in $s1 and object+0x10
 * in $s3, plus 0.0f in $f21; retail has object in $s2, data in $s1, data+0x30
 * then object+0x10 in $s0, and reuses $f20 for 0.0f after the ratio dies.  The
 * extra saved registers and the extra $f21 save are the whole overrun.  Inline
 * call arguments (no named pos/v locals) did not change the hoisting of
 * `data + 0x20` and `object + 0x10`.
 *
 * Next experiment: a source shape that computes the 6th argument and
 * object+0x10 only at their calls (they are hoisted here), or evidence from a
 * matched caller of func_00328D98 in another level/source unit.
 */
extern float func_00283CE0(int);

extern float func_002A7798(float);

extern int func_002A7820(int, int);

extern void func_00328B68(char *);

extern void func_00328D98(char *, int, int, char *, int, char *, float, float);

extern void func_00328F18(char *, int, int, char *, int, float, float, float);

extern void func_00329488(char *);

void func_00328A20(char *obj)
{
    char *data;
    float f;

    if ((unsigned char)(*(unsigned char *)(obj + 0x20) - 2) < 2) {
        data = *(char **)(obj + 0x68);
        f = func_00283CE0(*(int *)(data + 0x44)) / func_00283CE0(0x14);
        func_00328D98(data + 0x30, 0x204080, *(int *)(data + 0x58), (char *)0x2E, 1,
                      data + 0x20, func_002A7798(1.0f - f) * 0.75f, 0.0f);
        func_00328B68(obj);
        func_00328F18(obj + 0x10, 0x7F7F, func_002A7820(0x20, 0x40), (char *)0xB, 2,
                      0.125f, 0.0f, 0.3f);
        func_00328F18(obj + 0x10, 0x103080, func_002A7820(0x20, 0x40), (char *)0xB, 2,
                      0.45f, 0.0f, 0.31f);
        func_00329488(obj);
    }
}
