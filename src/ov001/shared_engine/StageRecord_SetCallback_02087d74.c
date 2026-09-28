#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void *GetStageEventRecord_0209c0ec(u32 id);
extern void SetActorCallbackPair_020958d0(void *record, u32 callback, u32 userData);

void StageRecord_SetCallback_02087d74(u32 id, u32 callback, u32 userData)
{
    void *record;

    if (id != 0 && g_stageEventsState_0209f2c8 != -1 && (record = GetStageEventRecord_0209c0ec(id)) != NULL) {
        SetActorCallbackPair_020958d0(record, callback, userData);
    }
}
