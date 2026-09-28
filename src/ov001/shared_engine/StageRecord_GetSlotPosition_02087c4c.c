#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void *GetStageEventRecord_0209c0ec(u32 id);
extern BOOL func_ov001_0209661c(void *record, u32 slot, void *outPoint);

BOOL StageRecord_GetSlotPosition_02087c4c(u32 id, u32 slot, void *outPoint)
{
    void *record;

    if (g_stageEventsState_0209f2c8 != -1 && (record = GetStageEventRecord_0209c0ec(id)) != NULL) {
        return func_ov001_0209661c(record, slot, outPoint);
    }
    return FALSE;
}
