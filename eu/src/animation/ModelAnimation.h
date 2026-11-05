#ifndef EU_MODEL_ANIMATION_H
#define EU_MODEL_ANIMATION_H

#include "nitro/fx_types.h"

/* Proven prefixes only; neither is a full resource/allocation definition. */
typedef struct ModelAnimationResourcePrefix {
    u32 reserved00;
    u16 frameCount;
} ModelAnimationResourcePrefix;

typedef struct ModelAnimationTrackState {
    fx32 frame;
    u32 reserved04;
    const ModelAnimationResourcePrefix *resource;
} ModelAnimationTrackState;

typedef char ModelAnimationResourceCountOffsetCheck[
    (u32)&((ModelAnimationResourcePrefix *)0)->frameCount == 4 ? 1 : -1];
typedef char ModelAnimationTrackResourceOffsetCheck[
    (u32)&((ModelAnimationTrackState *)0)->resource == 8 ? 1 : -1];

/* state is the animation-flags origin, which can be inside a larger model.
 * Returns a borrowed mutable track, or NULL for an unbound track.
 * The lookup does not validate the index or state pointer.
 */
ModelAnimationTrackState *GetModelAnimationTrackState(const void *state, int index);
ModelAnimationTrackState *SetModelAnimationFrameWithSingleWrap(const void *state,
                                                              int index, fx32 frame);
fx32 GetModelAnimationDurationFx32(const void *state, int index);

#endif
