#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x95C];
    void *actorSlots[0x200];
    u8 partyMembers[3][0xF2C];
} ActorManager;

extern ActorManager *g_actorManager_020a04e0;
extern void func_01ff8830(void *dst, int val, u32 size);
extern void func_0202a1c4(void *block);
extern void func_ov001_02089f1c(void *actor);
extern void func_ov001_0208a8b8(void *actor, s32 flag);

void func_ov001_020888dc(void)
{
    s32 index;
    void *actor;

    index = 0;
    do {
        actor = g_actorManager_020a04e0->actorSlots[index];
        if (actor != 0) {
            func_ov001_0208a8b8(actor, 0);
            func_ov001_02089f1c(g_actorManager_020a04e0->actorSlots[index]);
            func_0202a1c4(g_actorManager_020a04e0->actorSlots[index]);
            g_actorManager_020a04e0->actorSlots[index] = 0;
        }
        index = index + 1;
    } while (index < 0x200);
    index = 0;
    do {
        func_ov001_02089f1c(g_actorManager_020a04e0->partyMembers[index]);
        index = index + 1;
    } while (index < 3);
    func_01ff8830(g_actorManager_020a04e0->partyMembers[0], 0, 0x2D84);
}
