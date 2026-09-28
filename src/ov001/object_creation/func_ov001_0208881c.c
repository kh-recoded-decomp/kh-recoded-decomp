#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x140];
    u8 pad_140[0x628];
    u32 field_768;
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern void func_02025cec(void *dst);

u32 func_ov001_0208881c(void)
{
    func_02025cec((u8 *)g_actorManager_020a04e0 + 0x140);
    return g_actorManager_020a04e0->field_768;
}
