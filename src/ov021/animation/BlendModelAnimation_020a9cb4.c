#include "nitro/types.h"

typedef struct AnimatedModel {
    u32 flags;
    s32 timer;
    u8 fadeState[1];
} AnimatedModel;

extern void BlendToAnimationTrack_0202f374(void *state, u16 trackIndex, void *table, s16 blendIndex, int frameCount);

void BlendModelAnimation_020a9cb4(AnimatedModel *model, void *table, int trackIndex, int blendIndex, int frameCount)
{
    if (model->flags & 1) {
        BlendToAnimationTrack_0202f374(model->fadeState, trackIndex, table, blendIndex, frameCount);
        model->timer = 0;
        model->flags &= ~0x400;
    }
}
