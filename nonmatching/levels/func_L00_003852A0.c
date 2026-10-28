/* Near miss, worker w3 batch 3: 204/204 B, 0/27, 18 lines. Unit L00_0037E898-nosplit.c (-O2 -G0 -ffunction-sections -mno-split-addresses); gp loads D_98 and D_B0 through SDATA aliases, the rest plain externs. Left: retail s0=&D_EC0 and s1=state (ours reversed), and the arg-load order in calls 1 and 3. */

extern int func_00115DA8(char *, char *, ...);
extern void func_L00_002E95C0(int first, int second, int third, char *buffer, int flags);
extern char D_L00_001AEEC0[];
extern char D_L00_001AEED0[];
extern int D_L00_001AEE98 SDATA(D_L00_001AEE98);
extern int D_L00_001AEE9C;
extern int D_L00_001AEEA0;
extern int D_L00_001AEEA4;
extern int D_L00_001AEEA8;
extern int D_L00_001AEEAC;
extern int D_L00_001AEEB0 SDATA(D_L00_001AEEB0);
extern int D_L00_001AEEB4;
extern int D_L00_001AEEB8;

void func_L00_003852A0(char *object)
{
    char buffer[0x100];
    char *state = *(char **)(object + 0x68);

    func_00115DA8(buffer, D_L00_001AEEC0, *(int *)(state + 0x60));
    func_L00_002E95C0(D_L00_001AEE98, D_L00_001AEE9C, D_L00_001AEEB8, buffer, -1);
    func_00115DA8(buffer, D_L00_001AEED0, *(int *)(state + 0x70) + 1);
    func_L00_002E95C0(D_L00_001AEEA0, D_L00_001AEEA4, D_L00_001AEEB4, buffer, -1);
    func_00115DA8(buffer, D_L00_001AEEC0, *(int *)(state + 0x64));
    func_L00_002E95C0(D_L00_001AEEA8, D_L00_001AEEAC, D_L00_001AEEB0, buffer, -1);
}

