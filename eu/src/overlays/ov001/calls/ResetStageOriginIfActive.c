#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ResetStageOrigin(void);

void ResetStageOriginIfActive(void)
{
    if (g_stageEventsState != -1) {
        ResetStageOrigin();
    }
}
