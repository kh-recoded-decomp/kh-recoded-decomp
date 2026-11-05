#include "nitro/types.h"

extern u32 SuspendTaskAndSetFlag();
extern u32 StartIdleSceneObjects();
extern u32 HasActiveFieldEffects();
extern u32 WakeNearbyIdleNodes();

u32 ScriptCmd_WaitForFieldEffectsThenSuspend(void) {
    s32 result;

    WakeNearbyIdleNodes(0);
    result = HasActiveFieldEffects();
    if (result != 0) {
        return 0;
    }
    StartIdleSceneObjects();
    SuspendTaskAndSetFlag();
    return 1;
}
