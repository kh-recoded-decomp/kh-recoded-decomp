#include "nitro/types.h"

typedef struct StageRecord {
    u8 pad_00[0x70];
    s32 hitPoints;
} StageRecord;

extern int g_stageEventsState_0209f2c8;
extern StageRecord *GetStageEventRecord_0209c0ec(u32 id);

BOOL StageRecord_IsDefeated_02087cc4(u32 id)
{
    StageRecord *record;

    if (g_stageEventsState_0209f2c8 != -1 && (record = GetStageEventRecord_0209c0ec(id)) != NULL) {
        if (record->hitPoints == 0) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}
