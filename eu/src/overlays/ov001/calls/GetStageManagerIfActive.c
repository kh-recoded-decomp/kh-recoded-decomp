#include "nitro/types.h"

extern s32 g_stageEventsState;
extern u32 GetStageManager(void);

u32 GetStageManagerIfActive(void)
{
    if (g_stageEventsState != -1) {
        return GetStageManager();
    }
    return 0;
}
