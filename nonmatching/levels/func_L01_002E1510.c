/*
 func_L01_002E1510 (348 bytes, 13 places) - default flags, in L01_002A7248.c; size exact (w5, 2026-10-28), 19 masked lines differ.
 Retail's shape: do/while with n-- between the two calls, q = a0 + 0x30 before p, k = (i & 1) ? 2 : 0, second record pointer a0 + (off + 16),
 separate p2/q2 variables for the second loop (gives retail's s0/s1 roles in both loops). Open: register numbers only (retail a0 -> s4, a1 -> s6,
 i+1 -> s5, r -> s3, n -> s2; ours a0 -> s6, a1 -> s5, i+1 -> s4, r -> s2, n2 -> s3).
 */
extern void func_00283098(void *a0, void *a1, void *a2);
extern void func_00283738(void *a0, void *a1, void *a2);
extern void func_00280B90(void *a0, void *a1, int a2);

void func_L01_002E1510(char *a0, int a1, char *a2, int a3, char *a4) {
    float buf[12];
    char *p;
    char *q;
    char *r;
    char *p2;
    char *q2;
    int n;
    int n2;
    int i;
    int k;
    int off;

    if (a1 > 0) {
        q = a0 + 0x30;
        p = a0 + 0x20;
        n = a1;
        do {
            func_00283098(p, p, a2);
            p += 0x90;
            n--;
            func_00283098(q, q, a2);
            q += 0x90;
        } while (n != 0);
    }
    func_00283738(buf, a2, a2);
    for (i = 0; i < a3; i++) {
        k = (i & 1) ? 2 : 0;
        if (a1 > 0) {
            off = k * 16;
            r = a0;
            p2 = a0 + off;
            q2 = a0 + (off + 16);
            n2 = a1;
            do {
                func_00283098(p2, p2, buf);
                n2--;
                p2 += 0x90;
                func_00283098(q2, q2, buf);
                q2 += 0x90;
                func_00280B90(r, a4, 1);
                r += 0x90;
            } while (n2 != 0);
        }
    }
}
