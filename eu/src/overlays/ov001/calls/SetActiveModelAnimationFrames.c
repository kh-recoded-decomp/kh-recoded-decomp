#include "src/animation/ModelAnimation.h"

void SetActiveModelAnimationFrames(void *state, u32 frame)
{
    u8 *base = state;
    u32 slot = 0;
    do {
        if (*(s16 *)(base + (slot & 0xffff) * 2 + 0xd8) > 0) {
            SetModelAnimationFrameWithSingleWrap(state, slot & 0xffff, frame);
        }
        slot = slot + 1;
    } while ((int)slot < 5);
}
