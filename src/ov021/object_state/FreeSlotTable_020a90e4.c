#include "nitro/types.h"

typedef struct SlotRecord {
    u8 pad00[0x2c];
} SlotRecord;

typedef struct SlotTable {
    SlotRecord *records;
    s32 count;
    s8 *ids;
} SlotTable;

extern void ReleaseSharedRecordState_020a9084(SlotRecord *record);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);

void FreeSlotTable_020a90e4(SlotTable *table)
{
    int i;

    if (table->count > 0) {
        for (i = 0; i < table->count; i++) {
            if (table->ids[i] >= 0) {
                ReleaseSharedRecordState_020a9084(&table->records[i]);
            }
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(table->records);
        table->count = 0;
        NNSi_FndFreeFromDefaultHeap_0202a1c4(table->ids);
    }
}
