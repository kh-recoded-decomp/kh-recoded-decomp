#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct {
    fx32 x;
    fx32 y;
} FxPoint;

extern void IndexedRecord_SetPair(void *recordBase, int recordIndex, FxPoint *position);

void SetSlotEntryPosition(int listIndex, int entryIndex, int x, int y, Ov101State *state)
{
    void *slotList = state->slotLists[listIndex];
    SlotEntry *entry;
    FxPoint position;

    if (listIndex == 0) {
        entry = &state->primaryEntries[entryIndex];
    } else {
        entry = &state->secondaryEntries[entryIndex];
    }

    entry->x = x;
    entry->y = y;
    position.x = (fx32)(((float)entry->x > 0) ? ((float)entry->x * 4096.0f + 0.5f) : ((float)entry->x * 4096.0f - 0.5f));
    position.y = (fx32)(((float)entry->y > 0) ? ((float)entry->y * 4096.0f + 0.5f) : ((float)entry->y * 4096.0f - 0.5f));
    IndexedRecord_SetPair(slotList, entry->recordIndex, &position);
}
