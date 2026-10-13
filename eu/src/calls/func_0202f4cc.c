/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
#include "nitro/types.h"

typedef struct AnimationResourceHeader {
    u32 signature;
    u16 frameCount;
} AnimationResourceHeader;

typedef struct BoundAnimation {
    u8 reserved00[8];
    AnimationResourceHeader *resource;
} BoundAnimation;

extern u32 func_01ffb2d4(u16 *state, int index);

int func_0202f4cc(u16 *state, int index)
{
    BoundAnimation *animation = (BoundAnimation *)func_01ffb2d4(state, index);

    if (animation != NULL) {
        return animation->resource->frameCount << 12;
    }
    return 0;
}
