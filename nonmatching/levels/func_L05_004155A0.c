/* Batch 3 (2026-10-28) handoff notes:
# func_L05_004155A0 (524 B, 1 place) -- w5 handoff, 5 differing lines (same as the nonmatching/ note)

draft.c is the nonmatching/ draft in place in L05_00314E28.c (default -G0 flags, 524 B). Change over the draft: the table pointer is the incomplete sda array element (`extern char *D_L05_001B251C[] __attribute__((sda)); rec = D_L05_001B251C[0] + idx * 256`); that gives the tied `lui;lw` macro form (destination = address temporary) in one register pair, with both retail registers v0/v1 swapped though.
Remaining: the order of the table-pointer load against the `lw ...,0x260(state)` reload: retail `lui v0,0x1B ; lw v0,0x251C(v0) ; lw v1,0x260(s2) ; sll v1,v1,8 ; addu v0,v0,v1`, ours idx first (`lw v0,0x260 ; lui v1 ; lw v1,0(v1) ; sll v0 ; addu v0,v1,v0`). Same wall in func_L05_00415B38 and func_L05_0041C860 (3 lines there, branch-likely forms exact). Tried the same battery as listed in func_L05_0041C860.

## check.py --diff (masked, differing lines only; ours | retail)
```
05_feltzin_system: instruction at +0xe0 differs
  00415680  lw          $v0, 0x260($s2)              | lui         $v0, 0x1B
  00415684  lui         $v1, 0x0                     | lw          $v0, 0x251C($v0)
  00415688  lw          $v1, 0x0($v1)                | lw          $v1, 0x260($s2)
  0041568C  sll         $v0, $v0, 8                  | sll         $v1, $v1, 8
  00415690  addu        $v0, $v1, $v0                | addu        $v0, $v0, $v1
func_L05_004155A0: 0 of 1 places match (src/levels/05_feltzin_system/L05_00314E28.c)
masked diff lines: 5
```
*/

/* In src/levels/05_feltzin_system/L05_00314E28.c (default -G0): change `extern char D_L05_001B251C[];` to `extern char *D_L05_001B251C[] __attribute__((sda));`,
   add `extern char D_00188660[];` and make func_3719A8 return int. */
extern float func_3067D8(char *a, char *b);
void func_L05_004155A0(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *r;
    char *rec, *rec2, *rec3;
    char buf[0x10];
    int st;

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_379860(object) == 0)
            return;
        func_L05_004157B0(object);
        func_3065F8(buf);
        if (*(int *)(state + 0x264) != 0)
            func_379E60(object, 0, 0, 0);
        return;
    }
    r = func_379CA0(object);
    if (*(int *)(r + 0x110) == 0)
        return;
    {
    int one = 1;
    func_37C160(object);
    func_37B538(object, 0, 0, 0);
    func_37B948(object, one, 32.0f);
    st = *(int *)(r + 0x110);
    if (st == one) {
        if (*(int *)(state + 0x260) != -1) {
            *(int *)(r + 0x11C) = st;
            rec = D_L05_001B251C[0] + *(int *)(state + 0x260) * 256;
            *(int *)(r + 0x120) = (int)rec;
            if (func_3067D8(rec + 0x10, object + 0x10) < 10.0f) {
                rec2 = D_00188660 + *(int *)(state + 0x270) * 0x70;
                if (*(char **)(rec2 + 0x88) != object ||
                    *(unsigned char *)(rec2 + 0x74) == 0) {
                    if (func_332AB8(0x190) == 0)
                        *(int *)(state + 0x270) =
                            func_3719A8(0xE, 0, object, 0xFBF);
                }
            }
        }
        if (*(int *)(r + 0x104) != 0)
            func_L05_004158B0(object);
        if (func_37B888(object) != 0)
            func_37B6D0(object);
        func_3062A0(state + 0x268);
        func_L05_00415958(object);
    }
    }
    rec = D_00188660 + *(int *)(state + 0x26C) * 0x70;
    if (*(char **)(rec + 0x88) != object || *(unsigned char *)(rec + 0x74) == 0)
        *(int *)(state + 0x26C) = func_3719A8(0, 6, object, 0xF73);
}
