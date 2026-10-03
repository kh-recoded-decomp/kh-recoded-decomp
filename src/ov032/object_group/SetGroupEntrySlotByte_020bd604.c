#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1b8];
    u8 slots[32];
} GroupEntry;

extern GroupEntry *func_ov032_020bbc60(void *group);

void SetGroupEntrySlotByte_020bd604(void *group, u8 value, int slot)
{
    GroupEntry *entry = func_ov032_020bbc60(group);
    entry->slots[slot % 32] = value;
}
