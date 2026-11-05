#include "nitro/types.h"

extern void ResetSceneModelState(void);
extern void SetEntityModeEnabled(u32 target, s32 type, s32 subType);

void SetEntityModeWithSceneReset(u32 target, s32 type, s32 subType)
{
    if (type == 2 && subType == 0) {
        ResetSceneModelState();
    }
    SetEntityModeEnabled(target, type, subType);
}
