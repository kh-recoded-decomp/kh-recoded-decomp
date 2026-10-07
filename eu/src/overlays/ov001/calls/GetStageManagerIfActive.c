#include "nitro/types.h"

extern s32 g_stageEventsState;
extern u32 func_ov001_0209c3e8(void);

u32 GetStageManagerIfActive(void)
{
    if (g_stageEventsState != -1) {
        return func_ov001_0209c3e8();
    }
    return 0;
}
