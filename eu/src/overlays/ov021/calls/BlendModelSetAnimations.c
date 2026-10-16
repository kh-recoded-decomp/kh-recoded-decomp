#include "src/overlays/ov021/AnimationTrackOrder.h"

typedef struct AnimationFadeState AnimationFadeState;
typedef struct AnimationBlendTable AnimationBlendTable;

typedef struct AnimatedModelSet {
    u32 flags;
    s32 hasSub;
    u8 animationState[0x10c - 8];
    AnimationBlendTable *selectedTable;
    u8 unknown110[0x228 - 0x110];
    AnimationFadeState *sub;
} AnimatedModelSet;

typedef char ModelHasSubOffset[(u32)&((AnimatedModelSet *)0)->hasSub == 4 ? 1 : -1];
typedef char ModelAnimationStateOffset[(u32)&((AnimatedModelSet *)0)->animationState == 8 ? 1 : -1];
typedef char ModelSelectedTableOffset[(u32)&((AnimatedModelSet *)0)->selectedTable == 0x10c ? 1 : -1];
typedef char ModelSubStateOffset[(u32)&((AnimatedModelSet *)0)->sub == 0x228 ? 1 : -1];

extern void BlendToAnimationTrack(AnimationFadeState *state, u16 track,
                                  AnimationBlendTable *table, s16 index,
                                  int frameCount);

static inline void BlendPrimaryAnimations(AnimatedModelSet *model,
                                          AnimationBlendTable *table,
                                          int index, int frameCount)
{
    if (table != NULL) {
        int i = 0;
        AnimationTrackOrder order = kPrimaryModelTrackOrder;
        for (; i < 5; ++i) {
            if ((model->flags & 4) || model->hasSub != 0) {
                BlendToAnimationTrack((AnimationFadeState *)model->animationState,
                                      order.tracks[i], model->selectedTable,
                                      index, frameCount);
            }
        }
    }
}

static inline void BlendSecondaryAnimations(AnimatedModelSet *model,
                                            AnimationFadeState *state,
                                            AnimationBlendTable *table,
                                            int frameCount)
{
    if (table != NULL) {
        int i = 0;
        AnimationTrackOrder order = kSecondaryModelTrackOrder;
        for (; i < 5; ++i) {
            if ((model->flags & 4) || model->hasSub != 0) {
                BlendToAnimationTrack(state, order.tracks[i], table, 0, frameCount);
            }
        }
        model->flags |= 0x400;
    }
}

/* Blend the primary tracks and, when enabled, the secondary animation state. */
void BlendModelSetAnimations(AnimatedModelSet *model, AnimationBlendTable *table,
                              int index, AnimationBlendTable *subTable,
                              int frameCount)
{
    if (!(model->flags & 1)) {
        return;
    }
    model->selectedTable = table;
    BlendPrimaryAnimations(model, table, index, frameCount);
    AnimationFadeState *sub = model->sub;
    if (sub != NULL && model->hasSub != 0 && subTable != NULL) {
        BlendSecondaryAnimations(model, sub, subTable, frameCount);
    }
}
