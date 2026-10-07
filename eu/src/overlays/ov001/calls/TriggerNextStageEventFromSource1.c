#include "nitro/types.h"

extern u16 TriggerNextStageEvent(u32 source, u32 param, u32 extra, u16 *outResult);

u16 TriggerNextStageEventFromSource1(u32 param, u32 extra, u16 *outResult)
{
    return TriggerNextStageEvent(1, param, extra, outResult);
}
