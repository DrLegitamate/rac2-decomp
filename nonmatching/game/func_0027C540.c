/* func_0027C540 - first C candidate, 2026-10-28.
   `python3 tools/check.py func_0027C540 --diff`: 252 bytes vs. 288, 0/28.
   The loops and state clearing are represented, but address setup, loop
   control, and memory access schedules differ throughout. This unit needs
   -G8 for its three small-data words. Moving the first count load after the
   state stores still compiled to 252 bytes; spelling the first two globals
   as offsets from one byte-array symbol also stayed 252 bytes and introduced
   extra address arithmetic. No match is claimed. */
extern unsigned int D_001B22A8 __attribute__((section(".data")));
extern unsigned int D_001B15F4 __attribute__((section(".data")));
extern int D_001B1600 __attribute__((section(".data")));
extern unsigned int D_001A72D4 __attribute__((section(".data")));
extern unsigned int D_001A72D0 __attribute__((section(".data")));
extern unsigned char D_001B9740[] __attribute__((section(".data")));
extern unsigned char *D_001B1888 __attribute__((section(".data")));
extern unsigned char *D_001B1894 __attribute__((section(".data")));
extern unsigned char *D_001B1898 __attribute__((section(".data")));
extern unsigned int D_001A72DC __attribute__((section(".data")));
extern unsigned long long D_001A8780 __attribute__((sda));
extern unsigned long long D_001A8788 __attribute__((sda));
extern unsigned int D_001A8790 __attribute__((sda));
void func_0027C540(int arg) {
    unsigned int old = D_001B22A8;
    int count = D_001B1600;
    int i;
    D_001B15F4 = old;
    D_001B22A8 = old + 0x10;
    D_001A72D0 = D_001A72D4;
    for (i = 0; i < count; i++)
        *(unsigned long long *)(D_001B9740 + i * 0x10) = 0;
    D_001A8780 = 0;
    D_001A8788 = 0;
    D_001A8790 = 0;
    if (arg == 0) {
        int n = *(int *)(D_001B1888 + 0x44);
        for (i = 0; i < n; i++) {
            unsigned char *entry = D_001B1894 + i * 8;
            if (*(unsigned short *)(entry + 4) >= (D_001A72DC >> 8))
                *(unsigned short *)(entry + 4) = 0;
        }
        n = *(int *)(D_001B1888 + 0x24);
        for (i = 0; i < n; i++)
            *(unsigned short *)(D_001B1898 + i * 8 + 4) = 0;
    }
}
