/* SPDX-License-Identifier: MIT
 *
 * Near miss: func_002DE618, 212 bytes in the retail boot and in every level, 28 places.
 * Profile -O2 -G0 -ffunction-sections (src/game/002DDEC8.c).
 *
 * It looks a chunk up by key in the five-entry (key, flags) table at D_001B1F50. On the first
 * entry with that key and flag 2, it clears flag 4 (and, when the byte at D_001F2840 + 0xDB is
 * set, calls func_002B7AD0 and clears the byte), then clears flag 2 and returns 0. Without such
 * an entry it returns 0.
 *
 * Result: 212/212 bytes, 0/28 places in USA v1.01. Every instruction is retail's except the
 * registers of the two reduced table pointers: retail walks the keys in $a1 and the flags in
 * $a2, and ends the loop on the keys pointer (end D_001B1F50 + 0x28); this source puts the
 * flags in $a1 and the keys in $a2, ends on the flags pointer, and increments the two in the
 * other order (10 instructions differ).
 *
 * The local root pointer is what gives retail's hoisted %hi of D_001F2840 in $t0 and the
 * address in $s0; indexing D_001F2840 directly folds the 0xDB into the %lo (204 bytes).
 * Walking the table with pointers (as func_002DE6F0 does) loses the i * 8 offset in $s2 that
 * retail keeps for the final store (192 bytes).
 *
 * Unchanged by: do/while and continue forms, an i += 2 step, unsigned i, u32 key, the compare
 * operands swapped, D_001B1F50[i * 2] for the Chunk read, the tests joined with &&, reading the
 * flags again for each test, ^= 4 on the table, a struct for D_001F2840. Worse: local table
 * pointers, the flags read through Chunk, the flags address taken before the key test.
 * decomp-permuter (OpenRAC tools/permuter, rac2/ntsc) ran 12,499 candidates from this base
 * without going below its score of 10. Reopen with a source shape, or a compiler finding, that
 * changes the order strength reduction creates the two pointers in.
 *
 * This replaces the 188-byte draft of 2414789a (pointer walks with a byte-offset counter),
 * whose final clear merged into the flags walk; the array index i * 2 keeps it separate.
 */

#include "include_asm.h"

typedef unsigned int u32;
typedef unsigned char u8;

typedef struct {
    u32 key;
    u32 flags;
} Chunk;

extern int D_001B1F50[] __attribute__((sda));
extern int D_001B1F54[] __attribute__((sda));
typedef int s32;

extern s32 D_001F2840[];
void func_002B7AD0(void);

int func_002DE618(int key)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (((Chunk *)D_001B1F50)[i].key == key) {
            u32 flags = D_001B1F54[i * 2];
            if (flags & 2) {
                if (flags & 4) {
                    u8 *root = (u8 *)D_001F2840;
                    D_001B1F54[i * 2] = flags ^ 4;
                    if (root[0xDB] != 0) {
                        func_002B7AD0();
                        root[0xDB] = 0;
                    }
                }
                D_001B1F54[i * 2] &= ~2;
                return 0;
            }
        }
    }
    return 0;
}
