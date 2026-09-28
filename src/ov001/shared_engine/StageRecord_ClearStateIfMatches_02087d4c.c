#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void *GetStageEventRecord_0209c0ec(u32 id);
extern void func_ov001_020958e4(void *record, u32 state);

void StageRecord_ClearStateIfMatches_02087d4c(u32 id, u32 state)
{
    void *record;

    if (id != 0 && g_stageEventsState_0209f2c8 != -1 && (record = GetStageEventRecord_0209c0ec(id)) != NULL) {
        func_ov001_020958e4(record, state);
    }
}
