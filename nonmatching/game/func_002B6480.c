/* func_002B6480 - 308 bytes, 28 places (src/game/002B6120.c).  Needs -G8
   (D_001B32B8 is reached through $gp), so it would go in src/game/002B6480-g8.c
   with its marker removed from 002B6120.c.  Writes two DMA tags at the packet
   pointer D_001B22A8, advances it, counts the packet in D_001B8840, draws
   through func_0027D4B8 or func_0027D5C0, ends the chain and sets D_001B32B8.

   Near miss: right size, 7 lines differ after masking relocations, all in
   002B6534..002B6558.  Retail loads the packet pointer into $v1 and the count
   into $v0; this has them swapped.  The stores must go through
   `*(int *)(D_001B22A8 + off)` with D_001B22A8 a char pointer: `int *`
   indexing lets GCC keep the pointer in a register (244 bytes).

   29 October 2026 integration check: moving this body to a temporary dedicated
   `src/game/002B6480-g8.c` unit with `-O2 -G8 -ffunction-sections` kept it at
   308 bytes but still matched 0/28; after relocation masking, the first
   mismatch was +0xBC. The temporary source, flag entry and marker change were
   restored. The profile does not resolve the packet/count scheduling.

   Tried (same swap or worse): count++ before the pointer advance (304 bytes),
   `+= 1`, an unsigned count, the count as int D_001B8840[13], the advance as
   `(int *)p + 8`, `p = p + 0x20`, the count in a local, a void * pointer. */

/* 29 October 2026 typed-DMA-packet probe, not retained as a candidate:
 * representing the two 16-byte tags as a struct array under
 * `-O2 -G8 -ffunction-sections` compiles to 244/308 bytes and matches 0/28.
 * The compiler reloads D_001B22A8 repeatedly and changes the tag-address
 * materialization and setup order. This does not reproduce the packet/count
 * scheduling in retail. The temporary source and cflags entry were removed.
 */

#include "include_asm.h"


extern char *D_001B22A8;
extern int D_001A742C;
extern int D_001A6AF0[];
extern struct { char pad[0x34]; int count; } D_001B8840;
extern char *D_001BAD40[];
extern char *D_001B32B8 __attribute__((sda));
extern void func_0027D4B8(void *);
extern void func_0027D5C0(void);
extern void func_0011AED0(int);

void func_002B6480(int *p) {
    D_001B22A8 = (char *)p;
    p[0] = 0x30000009;
    *(int *)(D_001B22A8 + 4) = (D_001A742C + 0xC0) & 0x0FFFFFFF;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 0xC) = 0x50000009;
    *(int *)(D_001B22A8 + 0x10) = 0x30000025;
    *(int *)(D_001B22A8 + 0x14) = (int)D_001A6AF0;
    *(int *)(D_001B22A8 + 0x18) = 0;
    *(int *)(D_001B22A8 + 0x1C) = 0x50000025;
    D_001B22A8 += 0x20;
    D_001B8840.count++;
    if (D_001BAD40[0])
        func_0027D4B8(D_001BAD40[0]);
    else
        func_0027D5C0();
    *(int *)D_001B22A8 = 0x70000000;
    *(int *)(D_001B22A8 + 4) = 0;
    D_001B32B8 = D_001B22A8 + 0x10;
    func_0011AED0(0);
}
