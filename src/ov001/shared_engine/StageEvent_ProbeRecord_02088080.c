#include "nitro/types.h"

extern u8 *GetStageEventRecord_0209c0ec(u32 id);

void StageEvent_ProbeRecord_02088080(u32 id)
{
    u8 *record = GetStageEventRecord_0209c0ec(id);

    if (record == NULL) {
        return;
    }
}
