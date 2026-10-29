/* Corrected table base from the USA v1.01 retail body. The two table paths
   index the boot-resident D_0010B540 block at offsets 0x14F4 and 0x15D4.

   29 October 2026 current-master check in the original source unit:
   -O2 -G0 produces 64/68 bytes and 0/28 placements. This supersedes the old
   D_00105540 candidate: that symbol names a different address and did not
   describe retail's table references.

   The corrected candidate preserves the branch and table semantics, but cc1
   allocates the mask to $v1, table base to $v0 and loaded word to $v0;
   retail uses $v0, $v1 and $a0, respectively. `-fno-schedule-insns` remains
   0/28 and leaves the mask outside the retail branch delay slot. A byte-offset
   pointer form using the corrected base is 56/68 and hoists the index. Do not
   use artificial accesses or dependencies to force the allocation. A 29 October
   branch-local table-pointer form (choose one of the two table bases, then
   index it) also compiles to 56/68, 0/28: cc1 hoists the masked index and
   forms separate branch addresses, so the retail branch layout is lost.
   Artificial accesses or dependencies are not valid ways to force the retail
   allocation. A 29 October temporary whole-file `-fno-schedule-insns2` test
   linked the corrected symbol-based candidate into the boot; the build
   reported an instruction mismatch at +0x14. Sixteen other C functions in
   the translation unit also differed under that profile, so it is not a
   viable file-wide flag change.
*/
int func_00295870(int arg)
{
    extern int D_0010B540[];

    if ((arg & 0x100) == 0)
        return D_0010B540[(arg & 0xFF) * 2 + 0x15D4 / 4] > 0;
    return D_0010B540[(arg & 0xFF) * 2 + 0x14F4 / 4] > 0;
}
