#include "nitro/types.h"

typedef struct AnimationFadeState AnimationFadeState;
typedef struct AnimationBlendTable AnimationBlendTable;

typedef struct ActorModel {
    u32 flags;
    u8 animationState[1];
} ActorModel;

typedef struct Actor {
    u8 pad_000[0x230];
    ActorModel *model;
    u8 pad_234[0x764 - 0x234];
    AnimationBlendTable *animationTable;
} Actor;

extern u32 GetField28_020bbff4(void);
extern void BlendToAnimationTrack_0202f374(AnimationFadeState *state, u16 trackIndex, AnimationBlendTable *table, s16 blendIndex, int frameCount);

void Actor_PlayAnimation_020c88c4(Actor *actor, AnimationBlendTable *table, int trackIndex, int blendIndex, int frameCount)
{
    if (blendIndex == 1 && GetField28_020bbff4() == 0) {
        blendIndex = 0;
    }
    if (table != actor->animationTable) {
        actor->animationTable = table;
    }
    BlendToAnimationTrack_0202f374((AnimationFadeState *)actor->model->animationState, trackIndex, actor->animationTable, blendIndex, frameCount);
}
