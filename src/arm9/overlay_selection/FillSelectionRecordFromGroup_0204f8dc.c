#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x0e];
    u8 level;
    u8 pad_0f;
    u16 values[4];
} NamedEntry;

typedef struct {
    u8 pad_00[0x10];
    NamedEntry entry;
} OverlaySelectionRecord;

typedef struct {
    u8 pad_00[0x08];
    s32 value;
    u8 pad_0c[0x14];
    s32 nameIndex;
    s32 level;
} SlotPair0Entry;

typedef struct {
    u8 pad_0000[0x2db4];
    u16 entryId;
} GameState;

extern GameState *data_0205fe0c;

extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void PackNamedRecordEntry_0204f63c(NamedEntry *out, int index, int nameId);
extern void OpenRecordManager_02051c80(void);
extern void CloseRecordManager_02051cdc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern SlotPair0Entry *GetRecordSlotPair0Entry_02051ec8(s32 index);

void FillSelectionRecordFromGroup_0204f8dc(void)
{
    NamedEntry *entry;
    u16 entryId;
    SlotPair0Entry *slot;
    int groupBase;
    int i = 0;

    entry = &GetOverlaySelectionRecord_0204f768(i)->entry;
    entryId = data_0205fe0c->entryId;

    OpenRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(i, 1);
    slot = GetRecordSlotPair0Entry_02051ec8(entryId);
    PackNamedRecordEntry_0204f63c(entry, slot->nameIndex, i);
    entry->level = slot->level - 1;
    groupBase = (entryId - 0xd0) / 5 * 5 + 0xd0;
    for (; i < 4; i++) {
        entry->values[i] = GetRecordSlotPair0Entry_02051ec8(groupBase + i)->value;
    }
    ReleaseRecordSlot_02051dfc(0);
    CloseRecordManager_02051cdc();
}
