#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ResetStageLinksForSession(void);

void ResetStageLinksForSessionIfActive(void)
{
    if (g_stageEventsState != -1) {
        ResetStageLinksForSession();
    }
}
