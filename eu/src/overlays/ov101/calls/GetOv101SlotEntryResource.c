#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    s32 x;
    s32 y;
    u8 pad_0C[0x10];
} SlotEntry;

typedef struct {
    u8 pad_00[0x30];
    u8 *resource;
    u8 pad_34[0x8C - 0x34];
} SlotRecord;

typedef struct {
    u8 pad_00[0x18];
    SlotRecord records[1];
} SlotList;

typedef struct {
    u8 pad_0000[0x184];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
} Ov101State;

void *GetOv101SlotEntryResource(int listIndex, int entryIndex, Ov101State *state)
{
    SlotList *list = (SlotList *)state->slotLists[listIndex];
    SlotEntry *entry;
    SlotRecord *record;
    int recordIndex;
    u8 *resource;

    if (listIndex == 0) {
        entry = &state->primaryEntries[entryIndex];
    } else {
        entry = &state->secondaryEntries[entryIndex];
    }
    recordIndex = entry->recordIndex;
    if (recordIndex < 0) {
        return NULL;
    }
    record = &list->records[recordIndex];
    if (record == NULL) {
        return NULL;
    }
    resource = record->resource;
    if (resource == NULL) {
        return NULL;
    }
    resource += 8;
    if (resource == NULL) {
        return NULL;
    }
    return resource;
}
