#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ClearStageManagerFlags42(void);

void ClearStageManagerFlags42IfActive(void)
{
    if (g_stageEventsState != -1) {
        ClearStageManagerFlags42();
    }
}
