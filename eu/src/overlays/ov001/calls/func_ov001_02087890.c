#include "nitro/types.h"

extern s32 g_stageEventsState;
extern s32 QueryStageEventState(s32 mode, s32 filterId);

s32 func_ov001_02087890(s32 mode)
{
    if (g_stageEventsState != -1) {
        return QueryStageEventState(mode, -1);
    }
    return 0;
}
