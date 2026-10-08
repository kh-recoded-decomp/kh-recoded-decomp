#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PartyEntry PartyEntry;

struct PartyEntry {
    u8 pad_000[0x1fc];
    void (*onEvent)(PartyEntry *entry, int arg);
    u8 pad_200[0x760 - 0x200];
    s32 animValue;
    u8 pad_764[0x9ac - 0x764];
    u64 flags;
    u8 pad_9b4[0xb2c - 0x9b4];
    u8 sound[4];
};

typedef struct {
    u8 pad_000[0x130];
    s32 active;
} EmitterRig;

typedef struct {
    s8 mode;
    u8 pad_01[3];
    s32 timer;
    u8 pad_08[0x20 - 0x8];
    u16 heading;
    u16 speed;
    s32 arrived;
    s32 landed;
    s32 soundPending;
    s32 finished;
    s32 finishArg;
    u8 pad_38[0x3c - 0x38];
    u8 model[0x174 - 0x3c];
    EmitterRig frontRig;
    EmitterRig rigs[3];
    EmitterRig backRig;
    u8 pad_778[0x7f8 - 0x778];
    s8 speedPhase;
    u8 pad_7f9[3];
    s32 speedTimer;
} SceneState;

extern SceneState data_ov058_020d8a24;

extern void PlaySoundChecked_0204d8d0(int id, int arg);
extern void StopSeqArcOrDefault_0204d960(int seqArcNo, int seqIndex, int fadeFrames);
extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern void *func_ov001_0206db78(int player);
extern BOOL UpdateIdleTimeout_0206e1c8(void);
extern s32 func_ov001_0206e6f4(s32 callerId);
extern void RunHudEnterCallback_02071fb4(void);
extern void RunHudExitCallback_02071fec(void);
extern BOOL func_ov001_02072040(void);
extern u16 GetId10_020a755c(void *self);
extern s32 GetFieldAt0x12_020a7560(void *obj);
extern BOOL RestartScriptSound_020a818c(void *sound, int soundId);
extern void SelectAnimationById_020ac8f4(void *selector, int id);
extern void TransitionState_020ac94c(void *obj, s32 value);
extern BOOL CameraPath_ConsumeSkipRequest_020c2fd4(void);
extern void SettleAnchorOnGround_020d7054(fx32 step);
extern void UpdateSceneCameraTransform_020d720c(BOOL force);
extern void UpdateBlastFadeSequence_020d72c4(fx32 delta);
extern void ClearStageEventsAndPlayerFlags_020d7404(SceneState *control);
extern void ResetEmitterRigOffset_020d75f8(EmitterRig *rig);
extern void RebindEmitterSlotsPhase3_020d7628(EmitterRig *rig);
extern void UpdateEffectSlotPhase_020d7640(EmitterRig *slot, int delta);
extern void ResetEmitterRigAndApply_020d7738(EmitterRig *rig, int arg);
extern void RebindEmitterSlotsPhase3_020d7764(EmitterRig *rig);
extern void UpdateHazardRig_020d777c(EmitterRig *rig, int index, fx32 step);
extern void RebindEmitterSlotsPhase1_020d78ec(EmitterRig *rig);
extern void UpdateRaisedModelAnimation_020d7904(EmitterRig *rig, fx32 step);
extern void PurgeNearbyStageObjects_020d7998(void);

void UpdateSceneIntroSequence_020d81a4(fx32 delta)
{
    SceneState *scene = &data_ov058_020d8a24;
    PartyEntry *entries[3];
    int i;

    if (scene->mode == 0) {
        return;
    }
    if (UpdateIdleTimeout_0206e1c8() && func_ov001_02072040()) {
        RunHudExitCallback_02071fec();
    }
    scene->timer += delta;
    SettleAnchorOnGround_020d7054(delta);
    UpdateEffectSlotPhase_020d7640(&scene->frontRig, delta);
    UpdateRaisedModelAnimation_020d7904(&scene->backRig, delta);
    for (i = 0; i < 3; i++) {
        UpdateHazardRig_020d777c(&scene->rigs[i], i, delta);
    }
    UpdateBlastFadeSequence_020d72c4(delta);
    for (i = 0; i < 3; i++) {
        entries[i] = GetBoundedEntryField_0206db5c(i);
    }

    switch (scene->mode) {
    case 0:
        break;
    case 1: {
        BOOL ready = FALSE;
        if (scene->timer >= 0x14000) {
            ready = TRUE;
        }
        if (scene->arrived && scene->landed) {
            ready = TRUE;
        }
        if (!ready) {
            return;
        }
        UpdateSceneCameraTransform_020d720c(TRUE);
        scene->timer = 0;
        scene->mode = 2;
        return;
    }
    case 2: {
        BOOL ready = TRUE;
        for (i = 1; i < 3; i++) {
            if (entries[i]->flags & 0x40000) {
                ready = FALSE;
            }
        }
        if (!ready) {
            return;
        }
        UpdateSceneCameraTransform_020d720c(TRUE);
        scene->mode = 3;
        scene->timer = 0;
        scene->soundPending = 1;
        return;
    }
    case 3: {
        BOOL ready = TRUE;
        UpdateSceneCameraTransform_020d720c(FALSE);
        for (i = 1; i < 3; i++) {
            if (entries[i]->flags & 0x20000) {
                ready = FALSE;
            }
        }
        if (scene->soundPending && scene->timer >= 0) {
            RestartScriptSound_020a818c(entries[0]->sound, 0);
            scene->soundPending = 0;
        }
        if (!ready) {
            return;
        }
        if (entries[0]->onEvent != NULL) {
            entries[0]->onEvent(entries[0], 0x1d000);
        }
        for (i = 1; i < 3; i++) {
            PartyEntry *entry = entries[i];
            if (entry->onEvent != NULL) {
                entry->onEvent(entry, 0x1d000);
            }
            entry->flags |= 0x20000000;
        }
        SelectAnimationById_020ac8f4(scene->model, 0);
        TransitionState_020ac94c(scene->model, 0x1d000);
        scene->mode = 4;
        scene->timer = 0;
        CameraPath_ConsumeSkipRequest_020c2fd4();
        PurgeNearbyStageObjects_020d7998();
        return;
    }
    case 4:
        UpdateSceneCameraTransform_020d720c(FALSE);
        if (scene->timer < 0x14000) {
            return;
        }
        ResetEmitterRigOffset_020d75f8(&scene->frontRig);
        for (i = 0; i < 3; i++) {
            ResetEmitterRigAndApply_020d7738(&scene->rigs[i], i);
            entries[i]->flags |= 0x200000000ULL;
        }
        RunHudEnterCallback_02071fb4();
        PlaySoundChecked_0204d8d0(0xc2, 0);
        scene->mode = 5;
        scene->timer = 0;
        scene->speed = 0x1e0;
        scene->speedTimer = 0;
        scene->speedPhase = 0;
        return;
    case 5: {
        BOOL skip = FALSE;
        BOOL step;
        int speed;
        int adjust;
        void *unit;

        UpdateSceneCameraTransform_020d720c(FALSE);
        scene->speedTimer += delta;
        step = FALSE;
        switch (scene->speedPhase) {
        case 0:
            if (scene->speedTimer >= 0x1e000) {
                step = TRUE;
                scene->speedPhase = step;
            }
            break;
        case 1:
            if (scene->speedTimer >= 0x5000) {
                step = TRUE;
            }
            break;
        }
        if (step) {
            scene->speedTimer = 0;
            speed = scene->speed - 0x100;
            if (speed > 0x2000) {
                speed = 0x2000;
            } else if (speed < 0x1e0) {
                speed = 0x1e0;
            }
            scene->speed = speed;
        }
        adjust = 0;
        unit = func_ov001_0206db78(adjust);
        if (GetId10_020a755c(unit) == 5) {
            switch (GetFieldAt0x12_020a7560(unit)) {
            case 1:
                adjust = 0x300;
                break;
            case 2:
                adjust -= 0x300;
                break;
            case 4:
                skip = TRUE;
                break;
            }
            if (adjust != 0) {
                speed = scene->speed + adjust;
                if (speed > 0x2000) {
                    speed = 0x2000;
                } else if (speed < 0x1e0) {
                    speed = 0x1e0;
                }
                scene->speed = speed;
                scene->speedPhase = 0;
                scene->speedTimer = 0;
            }
        }
        if (skip || !func_ov001_02072040()) {
            if (skip) {
                scene->mode = 6;
                scene->timer = 0;
                for (i = 0; i < 3; i++) {
                    if (entries[i]->onEvent != NULL) {
                        entries[i]->onEvent(entries[i], 0x35000);
                    }
                }
                RebindEmitterSlotsPhase1_020d78ec(&scene->backRig);
                CameraPath_ConsumeSkipRequest_020c2fd4();
                PlaySoundChecked_0204d8d0(0xc2, 1);
            }
            RebindEmitterSlotsPhase3_020d7628(&scene->frontRig);
            for (i = 0; i < 3; i++) {
                RebindEmitterSlotsPhase3_020d7764(&scene->rigs[i]);
            }
            StopSeqArcOrDefault_0204d960(0xc2, 0, 6);
            if (!skip) {
                ClearStageEventsAndPlayerFlags_020d7404(scene);
            }
        }
        scene->heading += scene->speed;
        TransitionState_020ac94c(scene->model, entries[0]->animValue);
        return;
    }
    case 6:
        UpdateSceneCameraTransform_020d720c(FALSE);
        if (scene->finished == 0 && scene->timer >= 0x29000) {
            func_ov001_0206e6f4(0);
            scene->finished = 1;
            scene->finishArg = 0;
        }
        TransitionState_020ac94c(scene->model, entries[0]->animValue);
        return;
    case 7: {
        BOOL idle = TRUE;
        if (scene->frontRig.active) {
            idle = FALSE;
        }
        if (scene->backRig.active) {
            idle = FALSE;
        }
        for (i = 0; i < 3; i++) {
            if (scene->rigs[i].active) {
                idle = FALSE;
                break;
            }
        }
        if (scene->finished) {
            idle = FALSE;
        }
        if (idle) {
            scene->mode = 0;
        }
        break;
    }
    }
}
