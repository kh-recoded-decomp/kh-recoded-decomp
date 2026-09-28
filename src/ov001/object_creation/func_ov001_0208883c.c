#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x764];
    s32 actorCount;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;

BOOL func_ov001_0208883c(void)
{
    if (g_actorManager_020a04e0->actorCount != 0) {
        return TRUE;
    }
    return FALSE;
}
