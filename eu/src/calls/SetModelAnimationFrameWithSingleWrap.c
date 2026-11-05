/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
#include "src/animation/ModelAnimation.h"

ModelAnimationTrackState *SetModelAnimationFrameWithSingleWrap(const void *state,
                                                              int index, fx32 frame)
{
    ModelAnimationTrackState *track = GetModelAnimationTrackState(state, index);
    if (track != NULL) {
        int duration;
        track->frame = frame;
        duration = (int)track->resource->frameCount << 12;
        if (frame >= duration) {
            track->frame = frame - duration;
        }
    }
    return track;
}
