#include "nitro/types.h"

extern int gResumeModeTaskHandle;
extern u32 Obj_GetWord28(u32 argument0);

BOOL HasResumeModeTaskExitSignal(void)
{
    return Obj_GetWord28(gResumeModeTaskHandle) != 0;
}
