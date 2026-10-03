#include "nitro/types.h"

typedef struct {
    u8 pad0[0x18];
    u16 primary : 1;
    u16 reserved1 : 4;
    u16 linked : 1;
    u16 mirrored : 1;
    u16 owned : 1;
    u16 reserved8 : 8;
    u8 state;
    u8 id;
    u8 pad1c[4];
} SlotEntry;

typedef struct {
    u8 pad0[4];
    int id;
    u8 pad8[0x44];
    u16 reserved0 : 4;
    u16 primary : 1;
    u16 linked : 1;
} SlotSource;

extern void func_01ff8830(void *dst, int value, int size);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);

void InitSlotEntry_020d19f8(SlotEntry *entry, SlotSource *source, int mirrored, int player)
{
    func_01ff8830(entry, 0, sizeof(SlotEntry));
    entry->state = 0;
    entry->id = source->id;
    entry->mirrored = (u16)mirrored;
    entry->linked = source->linked;
    entry->primary = source->primary;
    if (IsPlayerEntryFlagSet_02050014(player, 0x50)) {
        entry->owned = 1;
    }
}
