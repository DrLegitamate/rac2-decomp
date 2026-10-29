/* func_0029F840 - USA v1.01 first C reconstruction, 28 Oct 2026.
   `python3 tools/check.py func_0029F840 --diff`: 284 bytes vs. 288; 0/28.
   It represents the entry checks, vector-helper updates, optional output loop
   and signed return. Four bytes short; address/register lifetimes, branch
   scheduling and pointer-copy ABI still differ. The retail coefficient at
   the initial float multiply is 0x3A800000 (1/1024); candidate uses that.
   Current-master diff replay on 28 Oct 2026 reconfirmed 284/288 and 0/28:
   the body schedules the entry checks, helper arguments and loop differently,
   and cc1 uses a different callee-saved register allocation. The pointer
   increment/copy loop is not an isolated four-byte omission. A fresh form
   keeping 1/1024 in a local and multiplying by a field reload at each helper
   call measured 280/288, 0/28; it moved the constant to the wrong FPU register
   and changed saved-register allocation.
   Marker remains; no match is claimed. */
extern void func_00282D60(void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283130(void *, unsigned long long);
extern void func_00282D30(void *, void *, float);
int func_0029F840(void *object, void *out, int count, int index) {
    unsigned char *base = *(unsigned char **)((char *)object + 0x24);
    int idx = *(short *)((char *)object + 0x2E);
    unsigned char *entry;
    float scale = *(float *)((char *)object + 0x2C) * (1.0f / 1024.0f);
    int n;
    int i;
    unsigned long long q;
    if (idx == 0) return 0;
    entry = base + idx * 0x10 + index;
    if (entry[1] == 0xFF) return 0;
    func_00282D60(entry, scale);
    func_00283098(out, out, (char *)object + 0xC0);
    func_00282CC0(out, out, (char *)object + 0x10);
    n = *(short *)(entry + 6);
    if (out != 0 && count > 0) {
        unsigned char *src = entry + 0x10;
        unsigned char *dst = out;
        for (i = 0; i < n; i++) {
            q = *(unsigned long long *)src;
            func_00283130(dst, q);
            func_00282D30(dst, dst, scale);
            *(float *)(dst + 0xC) = 1.0f;
            src += 8;
            dst += 0x10;
        }
    }
    return n;
}
