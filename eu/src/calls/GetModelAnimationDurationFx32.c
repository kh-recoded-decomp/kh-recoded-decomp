/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
#include "src/animation/ModelAnimation.h"

fx32 GetModelAnimationDurationFx32(const void *state, int index)
{
    ModelAnimationTrackState *track = GetModelAnimationTrackState(state, index);
    if (track != NULL) {
        return track->resource->frameCount << 12;
    }
    return 0;
}
