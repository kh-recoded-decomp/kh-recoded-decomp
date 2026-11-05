#include "nitro/types.h"

extern int data_ov033_020baaa0;
extern u32 Obj_GetWord28(u32 argument0);

BOOL HasResumeModeTaskExitSignal(void)
{
    return Obj_GetWord28(data_ov033_020baaa0) != 0;
}
