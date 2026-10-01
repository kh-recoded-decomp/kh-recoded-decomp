#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

struct Actor {
    u8 pad_0000[0x234];
    u32 collisionFlags;
    u8 pad_0238[0x768 - 0x238];
    BOOL animationEnded;
    u8 pad_076C[0x928 - 0x76c];
    u64 stateFlags;
    u8 pad_0930[0x970 - 0x930];
    VecFx32 velocity;
    u8 pad_097C[0x1808 - 0x97c];
    ActorChangeStateFunc changeState;
};

extern const VecFx32 data_02053438;
extern void func_ov059_020c997c(Actor *actor);

void Actor_UpdateHaltedState_020ca5f0(Actor *actor)
{
    actor->velocity = data_02053438;
    func_ov059_020c997c(actor);
    if (actor->stateFlags & 8) {
        actor->changeState(actor, 6);
        return;
    }
    if (!(actor->collisionFlags & 4)) {
        actor->changeState(actor, 3);
        return;
    }
    if (actor->animationEnded) {
        actor->changeState(actor, 1);
    }
}
