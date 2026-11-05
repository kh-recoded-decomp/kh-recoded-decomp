#include "nitro/types.h"

extern s32 g_stageEventsState;
extern s32 StartStageEventInstance(s32 eventIndex, s32 first, s32 second, u16 *outResult);

s32 StartStageEventInstanceIfActive(s32 eventIndex, s32 first, s32 second, u16 *outResult)
{
    if (g_stageEventsState != -1) {
        return StartStageEventInstance(eventIndex, first, second, outResult);
    }
    return 0;
}
