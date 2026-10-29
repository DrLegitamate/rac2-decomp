/* func_0033A520 (360 bytes, boot + 27 levels, src/game/003399B0.c, default -G0) - near miss,
   measured 21 October 2026 and rechecked 28 October 2026 with the current compiler (#222's
   mfc1 interlock is in: plain C remains 360/360 bytes, 0/28 USA v1.01 places).

   The plain C below is 360 bytes, 0 of 28 places: 26 of the 90 words differ, all in +0x58..+0xBC.
   Everything before (prologue, the allocation, the four clears) and after (from the first call's
   delay slot on) is retail's.

   What differs, and why: retail schedules two blocks there with no branch between them:
   block A = the rounding `(f32)(s32)(D_001B23A4 * 300.0f + 0.5f)` with the store of 70.0f to
   alloc[0] (300.0f loaded before D_001B23A4, alloc in $v0, the rounded value in $f0), ending at
   `cvt.s.w`; block B = `lui $s1,%hi(D_001ADC88)` first, then the alloc reload, the store of the
   rounded value to alloc[1] and the first call's arguments. One block (plain C) lets sched2
   interleave the argument set-up with the conversion chain. Calls do not end blocks in this cc1;
   no single flag separates them. The same block boundary after a scale-and-round of D_001B23A4
   is in func_0033C028 (its record) and twice in func_002900B8.
   - The previous record's `if (obj) { A } else { A }` (identical arms, cross-jumped by jump2
     after sched2) gives the boundary and 12 words off: the 300.0f/D_001B23A4 load order, alloc
     in $v1 (local-alloc's false-dependency rule: alloc dies right before the fix result is born
     in sched1's order), and block B's order. It is not admissible (identical arms).
   - `do { A } while (0);` (the loop-end note as a scheduling barrier, as func_00124818 and
     func_L23_0041C8C0 use it) plus `char *text = D_001ADC88;` written right after it (so the
     barrier insn is the `lui $s1`, which sched2 must issue first) gives block B exactly
     retail's; 6 words still differ in block A: the two loads' order, alloc in $v1 for $v0, the
     rounded value in $f1 for $f0 (it is a local pseudo then, and local-alloc keeps it off the
     add result's $f0; with a real block boundary it is a global pseudo and gets $f0).
     Statement order inside the loop, `300.0f * D` and a local copy of D_001B23A4 change nothing
     useful (the 70.0f store first is worse).
   What would unblock it: the original's construct for that boundary (probably a branch whose two
   arms compile alike, as func_0033C028's record argues), or evidence that a do-while(0) barrier
   is admissible here, plus the block-A allocation. */

typedef float f32;
typedef unsigned char u8;
typedef int s32;
extern void func_00336710(void *a0, void *a1, void *a2);
extern void func_00335F88(void *a0, f32 a1, f32 a2, f32 a3, f32 a4);
extern int *func_00335E20(void *a0);
extern void func_003369A8(void *a0, void *a1, void *a2);
extern int *func_00336DA8(int a0, int a1);
extern int func_00336E40(void *a0);
extern char D_001ADC88[];
extern f32 D_001B23A4 __attribute__((sda));

void func_0033A520(u8 *obj, void *arg)
{
    f32 v;
    char *text;

    *(s32 *)(obj + 0x1F8) = 0;
    *(void **)(obj + 0x200) = arg;
    if (arg != 0) {
        s32 *alloc = func_00336DA8(16, func_00336E40(arg));
        *(s32 **)(obj + 0x1FC) = alloc;
        alloc[1] = 0;
        alloc[2] = 0;
        alloc[3] = 0;
        alloc[0] = 0;
    }
    v = (f32)(s32)(D_001B23A4 * 300.0f + 0.5f);
    ((f32 *)*(s32 **)(obj + 0x1FC))[0] = 70.0f;
    text = D_001ADC88;
    ((f32 *)*(s32 **)(obj + 0x1FC))[1] = v;
    func_00336710(obj + 0x134, text, *(void **)(obj + 0x200));
    func_00335F88(obj + 0x134, 24.0f, 24.0f, 0.0f, 0.0f);
    *func_00335E20(obj + 0x134) = 0x60F0F0B0;
    *(f32 *)(obj + 0x204) = 65.0f;
    func_003369A8(obj + 0x170, text, *(void **)(obj + 0x200));
    *func_00335E20(obj + 0x170) = 0x80F0F0F0;
    func_00335F88(obj + 0x170, 0.7f, 0.7f, 0.0f, 0.0f);
}
