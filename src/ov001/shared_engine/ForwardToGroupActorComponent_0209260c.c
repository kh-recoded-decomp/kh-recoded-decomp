#include "nitro/types.h"

typedef struct ActorGroupOwner {
    u8 pad_00[0x10];
    u16 groupId;
} ActorGroupOwner;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 component[1];
} StageActor;

extern StageActor *GetStageActor_0209c040(s16 groupId);
extern void func_ov021_020b4b9c(void *component, void *arg);

void ForwardToGroupActorComponent_0209260c(ActorGroupOwner *owner, void *arg)
{
    StageActor *actor;

    if (owner != NULL && owner->groupId != 0) {
        actor = GetStageActor_0209c040(owner->groupId);
        if (actor != NULL) {
            func_ov021_020b4b9c(actor->component, arg);
        }
    }
}
