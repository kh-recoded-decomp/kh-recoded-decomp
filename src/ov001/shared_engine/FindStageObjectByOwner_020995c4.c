#include "nitro/types.h"

typedef struct StageObjectRecord {
    u8 pad_000[0x110];
    u32 owner;
    u16 slotId;
    u8 pad_116[0x124 - 0x116];
} StageObjectRecord;

typedef struct StageManager {
    u8 pad_00000[0x214];
    StageObjectRecord records[1];
    u8 pad_00338[0x18dea - 0x338];
    u16 recordCount;
} StageManager;

extern StageManager *g_stageManager_020a0508;

u16 FindStageObjectByOwner_020995c4(u16 slot, u32 owner)
{
    u16 index;
    StageObjectRecord *record;

    for (index = 0; index < g_stageManager_020a0508->recordCount; index++) {
        record = &g_stageManager_020a0508->records[index];
        if (record->owner == owner && record->slotId == slot + 1) {
            return index + 1;
        }
    }
    return 0;
}
