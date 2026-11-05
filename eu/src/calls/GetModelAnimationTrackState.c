#include "src/animation/ModelAnimation.h"

ModelAnimationTrackState *GetModelAnimationTrackState(const void *state, int index)
{
    const u8 *base = state;
    if ((*(const u16 *)base & 4) != 0 && index == 0) {
        return *(ModelAnimationTrackState *const *)(base + 0xcc);
    }
    return *(ModelAnimationTrackState *const *)(base + index * 4 + 0xc);
}
