#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

struct Actor {
    u8 pad_0000[0x768];
    BOOL animationEnded;
    u8 pad_076C[0x970 - 0x76c];
    VecFx32 velocity;
    u8 pad_097C[0x1808 - 0x97c];
    ActorChangeStateFunc changeState;
};

extern void Actor_ExtendCountdown_020c89fc(Actor *actor, fx32 duration);
extern void func_ov059_020c997c(Actor *actor);

void Actor_UpdateState14_020ca754(Actor *actor)
{
    Actor_ExtendCountdown_020c89fc(actor, 0x6000);
    func_ov059_020c997c(actor);
    if (actor->velocity.y < 0) {
        actor->velocity.y = 0;
    }
    if (actor->animationEnded) {
        actor->changeState(actor, 3);
    }
}
