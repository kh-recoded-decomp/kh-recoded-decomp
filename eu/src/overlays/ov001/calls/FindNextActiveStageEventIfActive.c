#include "nitro/types.h"

extern s32 g_stageEventsState;
extern s32 FindNextActiveStageEvent(s32 startIndex);

s32 FindNextActiveStageEventIfActive(s32 startIndex)
{
    if (g_stageEventsState != -1) {
        return FindNextActiveStageEvent(startIndex);
    }
    return 0;
}
