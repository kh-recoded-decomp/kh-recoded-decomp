#include "src/overlays/ov040/Ov040RewardAnimationState.h"

void *GetFallbackActorAnimation(void)
{
    return gOv040RewardAnimationState->group->animationData + 8;
}
