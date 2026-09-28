#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x95C];
    void *actorSlots[0x200];
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern s32 func_ov001_0208a334(void);
extern void func_ov001_0208a114(void *actor);

void func_ov001_02088568(void)
{
    s32 index;
    s32 hasFlag;

    index = 0;
    do {
        if (g_actorManager_020a04e0->actorSlots[index] != 0 &&
            (hasFlag = func_ov001_0208a334(), hasFlag != 0)) {
            func_ov001_0208a114(g_actorManager_020a04e0->actorSlots[index]);
        }
        index = index + 1;
    } while (index < 0x200);
}
