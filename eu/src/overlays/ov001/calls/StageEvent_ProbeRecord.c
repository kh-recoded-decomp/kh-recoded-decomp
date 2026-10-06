#include "nitro/types.h"

extern u8 *GetStageEventRecord(u32 id);

void StageEvent_ProbeRecord(u32 id)
{
    u8 *record = GetStageEventRecord(id);

    if (record == NULL) {
        return;
    }
}
