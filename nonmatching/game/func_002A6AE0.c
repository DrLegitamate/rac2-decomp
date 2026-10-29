/*
 * func_002A6AE0: 28 October 2026 requalification using the supported
 * per-placement external name for the table previously misrepresented as
 * D_00264630. In an isolated default -O2 -G0 unit, `python3 tools/check.py
 * func_002A6AE0 --diff` reports 300/372 bytes and 0/28 USA v1.01 placements on the current checkout.
 * The `ref_L00_002A6AE0_00` relocation resolves at all checked placements, so
 * the earlier claim that no supported mapping existed is superseded. Keep this
 * semantically complete draft as the starting point; its compact loop and
 * state-update code still differ substantially from retail. A 29 Oct 2026 unrolled
 * four-comparison-per-record search measured 304/372 bytes, 0/28, so the nested
 * search remains the closer semantic draft. The prior 356-byte
 * result is historical and was not qualified with this reference mapping.
 */
extern short ref_L00_002A6AE0_00[];
extern unsigned char D_001A7A0A;
extern unsigned char D_001A7A32[2];
extern int D_0019BE70 __attribute__((sda));
extern unsigned short D_00188510[];
extern void func_0029B698(int);

void func_002A6AE0(unsigned char *object, int mode)
{
    short id = *(short *)(object + 0xAA);
    int found = -1;
    int i;
    int j;

    for (i = 0; i < 0x40; i++) {
        short *row = ref_L00_002A6AE0_00 + i * 12;
        for (j = 0; j < 4; j++) {
            if (row[j] == id) {
                found = i;
                goto searched;
            }
        }
    }
searched:
    if (D_001A7A0A != 0 && D_0019BE70 == -1 && D_001A7A32[0] < 0x14) {
        D_001A7A32[1]++;
        if ((unsigned char)(D_001A7A32[1] * 2) >= D_001A7A32[0]) {
            func_0029B698(0xB4);
            D_001A7A32[0]++;
            D_001A7A32[1] = 0;
        }
    }

    if (found >= 0 && (mode == 0 || mode == 1)) {
        unsigned short *counter = (unsigned short *)((char *)D_00188510 + found * 4 + mode * 2);
        if (*counter < 0x270F)
            ++*counter;
    }
}
