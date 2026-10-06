#include "nitro/types.h"

extern u32 SuspendTaskAndSetFlag();
extern u32 StartIdleSceneObjects();
extern u32 func_ov001_0206685c();
extern u32 WakeNearbyIdleNodes();

u32 func_ov001_02065b8c(void) {
    s32 result;

    WakeNearbyIdleNodes(0);
    result = func_ov001_0206685c();
    if (result != 0) {
        return 0;
    }
    StartIdleSceneObjects();
    SuspendTaskAndSetFlag();
    return 1;
}
