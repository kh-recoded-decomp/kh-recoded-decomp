#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern void func_ov001_0209b5b8(int eventIndex);

void StageEvent_ReleaseHoldBit1_020876fc(int eventIndex)
{
    if (g_stageEventsState_0209f2c8 != -1) {
        func_ov001_0209b5b8(eventIndex);
    }
}
