#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define YAW_TURNED 0x3ffc /* facing across the field */
#define SHOT_HEIGHT 0x19a /* every shot flies at this height */
#define BARRAGE_OVER 0x67 /* every shot has landed */

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void PlayEntryActionSound(StageEntry *entry, fx32 frame);
extern int func_0202a9e4(u16 range);
extern void ChooseEntryMainTarget(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void MI_Copy48B(const void *src, void *dest);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern void SpawnPanelDriftPreset(int preset);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void StartStageMotion(VecFx32 *position, StageMotion *motion, const VecFx32 *start, const VecFx32 *end,
                             fx32 duration, int profile);
extern int Anim_GetFrame(void *anim, int track);
extern BOOL StepStageMotion(VecFx32 *position, StageMotion *motion, fx32 step);
extern void UpdateTimedPressPanel(StageEntry *player, StageEntry *other, BOOL playerFirst);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionHit(StageEntry *entry, u8 targetIndex, BOOL pressCheck);
extern void CheckTimedPress(StageEntry *entry, BOOL defending);
extern void ReleaseStageItem(StageResourceItem *item);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern u32 IsEntryFlag2Set(StageEntry *entry);

static inline void TurnItemModel(StageItemModel *model, u16 yaw)
{
    model->yaw = yaw;
    model->flags |= STAGE_MODEL_USE_YAW;
}

static inline VecFx32 AboveGroundOf(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    return position;
}

static inline VecFx32 OverheadOf(StageEntry *entry)
{
    VecFx32 position;

    GetEntryOverheadPosition(&position, entry);
    return position;
}

/*
 * Action handler for a barrage: picks how many shots to fire (minShots to maxShots), shows the cast effect on
 * the cast frame and the aim effect on the effect frame, then every shotInterval frames fires a shot at the next
 * standing primary entry, flying it from beside the attacker to the target's head. A shot that arrives hits its
 * target (shown on the press panel while it flies, with the guard press checked early when no shot flies just
 * ahead of it); once no shot is left in the air the attacker goes back to idle and the action ends.
 */
void EntryActionBarrage(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    BOOL flying = FALSE;
    BOOL landed[3] = {FALSE, FALSE, FALSE};
    VecFx32 start;
    VecFx32 end;
    int frame = GetEntryAnimationFrame(entry);
    int shotFrame;
    fx32 hitFrame;
    fx32 pressFrame;
    fx32 earlyWindow;

    PlayEntryActionSound(entry, frame);
    switch (entry->stateStep) {
    case 0:
        data_ov041_020cff48.shotsFired = 0;
        data_ov041_020cff48.shotCount =
            func_0202a9e4((action->maxShots - action->minShots) * 1000) / 1000 + action->minShots - 1;
        if (action->minShots == action->maxShots) {
            data_ov041_020cff48.shotCount = action->minShots - 1;
        }
        entry->stateStep++;
    case 1:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        SetSceneEntryAnimation(entry, action->animation, 1, 1);
        frame = GetEntryAnimationFrame(entry);
        PlayEntryActionSound(entry, frame);
        entry->stateStep++;
    case 2: {
        VecFx32 position;
        StageResourceItem *item;

        if (frame < FRAME_TO_FX32(action->castFrame)) {
            break;
        }
        GetEntryPosition(&position, entry);
        item = SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position,
                              FALSE);
        if (item != NULL) {
            MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
        }
        entry->stateStep++;
    }
    case 3: {
        VecFx32 position;
        StageResourceItem *item;

        if (frame < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        GetEntryOverheadPosition(&position, entry);
        item = SpawnStageItem(entry, action->aimEffectCategory, action->aimEffectIndex, action->aimEffectAnimation,
                              &position, FALSE);
        if (item != NULL) {
            MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
        }
        SpawnPanelDriftPreset(2);
        data_ov041_020cff48.shotTimer = action->shotInterval * 2;
        entry->stateStep++;
    }
    case 4:
        if (IsStageEntryFrozen(entry)) {
            break;
        }
        if (data_ov041_020cff48.shotTimer >= 0 && data_ov041_020cff48.shotTimer % action->shotInterval == 0 &&
            data_ov041_020cff48.shotsFired < entry->targetCount) {
            int target = data_ov041_020cff48.shotsFired;
            StageResourceItem **shot = &entry->effects[target];
            VecFx32 position;

            GetEntryOverheadPosition(&position, entry);
            *shot = SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &position,
                                   FALSE);
            TurnItemModel(&(*shot)->model, YAW_TURNED);
            for (; target < work->primaryCount; target++) {
                if (work->entries[target].state != STAGE_ENTRY_OUT) {
                    (*shot)->variant = target;
                    break;
                }
            }
            start = AboveGroundOf(entry);
            end = OverheadOf(&work->entries[entry->effects[data_ov041_020cff48.shotsFired]->variant]);
            start.x += 0x299a;
            start.z -= FX32_ONE;
            start.y = SHOT_HEIGHT;
            end.y = SHOT_HEIGHT;
            StartStageMotion(&entry->effects[data_ov041_020cff48.shotsFired]->model.position,
                             &entry->effects[data_ov041_020cff48.shotsFired]->model.motion, &start, &end,
                             FRAME_TO_FX32(action->effectLength - action->effectFrame), STAGE_MOTION_STEADY);
            data_ov041_020cff48.shotsFired++;
        }
        /* The frame is not needed any more: it runs through the shot slots. */
        for (frame = 0; frame < 5; frame++) {
            if (entry->effects[frame] != NULL) {
                shotFrame = Anim_GetFrame(&entry->effects[frame]->model, 0);
                hitFrame = FRAME_TO_FX32(action->effectLength - action->effectFrame - 1);
                pressFrame = FRAME_TO_FX32(action->pressWindow);
                earlyWindow = 4 * FX32_ONE;

                if (work->entries[entry->effects[frame]->variant].statuses[STAGE_ENTRY_STATUS_10] > 0) {
                    pressFrame += earlyWindow / 2;
                    earlyWindow -= earlyWindow / 2;
                }
                if (StepStageMotion(&entry->effects[frame]->model.position, &entry->effects[frame]->model.motion,
                                    work->frameStep)) {
                    UpdateTimedPressPanel(&work->entries[entry->effects[frame]->variant], entry, FALSE);
                    ComputeEntryHit(entry, &entry->hit);
                    ApplyActionHit(entry, entry->effects[frame]->variant, TRUE);
                    landed[frame] = TRUE;
                } else {
                    flying = TRUE;
                    pressFrame = hitFrame - pressFrame;
                    if (pressFrame < shotFrame && shotFrame <= hitFrame) {
                        UpdateTimedPressPanel(&work->entries[entry->effects[frame]->variant], entry, FALSE);
                    } else if (pressFrame - earlyWindow < shotFrame && shotFrame <= pressFrame && frame >= 1 &&
                               entry->effects[frame - 1] == NULL) {
                        CheckTimedPress(&work->entries[entry->effects[frame]->variant], TRUE);
                    }
                }
            }
        }
        for (frame = 0; frame < 5; frame++) {
            if (landed[frame] && entry->effects[frame] != NULL) {
                ReleaseStageItem(entry->effects[frame]);
                entry->effects[frame] = NULL;
            }
        }
        if (data_ov041_020cff48.shotTimer >= 0) {
            data_ov041_020cff48.shotTimer--;
        }
        if (!flying) {
            entry->stateStep = BARRAGE_OVER;
        }
        break;
    case BARRAGE_OVER:
        if (IsStageEntryFrozen(entry)) {
            break;
        }
        entry->stateStep++;
    case BARRAGE_OVER + 1:
        if (!MatchesEitherSlotId(entry, action->animation)) {
            FinishEntryAction(entry);
        }
        break;
    }
    if (MatchesEitherSlotId(entry, action->animation) && !IsEntryFlag2Set(entry) && !IsStageEntryFrozen(entry)) {
        SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
    }
}
