#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    s32 x;
    s32 y;
    u8 pad_0C[0x10];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x184];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
} Ov101State;

extern void IndexedRecords_SetFlag2(void *recordBase, int recordIndex, int visible);

void SetOv101SlotEntryVisible(int listIndex, int entryIndex, int visible, Ov101State *state)
{
    SlotEntry *entry;

    if (listIndex == 0) {
        entry = &state->primaryEntries[entryIndex];
    } else {
        entry = &state->secondaryEntries[entryIndex];
    }
    IndexedRecords_SetFlag2(state->slotLists[listIndex], entry->recordIndex, visible);
}
