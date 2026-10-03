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
extern BOOL func_ov041_020c2a04(SceneEntry *entry, int anim);
extern void func_ov041_020c2928(SceneEntry *entry, int flag);
extern void selectJointAnimationBlend_0202f2cc(void *state, int track, void *table, int blendIndex);
extern void BlendToAnimationTrack_0202f374(void *state, int track, void *table, int blendIndex, int frameCount);
extern void func_ov041_020c37f4(SceneEntry *entry, int anim);
extern void SetAnimationFrameIfChanged_020c389c(SceneEntry *entry, int frame);
extern void func_ov041_020c288c(SceneEntry *entry, int anim);

void SetSceneEntryAnimation_020c278c(SceneEntry *entry, int anim, int blend, int reset) {
    Work *work = *(Work **)(data_ov035_020bc4e0 + 0xb8);
    LinkedObject *linked;

    if (func_ov041_020c2a04(entry, anim)) {
        if (reset) {
            func_ov041_020c2928(entry, 0);
        }
        return;
    }
    if (anim == 0xff) {
        return;
    }
    if (blend) {
        BlendToAnimationTrack_0202f374(entry->animState, 0, entry->blendTable, anim, 5);
        if (entry->kind == 0xff) {
            BlendToAnimationTrack_0202f374(work->animState, 0, work->blendTable, anim, 5);
        }
    } else {
        selectJointAnimationBlend_0202f2cc(entry->animState, 0, entry->blendTable, anim);
        if (entry->kind == 0xff) {
            selectJointAnimationBlend_0202f2cc(work->animState, 0, work->blendTable, anim);
        }
    }
    func_ov041_020c37f4(entry, anim);
    SetAnimationFrameIfChanged_020c389c(entry, 0);
    func_ov041_020c288c(entry, anim);
    linked = entry->linkedObject;
    if (linked != NULL) {
        if (blend) {
            BlendToAnimationTrack_0202f374(linked->animState, 0, linked->blendTable, anim, 5);
        } else {
            selectJointAnimationBlend_0202f2cc(linked->animState, 0, linked->blendTable, anim);
        }
    }
    entry->animIndex = anim;
    entry->frame = 0;
    entry->flags |= 2;
}
