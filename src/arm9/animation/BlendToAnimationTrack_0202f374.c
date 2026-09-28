#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AnimationResource {
    u8 header[4];
    u16 frameCount;
} AnimationResource;

typedef struct AnimationObject {
    fx32 frame;
    fx32 ratio;
    AnimationResource *resource;
} AnimationObject;

typedef struct AnimationBlendTable {
    u16 animationCounts[5];
    u8 pad_0A[0x10 - 0x0A];
    AnimationObject **animationChoices[5];
} AnimationBlendTable;

typedef struct AnimationFadeState {
    u16 flags;
    s16 selectedIndices[5];
    AnimationObject *boundAnimations[5];
    u8 renderObject[0xca - 0x20];
    s16 pendingIndex;
    AnimationObject *pendingAnimation;
    fx32 outgoingWeight;
    fx32 incomingStep;
    AnimationBlendTable defaultTable;
} AnimationFadeState;

extern void CommitPendingAnimationSwap_0202f5c8(AnimationFadeState *state);
extern void selectJointAnimationBlend_0202f2cc(AnimationFadeState *state, u16 trackIndex, AnimationBlendTable *table, s16 blendIndex);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void AttachAnimationToRenderObject_0201875c(void *renderObject, AnimationObject *animation);

void BlendToAnimationTrack_0202f374(AnimationFadeState *state, u16 trackIndex, AnimationBlendTable *table, s16 blendIndex, int frameCount)
{
    AnimationObject *target;

    if (table == NULL) {
        table = &state->defaultTable;
    }
    if ((state->flags & 4) && trackIndex == 0) {
        CommitPendingAnimationSwap_0202f5c8(state);
    }
    if (frameCount == 0 || state->selectedIndices[trackIndex] < 0 || trackIndex != 0) {
        selectJointAnimationBlend_0202f2cc(state, trackIndex, table, blendIndex);
        return;
    }
    target = table->animationChoices[trackIndex][blendIndex];
    if (frameCount > (int)(target->resource->frameCount << 12) >> 12) {
        selectJointAnimationBlend_0202f2cc(state, trackIndex, table, blendIndex);
        return;
    }
    if (state->boundAnimations[trackIndex] == target) {
        return;
    }
    if (trackIndex != 0) {
        return;
    }
    state->pendingIndex = blendIndex;
    state->incomingStep = FX_Div_01ff9c84(0x1000, frameCount << 12);
    state->outgoingWeight = 0x1000 - state->incomingStep;
    state->pendingAnimation = table->animationChoices[trackIndex][blendIndex];
    state->pendingAnimation->frame = 0;
    AttachAnimationToRenderObject_0201875c(state->renderObject, state->pendingAnimation);
    state->boundAnimations[trackIndex]->ratio = state->outgoingWeight;
    state->pendingAnimation->ratio = 0x1000 - state->outgoingWeight;
    state->flags |= 4;
}
