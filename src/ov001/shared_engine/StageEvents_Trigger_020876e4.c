#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void func_ov001_0209a174(u32 eventIndex, int param);

void StageEvents_Trigger_020876e4(u32 eventIndex, int param)
{
    if (g_stageEventsState_0209f2c8 != -1) {
        func_ov001_0209a174(eventIndex, param);
    }
}
