/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections.
 * Current-master USA v1.01 replay, freshly checked 29 October 2026: 236 bytes;
 * retail 224 bytes, 0/28 places. The decoded diff begins with the mismatched
 * negative-request branch target, then shows the full-width index conversions
 * and conditional/address scheduling differences described below.
 * Historical PAL and USA v2.00 checks also reported 0/28.
 * No applicable carrying place was absent; no strict-build qualification.
 * Full-width unsigned-long callee result must be preserved at the call. The effective table
 * address is 32-bit, so a temporary probe narrowed only that address index to unsigned int:
 * it reduced the candidate from 236 to 216 bytes (0/28), but changed register allocation
 * and control-flow/address scheduling. The original 236-byte form remains below. The helper
 * itself is verified as unsigned long by its 28/28 check; do not change its return contract.
 * Reopen with a new control-flow/register-allocation hypothesis.
 */
extern int ref_L00_002F5D40_01 __attribute__((sda));
extern unsigned int D_00139768[];
extern char ref_L00_002F5D40_00[];
extern char D_0014B540[];
extern unsigned char D_001A7BB4[];
extern unsigned long func_002EF010(int);
extern void func_00288B38(void *);
extern void func_002F5E20(int, int, int, int, int);

void func_002F5D40(int request)
{
    unsigned long index;
    int special;
    char *entry;
    char *table;
    int option;
    if (request < 0) {
        ref_L00_002F5D40_01 = 0;
    } else {
        index = func_002EF010(request);
        special = 1;
        if (request != 0xBF)
            special = 0;
        if ((unsigned int)request < 0xB1)
            D_00139768[(unsigned int)request >> 2] |= 1u << (request & 31);
        func_00288B38(ref_L00_002F5D40_00);
        table = D_0014B540;
        entry = table + ((index << 4) | 8);
        option = D_001A7BB4[0];
        if (*(int *)ref_L00_002F5D40_00)
            option = 0;
        func_002F5E20(*(int *)(entry + 8) + *(int *)(table + 4),
                     *(int *)(entry + 12), (int)(table + 8 + (index << 4)),
                     option, special);
    }
}
