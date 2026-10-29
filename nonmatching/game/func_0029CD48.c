/* func_0029CD48 - corrected retained near miss.
 *
 * The earlier 240-byte candidate declared func_0029CD20 with an integer
 * argument, contrary to the actual no-argument definition in src. Using the
 * real interface and converting the loaded state word to the pointer expected
 * by func_00115484 produces 232 bytes vs. 240 retail and 0/28 USA v1.01
 * placements (fresh standalone replay, 29 October 2026). The first differences
 * are resident state/global address setup and the placement of func_0029CD20
 * relative to the clear sequence. Since the candidate size differs, the checker
 * does not qualify the byte layout. Older tail analysis based on the false helper prototype is
 * invalid and should not be used to guide a new attempt.
 * 29 October 2026: temporarily marking the local `func_0029CD20` definition
 * `noinline` leaves this candidate at 232 bytes and 0/28. The size gap and
 * address/store setup differences are unchanged, so that attribute does not
 * provide a source-level route to the retail body.
 */

extern char D_001BAEC0[];
extern int D_00138180[];
extern int D_001A79F0 __attribute__((section(".data")));
extern char *D_001A8CFC;

extern void func_00115484(void *, int, int);
extern void func_0029CD20(void);
extern int func_336DA8(int, int);
extern int func_34E5C0(int, int);
extern void func_0029C0D0(void);
extern void func_0029C108(void);
extern void func_0029C0D8(void);
extern void func_0029CD18(void);

/* The level object's callback table: the two slots at +0x734C and +0x7350. */
typedef struct { char pad[0x734C]; void *cb1; void *cb2; } SubBf;

void func_0029CD48(void)
{
    char *state = D_001BAEC0;
    char *obj;
    int mode;

    func_00115484((void *)(unsigned int)*(unsigned int *)(state + 0x80), 0xCD, 0x40000);
    D_00138180[104] = 0;
    D_00138180[105] = 0;
    D_00138180[106] = 0;
    D_00138180[107] = 0;
    D_00138180[108] = 0;
    D_00138180[109] = 0;
    D_00138180[110] = 0;
    D_00138180[111] = 0;
    D_00138180[112] = 0;
    D_00138180[113] = 0;
    D_00138180[114] = 0;
    D_00138180[115] = 0;
    func_0029CD20();
    mode = func_336DA8(0x3F490, *(int *)(state + 0x80));
    obj = (char *)func_34E5C0(mode, 0x40000);
    mode = D_001A79F0;
    D_001A8CFC = obj;
    if (mode == 0x1F5) {
        ((SubBf *)(obj + 0x38000))->cb1 = func_0029C0D0;
        ((SubBf *)(obj + 0x38000))->cb2 = func_0029CD18;
    } else {
        ((SubBf *)(obj + 0x38000))->cb1 = func_0029C108;
        ((SubBf *)(obj + 0x38000))->cb2 = func_0029C0D8;
    }
}
