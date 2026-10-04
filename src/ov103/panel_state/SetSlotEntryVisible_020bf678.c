#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    u8 pad_04[0x10];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x174];
    u8 slotLists[2][0x6434];
    SlotEntry entries[12];
} Ov103State;

extern void func_0204f378(void *recordBase, int recordIndex, int visible);

void SetSlotEntryVisible_020bf678(int listIndex, int entryIndex, int visible, Ov103State *state)
{
    SlotEntry *entry;

    if (listIndex == 0) {
        entry = &state->entries[entryIndex];
    } else {
        entry = NULL;
    }
    func_0204f378(state->slotLists[listIndex], entry->recordIndex, visible);
}
