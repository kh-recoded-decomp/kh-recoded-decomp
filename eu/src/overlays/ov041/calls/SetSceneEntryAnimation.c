#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x14];
    u8 animState[0xd8];
    u8 blendTable[4];
} LinkedObject;

typedef struct {
    u8 kind;
    u8 pad_001[7];
    u32 flags;
    u8 pad_00c[0x114];
    u32 frame;
    u8 animIndex;
    u8 pad_125[0x4b];
    u8 animState[0xd8];
    u8 blendTable[0xec];
    LinkedObject *linkedObject;
} SceneEntry;

typedef struct {
    u8 pad_000[0x10c];
    u8 animState[0xd8];
    u8 blendTable[4];
} Work;

extern int data_ov035_020bc4e0;
extern BOOL MatchesEitherSlotId(SceneEntry *entry, int anim);
extern void SetStageActorFrame(SceneEntry *entry, int flag);
extern void selectJointAnimationBlend(void *state, int track, void *table, int blendIndex);
extern void BlendToAnimationTrack(void *state, int track, void *table, int blendIndex, int frameCount);
extern void PlayActorAnimation(SceneEntry *entry, int anim);
extern void SetAnimationFrameIfChanged(SceneEntry *entry, int frame);
extern void func_ov041_020c28ac(SceneEntry *entry, int anim);

void SetSceneEntryAnimation(SceneEntry *entry, int anim, int blend, int reset) {
    Work *work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    LinkedObject *linked;

    if (MatchesEitherSlotId(entry, anim)) {
        if (reset) {
            SetStageActorFrame(entry, 0);
        }
        return;
    }
    if (anim == 0xff) {
        return;
    }
    if (blend) {
        BlendToAnimationTrack(entry->animState, 0, entry->blendTable, anim, 5);
        if (entry->kind == 0xff) {
            BlendToAnimationTrack(work->animState, 0, work->blendTable, anim, 5);
        }
    } else {
        selectJointAnimationBlend(entry->animState, 0, entry->blendTable, anim);
        if (entry->kind == 0xff) {
            selectJointAnimationBlend(work->animState, 0, work->blendTable, anim);
        }
    }
    PlayActorAnimation(entry, anim);
    SetAnimationFrameIfChanged(entry, 0);
    func_ov041_020c28ac(entry, anim);
    linked = entry->linkedObject;
    if (linked != NULL) {
        if (blend) {
            BlendToAnimationTrack(linked->animState, 0, linked->blendTable, anim, 5);
        } else {
            selectJointAnimationBlend(linked->animState, 0, linked->blendTable, anim);
        }
    }
    entry->animIndex = anim;
    entry->frame = 0;
    entry->flags |= 2;
}
