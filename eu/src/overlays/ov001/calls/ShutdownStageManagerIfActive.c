#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void ShutdownStageManager(void);

void ShutdownStageManagerIfActive(void)
{
    if (g_stageEventsState != -1) {
        ShutdownStageManager();
    }
}
