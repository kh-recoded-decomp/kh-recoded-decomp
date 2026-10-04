#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    s32 x;
    s32 y;
    u8 pad_0C[0x10];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x17C];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
} Ov101State;

extern void func_0204f378(void *recordBase, int recordIndex, int visible);

void SetSlotEntryVisible_020bfa6c(int listIndex, int entryIndex, int visible, Ov101State *state)
{
    SlotEntry *entry;

    if (listIndex == 0) {
        entry = &state->primaryEntries[entryIndex];
    } else {
        entry = &state->secondaryEntries[entryIndex];
    }
    func_0204f378(state->slotLists[listIndex], entry->recordIndex, visible);
}
