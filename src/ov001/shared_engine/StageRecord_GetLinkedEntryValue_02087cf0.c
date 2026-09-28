#include "nitro/types.h"

typedef struct StageRecord {
    u8 pad_00[0x1a];
    u16 linkedEntryIndex;
} StageRecord;

typedef struct LinkedEntry {
    u8 pad_00[0x8];
    s16 value;
} LinkedEntry;

extern int g_stageEventsState_0209f2c8;
extern StageRecord *GetStageEventRecord_0209c0ec(u32 id);
extern LinkedEntry *GetSmallTableEntry_0209c340(int index);

int StageRecord_GetLinkedEntryValue_02087cf0(u32 id)
{
    StageRecord *record;
    LinkedEntry *entry;

    if (g_stageEventsState_0209f2c8 != -1 && (record = GetStageEventRecord_0209c0ec(id)) != NULL &&
        record->linkedEntryIndex != 0xffff &&
        (entry = GetSmallTableEntry_0209c340(record->linkedEntryIndex)) != NULL) {
        return entry->value;
    }
    return 0;
}
