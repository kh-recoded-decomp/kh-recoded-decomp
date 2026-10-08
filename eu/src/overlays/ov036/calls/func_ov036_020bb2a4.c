#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x24];
    u16 active;
    u8 pad_26[0x2E];
} ScreenLayer;

typedef struct ActorSlot {
    u8 pad_00[0x88];
    u16 active;
    u8 pad_8A[0x12];
} ActorSlot;

typedef struct AnimationBindingState {
    s16 flags;
    s16 selectedAnimationIndices[5];
    void *boundAnimations[5];
} AnimationBindingState;

typedef struct AnimationBlendTable {
    s16 animationCounts[5];
    u8 pad_0A[0x6];
    void **animationChoices[5];
} AnimationBlendTable;

typedef struct PanelModel {
    u8 pad_00[0x20];
    s32 pendingEvents;
    AnimationBindingState anim;
    u8 pad_44[0x54];
    s32 enabled;
    u8 pad_9C[0x60];
    AnimationBlendTable blend;
    u8 pad_120[0xC];
    s32 groupHandle;
    s32 blendIndex;
    s32 loopBlends;
} PanelModel;

typedef struct PanelWork {
    u8 pad_0000[0xC80];
    s32 forceAdvance;
    u8 pad_0C84[0x40C];
    ActorSlot *actorSlots;
    PanelModel *models;
    ScreenLayer *layers;
    u8 pad_109C[0x3C];
    s32 exitRequested;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;
extern void AdvanceSlotTransition(void);
extern void UpdateScreenLayer(int layerIndex);
extern void func_ov036_020bb564(int slotIndex);
extern void StepSceneModelMove(PanelModel *model);
extern void ReleaseModelSlot(s32 groupHandle, int force);
extern u16 AdvanceAnimationTracks(AnimationBindingState *state, s32 delta);
extern u32 BuildSlotMask(AnimationBindingState *state, s32 offset);
extern void selectJointAnimationBlend(AnimationBindingState *state, u16 trackIndex, AnimationBlendTable *blendTable, s16 blendIndex);

void func_ov036_020bb2a4(void)
{
    BOOL advance;
    PanelModel *model;
    int i;
    PanelWork *work = data_ov036_020c3940.work;

    if (work->exitRequested != 0) {
        AdvanceSlotTransition();
        return;
    }
    for (i = 0; i < 2; i++) {
        if (work->layers[i].active != 0) {
            UpdateScreenLayer(i);
        }
    }
    for (i = 0; i < 8; i++) {
        if (work->actorSlots[i].active != 0) {
            func_ov036_020bb564(i);
        }
    }
    for (i = 0; i < 5; i++) {
        model = &work->models[i];
        if (model->enabled != 0) {
            if (model->pendingEvents > 0) {
                StepSceneModelMove(model);
            }
            AdvanceAnimationTracks(&model->anim, 0x1000);
            if (BuildSlotMask(&model->anim, 0x1000) != 0 || work->forceAdvance != 0) {
                advance = FALSE;
                if (model->loopBlends != 0) {
                    if (model->blendIndex < model->blend.animationCounts[0] - 1) {
                        advance = TRUE;
                    } else {
                        ReleaseModelSlot(model->groupHandle, advance);
                    }
                } else if (model->blendIndex == 0 && model->blend.animationCounts[0] > 1) {
                    advance = TRUE;
                }
                if (advance) {
                    int track;
                    model->blendIndex++;
                    for (track = 0; track < 5; track++) {
                        if (model->blendIndex < model->blend.animationCounts[track]) {
                            selectJointAnimationBlend(&model->anim, track, &model->blend, model->blendIndex);
                        }
                    }
                }
            }
        }
    }
}
