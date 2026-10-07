#include "nitro/types.h"

extern s32 g_stageEventsState;
extern void func_ov001_0209c440(void);

void ClearStageManagerFlags31IfActive(void)
{
    if (g_stageEventsState != -1) {
        func_ov001_0209c440();
    }
}
