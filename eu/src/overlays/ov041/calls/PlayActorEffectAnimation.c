#include "nitro/types.h"

typedef struct {
    s8 bodyTrack;
    s8 effectTrack;
} AnimTrackEntry;

typedef struct {
    u8 kind;
} AnimActor;

typedef struct {
    u8 pad_000[0x14];
    u8 anim[0xd8];
    u8 blendTarget[0x11c];
    volatile u8 dirtyFlags;
} EffectObject;

typedef struct {
    u8 pad_000[0x34c];
    EffectObject *effects[2];
} StageWork;

extern u8 *gMovieContextState;
extern AnimTrackEntry data_ov041_020cf61c[][24];
extern void selectJointAnimationBlend(void *state, int joint, void *target, s16 track);

void PlayActorEffectAnimation(AnimActor *actor, int animId) {
    StageWork *work = *(StageWork **)(gMovieContextState + 0xb8);
    int track;
    EffectObject *effect;

    switch (actor->kind) {
    case 0xff:
        track = data_ov041_020cf61c[0xff - actor->kind][animId].effectTrack;
        effect = work->effects[0];
        break;
    case 0xfd:
        track = data_ov041_020cf61c[0xff - actor->kind][animId].effectTrack;
        effect = work->effects[1];
        break;
    default:
        return;
    }
    if (track >= 0) {
        selectJointAnimationBlend(effect->anim, 0, effect->blendTarget, track);
        selectJointAnimationBlend(effect->anim, 1, effect->blendTarget, track);
        selectJointAnimationBlend(effect->anim, 2, effect->blendTarget, track);
        effect->dirtyFlags |= 1;
        effect->dirtyFlags |= 2;
    }
}
