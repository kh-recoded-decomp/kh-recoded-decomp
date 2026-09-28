#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void func_ov001_0209b644(int eventIndex);

void StageEvent_SetHoldBit2_02087db8(int eventIndex)
{
    if (g_stageEventsState_0209f2c8 != -1) {
        func_ov001_0209b644(eventIndex);
    }
}
