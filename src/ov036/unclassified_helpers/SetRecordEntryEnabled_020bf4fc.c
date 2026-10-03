#include "nitro/types.h"

typedef struct RecordEntry {
    s32 recordIndex;
    u8 pad_04[0x8];
    u32 flags;
} RecordEntry;

extern u8 *data_ov036_020c3844;
extern void func_0204f378(void *list, int index, int value);

void SetRecordEntryEnabled_020bf4fc(RecordEntry *entry, int enabled)
{
    if (enabled) {
        entry->flags |= 1;
    } else {
        entry->flags &= ~1;
    }
    func_0204f378(data_ov036_020c3844 + 0x18, entry->recordIndex, enabled);
}
