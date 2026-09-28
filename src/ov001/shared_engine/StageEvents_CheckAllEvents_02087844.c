#include "nitro/types.h"

extern int g_stageEventsState_0209f2c8;
extern BOOL func_ov001_0209c5c8(u16 eventIndex, s16 filterId, int flags);

BOOL StageEvents_CheckAllEvents_02087844(s16 filterId)
{
    if (g_stageEventsState_0209f2c8 != -1) {
        return func_ov001_0209c5c8(0xFFFF, filterId, 1);
    }
    return FALSE;
}
