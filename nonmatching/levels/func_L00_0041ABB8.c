/* Batch 3 (2026-10-28) handoff notes:
func_L00_0041ABB8 (w2). Flags -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier. 224 vs 228 bytes. Retail has 'daddu s3,a3' in the prologue and a nop in the bltz slot; ours sinks the move into the bltz slot (one word less). Tried: D+idx*0x40 operand orders (5 forms), all 10 int/float interleavings of func_002FED90's prototype. No change.
*/

/* Retained C reconstruction: 224/228 bytes.
   Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
   0/27 in us, pal and us2. Complete C replaces the comment-only screen; both quadword copies are reachable. The table-pointer load is hoisted into the prologue and the fourth argument move fills a branch slot, losing one instruction.
   Reopen only with new source/type/lifetime evidence; bounded scheduling/profile variants did not close it. */

typedef int Quad __attribute__((mode(TI)));
extern char *D_L00_001B144C __attribute__((sda));
extern void func_002FEE50(int);
extern int func_002FED90(void *, void *, float, float, float);
void func_L00_0041ABB8(char *self, Quad *first, Quad *second, int value)
{
    char *state = *(char **)(self + 0x68);
    char *slot = D_L00_001B144C + *(int *)(state + 0x3C) * 0x40;
    *(Quad *)slot = *first;
    *(Quad *)(slot + 0x10) = *second;
    if (*(int *)(slot + 0x38) >= 0) func_002FEE50(*(int *)(slot + 0x38));
    *(int *)(slot + 0x38) = func_002FED90(self, slot, 1.0f, 1.0f, 1.0f);
    *(int *)(slot + 0x30) = value;
    *(int *)(slot + 0x34) = 0;
    *(int *)(state + 0x48) = *(int *)(state + 0x3C);
    *(int *)(state + 0x3C) += 1;
    if (*(int *)(state + 0x3C) >= 35) {
        *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x40) = 1;
    } else if (*(int *)(state + 0x40) != 1) {
        *(int *)(state + 0x44) += 1;
    }
}
