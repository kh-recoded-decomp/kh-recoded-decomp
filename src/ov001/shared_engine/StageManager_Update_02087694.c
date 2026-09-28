#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void func_ov001_0209b950(u32 updateParam);

void StageManager_Update_02087694(u32 updateParam)
{
    if (g_stageEventsState_0209f2c8 != -1) {
        func_ov001_0209b950(updateParam);
    }
}
