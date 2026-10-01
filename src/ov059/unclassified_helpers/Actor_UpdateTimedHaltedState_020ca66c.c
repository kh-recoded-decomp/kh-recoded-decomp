#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

struct Actor {
    u8 pad_0000[0x234];
    u32 collisionFlags;
    u8 pad_0238[0x760 - 0x238];
    fx32 stateTimer;
    u8 pad_0764[0x768 - 0x764];
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
extern BOOL Actor_TryEnterState5_020ca700(Actor *actor);

void Actor_UpdateTimedHaltedState_020ca66c(Actor *actor)
{
    actor->velocity = data_02053438;
    func_ov059_020c997c(actor);
    if (!(actor->collisionFlags & 4)) {
        actor->changeState(actor, 3);
        return;
    }
    if (actor->stateFlags & 8) {
        actor->changeState(actor, 6);
        return;
    }
    if (actor->stateTimer >= 0x8000 && Actor_TryEnterState5_020ca700(actor)) {
        return;
    }
    if (actor->animationEnded) {
        actor->changeState(actor, 1);
    }
}
