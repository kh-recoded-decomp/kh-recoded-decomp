#include "nitro/types.h"

typedef struct TaggedEntry {
    u32 id : 18;
    u32 order : 6;
    u32 value : 7;
    u32 flag : 1;
} TaggedEntry;

typedef struct TaggedEntryTable {
    TaggedEntry *entries;
    u8 count;
} TaggedEntryTable;

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0x13b];
    TaggedEntryTable taggedEntries;
} OverlaySelectionRecord;

extern int data_020608c8[];
extern TaggedEntry *data_02060940[];

extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern TaggedEntry *FindTaggedEntry_0204f6a4(TaggedEntryTable *table, u32 id);
extern TaggedEntry *AddTaggedEntry_0204fe2c(TaggedEntryTable *table, u32 id, int flag, u32 value);

void RegisterTaggedEntry_0204ff18(u32 id)
{
    OverlaySelectionRecord *record = GetOverlaySelectionRecord_0204f768(0);
    TaggedEntry *entry;

    if (FindTaggedEntry_0204f6a4(&record->taggedEntries, id) != NULL) {
        return;
    }
    entry = AddTaggedEntry_0204fe2c(&record->taggedEntries, id, 0, 0);
    data_02060940[data_020608c8[1]] = entry;
    data_020608c8[1]++;
}
