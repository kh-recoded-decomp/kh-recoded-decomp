#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x3F1C];
    u32 field_3f1c;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;

u32 func_ov001_02088960(void)
{
    return g_actorManager_020a04e0->field_3f1c;
}
