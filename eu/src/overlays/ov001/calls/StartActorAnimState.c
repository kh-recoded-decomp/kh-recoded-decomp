#include "nitro/types.h"

typedef struct ActorAnimationState {
    u8 reserved00[0x894];
    u8 animState[0x660];
    u32 flags;
} ActorAnimationState;

extern void BindActorAnimation(void *animState, int animationId, int blendIndex);

void StartActorAnimState(ActorAnimationState *actor, int animationId, int blendIndex)
{
    BindActorAnimation(actor->animState, animationId, blendIndex);
    actor->flags |= 0x180;
}
