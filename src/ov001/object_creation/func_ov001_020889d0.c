#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x3F00];
    u32 field_3f00;
    u32 field_3f04;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;

void func_ov001_020889d0(u32 value1, u32 value2)
{
    g_actorManager_020a04e0->field_3f00 = value1;
    g_actorManager_020a04e0->field_3f04 = value2;
}
