/* func_002A8F70 - retained near miss, USA v1.01.
 *
 * Profile: default `-O2 -G0 -ffunction-sections`; 340 bytes at the boot and 27
 * level placements. Current-master `tools/check.py` compiles this candidate to
 * 312 bytes, 0 of 28 places. It recovers the existing-entry owner/time check,
 * flag merge, ring insertion, helper call and both 16-byte transfers. Retail
 * uses a 0x50 frame and saves s0-s7; this candidate uses a 0x40 frame and a
 * smaller saved-register set. The register allocation and branch placement
 * still differ. A current-master explicit `if`/`else` for the threshold result
 * grew the candidate to 316 bytes; keeping the ring-table base in a local
 * pointer instead produced 304 bytes. Both alternatives match 0/28. The two
 * qword transfers use the reviewed shared `qcopy` helper; no function-local
 * instruction sequence is added.
 */
#include "common.h"

struct A8F70Entry {
    u8 pad0[0x10];
    f32 pos[4];
    s32 i20;
    s32 flags;
    u8 b28;
    u8 b29;
    u16 h2A;
    f32 f2C;
    s32 i30;
    f32 f34;
    u8 *owner;
    s32 i3C;
};

extern s32 D_001BAF80[];
extern struct A8F70Entry D_001BF200[];
extern f32 func_00282DF0(void *vector);

void func_002A8F70(u8 *owner, s32 value, s32 flags, void *first, void *second, f32 time)
{
    s32 index = D_001BAF80[5];
    s32 oldFlags = 0;
    struct A8F70Entry *entry;

    if (owner[0xA8] != 0xFF) {
        entry = &D_001BF200[owner[0xA8]];
        if (entry->owner == owner) {
            if (time < entry->f2C) {
                entry->flags |= flags;
                return;
            }
            oldFlags = entry->flags;
        }
    }

    entry = &D_001BF200[index];
    entry->i20 = value;
    entry->flags = flags | oldFlags;
    entry->f34 = time;
    entry->owner = owner;
    entry->f2C = time;
    entry->i3C = 0;
    entry->i30 = func_00282DF0(second) > 0.0001f;
    qcopy(entry, first);
    qcopy(entry->pos, second);
    owner[0xA8] = (u8)index;
    D_001BAF80[5] = (index + 1) & 0x3F;
}
