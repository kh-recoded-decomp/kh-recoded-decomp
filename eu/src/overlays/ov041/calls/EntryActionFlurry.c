#pragma opt_common_subs off
#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

/* Whether the flurry timer is in the window before a hit frame, or in the early stretch before that window. */
#define IN_PRESS_WINDOW(f)                                                                                          \
    (FRAME_TO_FX32(f) - window <= data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < FRAME_TO_FX32(f))
#define IN_EARLY_WINDOW(f)                                                                                          \
    (FRAME_TO_FX32(f) - window - early < data_ov041_020cff48.castTimer &&                                          \
     data_ov041_020cff48.castTimer < FRAME_TO_FX32(f) - window)

#define FLURRY_RUN 10
#define FLURRY_HITS 20 /* each further hit */
#define FLURRY_LAST_HITS 25 /* hits four and five play out without moving */
#define FLURRY_HIT 100
#define FLURRY_RETURN 103

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void ClearEntryActionState(StageEntry *entry);
extern void ChooseEntryMainTarget(StageEntry *entry);
extern void ShowEntryPairPanel(StageEntry *entry, StageEntry *target);
extern void CheckPairTimedPress(StageEntry *entry, StageEntry *target);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern s32 GetHudLabelId(int labelIndex);
extern void ShowFieldMessageLine_02072ad0(int kind, ...);
extern int NNS_G3dGetResDictIdxByName(const void *dict, const char *name);
extern void FinishEntryAction(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ForEachActionTarget(StageEntry *entry, int seqArcNo, int soundIndex);
extern void ApplyActionToTargets(StageEntry *entry);
extern void ReleaseStageItem(StageResourceItem *item);
extern const char sOv041_Bip01_020cf730[];

static inline StageResourceItem *SpawnOnEntry(StageEntry *entry, u8 index, u8 animation, BOOL persistent)
{
    VecFx32 position;

    GetEntryPosition(&position, entry);
    return SpawnStageItem(entry, 0xff, index, animation, &position, persistent);
}

static inline void UpdateFlurryHitEnd(StageEntryAction *action)
{
    fx32 hitEnd;

    switch (data_ov041_020cff48.flurryHit) {
    default:
        return;
    case 4:
        hitEnd = FRAME_TO_FX32(action->flurry[FLURRY_HIT_END + data_ov041_020cff48.flurryHit]);
        break;
    case 5:
        hitEnd = FRAME_TO_FX32(action->flurry[FLURRY_HIT_END + data_ov041_020cff48.flurryHit]);
        break;
    }
    data_ov041_020cff48.flurryHitEnd = hitEnd;
}

static inline void SelectNextFlurryStep(int *nextStep, StageRenderCapture *capture)
{
    switch (capture->flurryRound) {
    case 0:
        capture->flurryRound++;
        *nextStep = FLURRY_HITS;
        return;
    case 1:
        *nextStep = FLURRY_HITS;
        return;
    case 2:
        *nextStep = FLURRY_HITS;
        return;
    case 3:
        *nextStep = FLURRY_RETURN;
        return;
    }
}

/* Action kind 5: close in, deliver six timed hits, then return to the starting position. */
void EntryActionFlurry(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame;
    BOOL again = FALSE;
    int seconds;
    u8 hit;

    if (!IsStageEntryFrozen(entry) && entry->stateStep > 4) {
        data_ov041_020cff48.castTimer += FX32_ONE;
    }
    frame = GetEntryAnimationFrame(entry);
    seconds = data_ov041_020cff48.castTimer >> FX32_SHIFT;
    if (action->flurryPressFrames[0] + 1 == seconds || action->flurryPressFrames[1] + 1 == seconds ||
        action->flurryPressFrames[2] + 1 == seconds) {
        ClearEntryActionState(entry);
        ChooseEntryMainTarget(entry);
    } else if (action->flurryPressFrames[3] + 1 == seconds || action->flurryPressFrames[4] + 1 == seconds) {
        ClearEntryActionState(entry);
    }
    if (entry->flags & STAGE_ENTRY_ENEMY) {
        StageEntry *target = &work->entries[entry->targets[0]];
        fx32 window = 4 * FX32_ONE;
        fx32 early = window;

        if (entry->statuses[STAGE_ENTRY_STATUS_10] > 0 || target->statuses[STAGE_ENTRY_STATUS_10] > 0) {
            window += 2 * FX32_ONE;
            early -= 2 * FX32_ONE;
        }
        if (IN_PRESS_WINDOW(action->flurryPressFrames[0]) || IN_PRESS_WINDOW(action->flurryPressFrames[1]) ||
            IN_PRESS_WINDOW(action->flurryPressFrames[2]) || IN_PRESS_WINDOW(action->flurryPressFrames[3]) ||
            IN_PRESS_WINDOW(action->flurryPressFrames[4]) || IN_PRESS_WINDOW(action->flurryPressFrames[5])) {
            ShowEntryPairPanel(entry, &work->entries[entry->mainTarget]);
        } else if (IN_EARLY_WINDOW(action->flurryPressFrames[0]) || IN_EARLY_WINDOW(action->flurryPressFrames[1]) ||
                   IN_EARLY_WINDOW(action->flurryPressFrames[2]) || IN_EARLY_WINDOW(action->flurryPressFrames[3]) ||
                   IN_EARLY_WINDOW(action->flurryPressFrames[4]) || IN_EARLY_WINDOW(action->flurryPressFrames[5])) {
            CheckPairTimedPress(entry, &work->entries[entry->mainTarget]);
        }
    }
    switch (entry->stateStep) {
    case 0:
        entry->effects[0] = SpawnOnEntry(entry, 0x14, 0, FALSE);
        PlayStageSound(0x1a0, 6, TRUE);
        ShowFieldMessageLine_02072ad0(0x11, GetHudLabelId(0xef));
        data_ov041_020cff48.flurryHit = 0;
        data_ov041_020cff48.flurryRound = 0;
        data_ov041_020cff48.castTimer = 0;
        entry->stateStep++;
    case 1:
        if (entry->effects[0]->flags & 4) {
            break;
        }
        entry->effects[0] = NULL;
        entry->effects[0] = SpawnOnEntry(entry, 0x16, 0, FALSE);
        PlayStageSound(0x43, 2, TRUE);
        PlayStageSound(0x1a0, 0x29, TRUE);
        entry->stateStep++;
    case 2: {
        void *dict;

        if (entry->effects[0]->flags & 4) {
            break;
        }
        dict = NULL;
        entry->effects[0] = NULL;
        entry->effects[0] = SpawnOnEntry(entry, 0x16, 1, TRUE);
        if (entry->slot.node.modelResource != NULL) {
            dict = (u8 *)entry->slot.node.modelResource + 0x40;
        }
        entry->effects[0]->variant = dict != NULL ? NNS_G3dGetResDictIdxByName(dict, sOv041_Bip01_020cf730) : -1;
        entry->effects[0]->flags |= 0x10;
        entry->stateStep++;
    }
    case 3:
        entry->stateStep++;
        break;
    case 4:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        entry->stateStep = FLURRY_RUN;
        again = TRUE;
        break;
    case FLURRY_RUN:
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        entry->stateStep++;
    case FLURRY_RUN + 1: {
        VecFx32 start;
        VecFx32 end;

        if (frame < FRAME_TO_FX32(action->flurry[FLURRY_START_FRAME])) {
            break;
        }
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        StartStageEntryMotion(entry, &start, &end, FRAME_TO_FX32(action->effectLength), STAGE_MOTION_EASE_OUT);
        entry->stateStep++;
    }
    case FLURRY_RUN + 2:
        if (!StepEntryMotion(entry, work->frameStep) || IsEntryFlag2Set(entry)) {
            break;
        }
        SetSceneEntryAnimation(entry, action->flurry[FLURRY_ANIMATION], 0, 0);
        frame = GetEntryAnimationFrame(entry);
        entry->stateStep++;
    case FLURRY_RUN + 3:
        if (frame < FRAME_TO_FX32(action->flurry[FLURRY_HIT_END])) {
            break;
        }
        entry->stateStep = FLURRY_HIT;
        again = TRUE;
        break;
    case FLURRY_HITS: {
        VecFx32 start;
        VecFx32 end;
        u8 animation = action->flurry[FLURRY_ANIMATION] + data_ov041_020cff48.flurryHit;

        data_ov041_020cff48.flurryHitEnd =
            FRAME_TO_FX32(action->flurry[FLURRY_HIT_END + data_ov041_020cff48.flurryHit]);
        SetSceneEntryAnimation(entry, animation, 0, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        StartStageEntryMotion(entry, &start, &end, data_ov041_020cff48.flurryHitEnd, STAGE_MOTION_EASE_OUT);
        entry->stateStep++;
    }
    case FLURRY_HITS + 1:
        if (!StepEntryMotion(entry, work->frameStep) || frame < data_ov041_020cff48.flurryHitEnd) {
            break;
        }
        entry->stateStep = FLURRY_HIT;
        again = TRUE;
        break;
    case FLURRY_LAST_HITS:
        if (frame < data_ov041_020cff48.flurryHitEnd) {
            break;
        }
        entry->stateStep = FLURRY_HIT;
        again = TRUE;
        break;
    case FLURRY_HIT:
        ComputeEntryHit(entry, &entry->hit);
        if (data_ov041_020cff48.flurryHit == 5) {
            ForEachActionTarget(entry, 0x1a0, 0xd);
        } else {
            ApplyActionToTargets(entry);
        }
        entry->stateStep++;
    case FLURRY_HIT + 1:
        if (IsStageEntryFrozen(entry)) {
            break;
        }
        if (data_ov041_020cff48.flurryHit == 3 || data_ov041_020cff48.flurryHit == 4) {
            entry->stateStep = FLURRY_LAST_HITS;
            data_ov041_020cff48.flurryHit++;
            UpdateFlurryHitEnd(action);
            break;
        }
        entry->stateStep++;
    case FLURRY_HIT + 2:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        data_ov041_020cff48.flurryHit++;
        /* Reload the stored byte before choosing the next round. */
        hit = *(volatile u8 *)&data_ov041_020cff48.flurryHit;
        if (hit == 3 || hit == 6) {
            data_ov041_020cff48.flurryRound++;
        }
        SelectNextFlurryStep(&again, &data_ov041_020cff48);
        entry->stateStep = again;
        again = TRUE;
        break;
    case FLURRY_RETURN: {
        VecFx32 backStart;
        VecFx32 backEnd;

        SetSceneEntryAnimation(entry, action->flurry[FLURRY_RECOVER_ANIMATION], 0, 0);
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &backStart, &backEnd, FALSE);
        StartStageEntryMotion(entry, &backStart, &backEnd, FRAME_TO_FX32(action->flurry[FLURRY_RETURN_LENGTH]),
                              STAGE_MOTION_EASE_OUT);
        entry->stateStep++;
    }
    case FLURRY_RETURN + 1:
        if (!StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        entry->effects[0]->flags &= (u8)~0x10;
        ReleaseStageItem(entry->effects[0]);
        entry->stateStep++;
    case FLURRY_RETURN + 2:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        entry->stateStep++;
    case FLURRY_RETURN + 3:
        FinishEntryAction(entry);
        break;
    }
    if (again) {
        data_ov041_020cff48.castTimer -= FX32_ONE;
        EntryActionFlurry(entryIndex);
    }
}
