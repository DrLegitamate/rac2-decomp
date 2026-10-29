/* Lead's follow-up, 29 Oct: the 0x8000 block's call takes 3 like the others ($a0 still holds
   3 there in retail), which gives 532/536 bytes in 00345358-g8.c. Retail keeps the 0x48C
   counter in $v1 in every block and fills the 0x40 block's first branch slot with the
   else-call's `addiu a0,5`; flipping the class-record lookup to index-first changed nothing. */
/* func_00345D58 - 536 bytes, boot and 27 levels (28 places).  Worker attempt (batch 3, wA).
   Not matched: the C below compiles to 536 bytes in a -G8 unit (check.py; 540 as a plain file)
   with the same control flow, but
   the register choice differs in places, so check.py reports 0 of 28 places.

   Remaining difference (measured with tools/check.py --diff):
   - flags 0x1000 block: GCC takes the loaded field in v0 and the -1 in v1,
     retail the other way round; the same swap in the flags 0x2000 block and the 0x40 block;
   - flags 0x8000 block: retail passes the incoming a0 to func_002E5E58 without a move,
     GCC copies the object pointer from s0 into a0 first;
   - flags 0x40 block: GCC schedules the table address (lui/addiu of D_001AA898) and the
     word loads in another order, and puts the D_00239BA0 base in a1 instead of v1.
   Tried: store-first versus if/else stores for the 0x8000 and 0x2000 blocks (store-first
   matches retail's branch shape, kept); a typed 10-byte table entry for D_001AA898 (kept);
   a block-local temporary for the 0x1000 clamp (no change in registers, not kept).
   The 0x1000 clamp is movz in retail and stays so here. D_001ADB10 is the -G8 word at
   $gp-0x14E0 (GP 0x001AEFF0); its name is inferred from that offset. */

extern char D_001AA898[];

extern void func_002E5E58(int, int, int);

typedef struct {
    char pad06[6];
    short f06;
    char pad08[0x3A];
    short f42;
    char pad44[0x9C];
} ClassRecord;

extern unsigned char D_00139568[];
extern ClassRecord D_00239BA0[];
extern unsigned char D_001A7AF8[];
extern char D_001F2840[];

extern int D_001ADB10 __attribute__((sda));

typedef struct {
    char pad00[6];
    short f06;
    char pad08[2];
} StateEntry;

/* Steps the 3-state index at +0x48C of the object with the flag word; the object's
   selected entry (10-byte records at D_001AA898, short at +6) feeds the class record
   through D_00139568 and the small-data word D_001ADB10. */
void func_00345D58(char *p, int flags)
{
    int v;
    int s1;
    int a2;

    if (flags & 0x1000) {
        func_002E5E58(3, 0, 0);
        *(int *)(p + 0x490) = 0;
        *(int *)(p + 0x498) = 3;
        v = *(int *)(p + 0x48C) - 1;
        if (v < 0)
            v = 0;
        *(int *)(p + 0x48C) = v;
    } else if (flags & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(p + 0x490) = 0;
        *(int *)(p + 0x498) = 0;
    } else if (flags & 0x8000) {
        func_002E5E58(3, 0, 0);
        v = *(int *)(p + 0x48C) - 1;
        *(int *)(p + 0x48C) = v;
        if (v < 0)
            *(int *)(p + 0x48C) = 2;
    } else if (flags & 0x2000) {
        func_002E5E58(3, 0, 0);
        v = *(int *)(p + 0x48C) + 1;
        *(int *)(p + 0x48C) = v;
        if (v >= 3)
            *(int *)(p + 0x48C) = 0;
    } else if (flags & 0x40) {
        s1 = ((StateEntry *)D_001AA898)[*(int *)(p + 0x48C)].f06;
        if (s1 != 0 && D_001A7AF8[s1] != 0) {
            char *cb;

            func_002E5E58(4, 0, 0);
            D_001ADB10 = D_00239BA0[D_00139568[*(int *)(p + 0x494)]].f06;
            cb = D_001F2840;
            if (*(int *)(cb + 0x44) == s1)
                *(int *)(cb + 0x44) = 0;
            else
                *(int *)(cb + 0x44) = s1;
        } else {
            func_002E5E58(5, 0, 0);
        }
    }

    a2 = ((StateEntry *)D_001AA898)[*(int *)(p + 0x48C)].f06;
    *(int *)(p + 0x494) = a2;
    if (a2 != 0 && D_001A7AF8[a2] != 0)
        D_001ADB10 = D_00239BA0[D_00139568[a2]].f06;
}
