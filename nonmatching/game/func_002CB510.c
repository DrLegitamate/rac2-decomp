/* Near miss: rebuilds the level-select availability list from the saved flags.
 *
 * wslcmp (boot): 0 of 28 places; 312 bytes against 312, first difference at +0x48.
 * Only three words differ, all of them a register-choice tie in the two address
 * materialisations of the loop setup:
 *   retail  addiu v0,s3,%lo ; lui s4,%hi ; addiu s4,s4,%lo ; addiu s1,v0,0xC
 *   here    addiu v1,s3,%lo ; lui v0,%hi ; addiu s4,v0,%lo ; addiu s1,v1,0xC
 * plus the D_001A7C01 byte load into v0 (retail) against v1 (here). The loop,
 * the state[0] reset, the flag chain and the table lookup are retail's.
 * Same cc1 "address destination as its own temporary" wall as
 * func_L05_004155A0: retail folds the %hi/%lo pair into one register, this
 * build gives the %hi a separate temporary and the rest of the allocation
 * follows it. A 28 Oct explicit state-pointer and byte-table-pointer form
 * measured 300/312 bytes, 0/28, and changed the allocation more broadly; the
 * original 312-byte form remains closer. Reopen with a source form that makes
 * the %hi/%lo pair coalesce.
 */
extern char D_001F2840[];

typedef struct {
    int count;
    int id;
    int pad;
    int state[64];
} LevelSelect_210A40;

extern LevelSelect_210A40 D_00210A40;
extern unsigned char D_001A7BC8[];
extern unsigned char D_001A7C01;
extern int D_00258D70[];
extern void func_00288CB0(int, int);
extern void func_002C9A98(s32 *);
extern void func_002C9AD8(s32 *);
extern s32 func_002CB4E8(s32);

int func_002CB510(int flags)
{
    int result = -1;
    int i;

    for (i = 0; i <= D_00210A40.count; i++) {
        if (func_002CB4E8(i))
            D_00210A40.state[i] = D_001A7BC8[i] != 0;
    }
    D_00210A40.state[0] = 0;
    if (flags & 0x1000) {
        func_002C9A98((s32 *)&D_00210A40);
    } else if (flags & 0x4000) {
        func_002C9AD8((s32 *)&D_00210A40);
    } else if (flags & 0x40) {
        result = D_00210A40.id;
        if (D_00258D70[result * 2] == 0xB47 && D_001A7C01 == 0)
            func_00288CB0(0x19, 1);
        else
            func_00288CB0(result, 1);
    }
    return result;
}
