#include "nitro/types.h"

typedef struct ActorAnimationState {
    u8 reserved00[0x894];
    u8 animState[0x660];
    u32 flags;
} ActorAnimationState;

extern void BindActorAnimation(void *animState, const char *name, int blendIndex);

void StartActorAnimState(ActorAnimationState *actor, const char *name, int blendIndex)
{
    BindActorAnimation(actor->animState, name, blendIndex);
    actor->flags |= 0x180;
}
