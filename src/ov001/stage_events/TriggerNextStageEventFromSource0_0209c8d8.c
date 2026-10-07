#include "nitro/types.h"

extern u16 TriggerNextStageEvent_0209947c(u32 source, u32 param, u32 extra, u16 *outResult);

u16 TriggerNextStageEventFromSource0_0209c8d8(u32 param, u32 extra, u16 *outResult)
{
    return TriggerNextStageEvent_0209947c(0, param, extra, outResult);
}
