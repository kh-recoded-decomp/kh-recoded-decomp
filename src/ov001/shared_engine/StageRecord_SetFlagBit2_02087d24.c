#include "nitro/types.h"

typedef struct StageRecord {
    u8 pad_00[0x4];
    u16 flags;
} StageRecord;

extern int g_stageEventsState_0209f2c8;
extern StageRecord *GetStageEventRecord_0209c0ec(u32 id);

void StageRecord_SetFlagBit2_02087d24(u32 id)
{
    StageRecord *record;

    if (id != 0 && g_stageEventsState_0209f2c8 != -1 && (record = GetStageEventRecord_0209c0ec(id)) != NULL) {
        record->flags |= 4;
    }
}
