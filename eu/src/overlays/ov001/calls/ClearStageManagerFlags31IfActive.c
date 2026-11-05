#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ClearStageManagerFlags31(void);

void ClearStageManagerFlags31IfActive(void)
{
    if (g_stageEventsState != -1) {
        ClearStageManagerFlags31();
    }
}
