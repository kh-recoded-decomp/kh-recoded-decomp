#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void func_ov001_0209b638(int eventIndex);

void StageEvent_SetHoldBit1_02087da0(int eventIndex)
{
    if (g_stageEventsState_0209f2c8 != -1) {
        func_ov001_0209b638(eventIndex);
    }
}
