#include "nitro/types.h"

typedef struct LinkEntry {
    s16 recordId;
    s16 valueIndex;
    u8 pad04[8];
} LinkEntry;

typedef struct LinkTable {
    LinkEntry entries[16];
    u32 values[16];
    int count;
} LinkTable;

typedef struct SlotRecord {
    u8 pad00[0x10];
    int state;
    u8 pad14[8];
    u16 baseValue;
} SlotRecord;

u8 *func_0204f768(u32 selectionIndex);
BOOL AcquireRecordManager_02051c80(void);
void ReleaseRecordManager_02051cdc(void);
int AcquireRecordSlot_02051d3c(int slot, int param);
BOOL ReleaseRecordSlot_02051dfc(s32 slot);
SlotRecord *GetRecordSlotPair1Entry_02051ef4(s32 index);

void RefreshSelectionLinkValues_0204fb1c(void)
{
    LinkTable *table;
    int i = 0;
    table = (LinkTable *)(func_0204f768(i) + 0x2c);

    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(1, 1);
    for (; i < table->count; i++) {
        LinkEntry *entry = &table->entries[i];
        SlotRecord *record = GetRecordSlotPair1Entry_02051ef4(entry->recordId);
        /* State 3 records are skipped */
        if (record != NULL && record->state != 3)
            table->values[entry->valueIndex] = record->baseValue * 2;
    }
    ReleaseRecordSlot_02051dfc(1);
    ReleaseRecordManager_02051cdc();
}

