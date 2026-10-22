#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define YAW_TURNED 0x3ffc /* facing across the field */

/* How the spell reaches its target (StageEntryAction.castStyle). */
#define CAST_FROM_ABOVE 0 /* a mark appears over the target and a shot flies down from it */
#define CAST_STRIKE 1 /* the same, and the shot bursts where it lands */
#define CAST_AROUND_CASTER 2 /* it takes hold around the caster */
#define CAST_VOLLEY 3 /* a volley of shots, then one more dropped on the target */
#define CAST_SWEEP 4 /* it strikes each side entry in turn */

/* The first state of each style, the hit and the end. */
#define CAST_STATE_FROM_ABOVE 10
#define CAST_STATE_STRIKE 20
#define CAST_STATE_AROUND_CASTER 30
#define CAST_STATE_VOLLEY 40
#define CAST_STATE_SWEEP 50
#define CAST_STATE_HIT 100
#define CAST_STATE_END 102

/* The early press span: the press window grows by half of it under STAGE_ENTRY_STATUS_10, and the cast timer
 * advances by a quarter of it each frame. */
#define PRESS_SPAN (4 * FX32_ONE)

/* Whole frames between two shots of a volley: the frames from its first shot to the return frame, spread over the
 * casts. */
#define VOLLEY_INTERVAL(action, first) (((action)->returnFrame - (first)) / (data_ov041_020cff48.castCount + 1))

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void ShowEntryPairPanel(StageEntry *entry, StageEntry *target);
extern void CheckPairTimedPress(StageEntry *entry, StageEntry *target);
extern void HandleTimedPressWindow(StageEntry *entry, int animation, fx32 hitFrame);
extern int func_0202a9e4(u16 range);
extern void ChooseEntryMainTarget(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern void ClearEntryActionState(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void PlayEntryActionSound(StageEntry *entry, fx32 frame);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern const fx32 gStageTurnEffectHeights[];
extern void MI_Copy48B(const void *src, void *dest);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void SpawnPanelDriftPreset(int preset);
extern int Anim_GetFrame(void *anim, int track);
extern void StartStageMotion(VecFx32 *position, StageMotion *motion, const VecFx32 *start, const VecFx32 *end,
                             fx32 duration, int profile);
extern BOOL StepStageMotion(VecFx32 *position, StageMotion *motion, fx32 step);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void ReleaseStageItem(StageResourceItem *item);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
#define SetPanelState NNS_FndFreeToExpHeap_2 /* ov044's SetPanelState under its EU symbol name */
extern void SetPanelState(int state, fx32 duration);

/* Turns an item's model to face the given yaw. */
static inline void TurnItemModel(StageItemModel *model, u16 yaw)
{
    model->yaw = yaw;
    model->flags |= STAGE_MODEL_USE_YAW;
}

/*
 * Action handler for a cast (kind 10): while the press window of each target is open the timed press is offered,
 * then the caster plays its animation (a sweep first rises a unit) and its effect item appears at the cast frame.
 * Each style then carries the spell to the main target: a mark over the target with a shot flying down from it,
 * the same with a burst where it lands, an effect around the caster, a volley of shots followed by one dropped
 * on the target, or a sweep over the side entries in turn. After the hit the cast repeats castCount more times
 * (the volley only its drop), then waits for the animation and castWait frames and finishes the action.
 */
void EntryActionCast(u8 entryIndex)
{
    StageWork *work;
    StageEntry *entry;
    int i;
    StageEntryAction *action;
    int frame;
    BOOL again;
    BOOL waiting;
    VecFx32 riseStart[1]; /* an array: the end is copied from it through memory */
    VecFx32 riseEnd;
    VecFx32 aboveMark;
    VecFx32 aboveShotStart;
    VecFx32 aboveShotEnd;
    VecFx32 strikeMark;
    VecFx32 strikeShotStart;
    VecFx32 strikeShotEnd;
    VecFx32 volleyStart;
    VecFx32 volleyEnd;
    VecFx32 dropStart;
    VecFx32 dropEnd;
    VecFx32 sweepMark;
    VecFx32 returnStart;
    VecFx32 returnEnd;

    work = gMovieContextState->stageWork;
    entry = &work->entries[entryIndex];
    action = GetEntryAction(entry);
    again = FALSE;
    waiting = FALSE;
    frame = GetEntryAnimationFrame(entry);
    for (i = 0; i < entry->targetCount; i++) {
        StageEntry *target = &work->entries[entry->targets[i]];
        fx32 hitFrame = FRAME_TO_FX32(action->effectLength);
        fx32 window = FRAME_TO_FX32(action->pressWindow);
        fx32 early = PRESS_SPAN;
        fx32 lead = FRAME_TO_FX32(action->returnFrame + 1);
        fx32 start;
        fx32 end;

        if (entry->statuses[STAGE_ENTRY_STATUS_10] > 0 || target->statuses[STAGE_ENTRY_STATUS_10] > 0) {
            window += PRESS_SPAN / 2;
            early -= PRESS_SPAN / 2;
        }
        switch (action->castStyle) {
        case CAST_FROM_ABOVE:
            if (entry->stateStep >= CAST_STATE_FROM_ABOVE && entry->stateStep < CAST_STATE_STRIKE) {
                data_ov041_020cff48.castTimer += PRESS_SPAN / 4;
                end = hitFrame + lead;
                start = end - window;
                if (start <= data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < end) {
                    ShowEntryPairPanel(entry, &work->entries[entry->mainTarget]);
                } else if (end - window - early < data_ov041_020cff48.castTimer &&
                           data_ov041_020cff48.castTimer < end - window) {
                    CheckPairTimedPress(entry, &work->entries[entry->mainTarget]);
                }
            } else {
                data_ov041_020cff48.castTimer = 0;
            }
            break;
        case CAST_STRIKE:
            if (entry->stateStep >= CAST_STATE_STRIKE && entry->stateStep < CAST_STATE_AROUND_CASTER) {
                data_ov041_020cff48.castTimer += PRESS_SPAN / 4;
                start = hitFrame - window;
                if (start <= data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < hitFrame) {
                    ShowEntryPairPanel(entry, &work->entries[entry->mainTarget]);
                } else if (start - early < data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < start) {
                    CheckPairTimedPress(entry, &work->entries[entry->mainTarget]);
                }
            } else {
                data_ov041_020cff48.castTimer = 0;
            }
            break;
        case CAST_AROUND_CASTER:
            HandleTimedPressWindow(entry, action->animation, FRAME_TO_FX32(action->effectLength));
            break;
        case CAST_VOLLEY:
            if (entry->stateStep >= CAST_STATE_VOLLEY + 5 && entry->stateStep < CAST_STATE_SWEEP) {
                data_ov041_020cff48.castTimer += PRESS_SPAN / 4;
                start = hitFrame - window - lead;
                if (start <= data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < hitFrame - lead) {
                    ShowEntryPairPanel(entry, &work->entries[entry->mainTarget]);
                } else if (start - early < data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < start) {
                    CheckPairTimedPress(entry, &work->entries[entry->mainTarget]);
                }
            } else {
                data_ov041_020cff48.castTimer = 0;
            }
            break;
        case CAST_SWEEP:
            if (entry->stateStep >= CAST_STATE_SWEEP + 1 && entry->stateStep < CAST_STATE_SWEEP + 10) {
                data_ov041_020cff48.castTimer += PRESS_SPAN / 4;
                end = hitFrame + lead;
                start = end - window;
                if (start <= data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < end) {
                    ShowEntryPairPanel(entry, &work->entries[entry->mainTarget]);
                } else if (start - early < data_ov041_020cff48.castTimer && data_ov041_020cff48.castTimer < start) {
                    CheckPairTimedPress(entry, &work->entries[entry->mainTarget]);
                }
            } else {
                data_ov041_020cff48.castTimer = 0;
            }
            break;
        }
    }
    switch (entry->stateStep) {
    case 0:
        data_ov041_020cff48.castsDone = 0;
        data_ov041_020cff48.castCount =
            action->minRepeats + func_0202a9e4((action->maxRepeats - action->minRepeats + 1) * 1000) / 1000 - 1;
        if (action->minRepeats == action->maxRepeats) {
            data_ov041_020cff48.castCount = action->minRepeats - 1;
        }
        data_ov041_020cff48.castDelay = 0;
        data_ov041_020cff48.sweepStage = 0;
        entry->stateStep++;
    case 1:
        switch (action->castStyle) {
        case CAST_FROM_ABOVE:
        case CAST_STRIKE:
        case CAST_VOLLEY:
        case CAST_SWEEP:
            break;
        default:
            ChooseEntryMainTarget(entry);
            if (entry->mainTarget == entry->index) {
                FinishEntryAction(entry);
                return;
            }
            break;
        }
        SetSceneEntryAnimation(entry, action->animation, 1, 1);
        frame = GetEntryAnimationFrame(entry);
        PlayEntryActionSound(entry, frame);
        if (action->castStyle == CAST_SWEEP) {
            VecFx32 position;

            GetPositionAboveGround(&position, entry);
            riseStart[0] = position;
            riseEnd = riseStart[0];
            riseEnd.x += FX32_ONE;
            StartStageEntryMotion(entry, riseStart, &riseEnd, 5 * FX32_ONE, STAGE_MOTION_STEADY);
        }
        entry->stateStep++;
    case 2:
        if (action->castStyle == CAST_SWEEP) {
            StepEntryMotion(entry, work->frameStep);
        }
        if (frame < FRAME_TO_FX32(action->castFrame)) {
            break;
        }
        {
            VecFx32 position;
            StageResourceItem *item;

            GetEntryPosition(&position, entry);
            item = SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation,
                                  &position, FALSE);
            if (item != NULL) {
                MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
            }
        }
        if (action->castStyle == CAST_SWEEP) {
            PlayStageSound(action->soundSeqArc, action->soundIndex, TRUE);
            SpawnPanelDriftPreset(0);
        }
        entry->stateStep++;
    case 3:
        switch (action->castStyle) {
        case CAST_FROM_ABOVE:
            entry->stateStep = CAST_STATE_FROM_ABOVE;
            break;
        case CAST_STRIKE:
            entry->stateStep = CAST_STATE_STRIKE;
            break;
        case CAST_AROUND_CASTER:
            entry->stateStep = CAST_STATE_AROUND_CASTER;
            break;
        case CAST_VOLLEY:
            entry->stateStep = CAST_STATE_VOLLEY;
            break;
        case CAST_SWEEP:
            entry->stateStep = CAST_STATE_SWEEP;
            break;
        }
        again = TRUE;
        break;
    case CAST_STATE_FROM_ABOVE:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            entry->stateStep = CAST_STATE_END;
            return;
        }
        entry->stateStep++;
    case CAST_STATE_FROM_ABOVE + 1: {
        VecFx32 overhead;
        VecFx32 grid;

        if (data_ov041_020cff48.castDelay < FRAME_TO_FX32(action->returnFrame)) {
            data_ov041_020cff48.castDelay += FX32_ONE;
            break;
        }
        GetEntryOverheadPosition(&overhead, &work->entries[entry->mainTarget]);
        aboveMark = overhead;
        GetStageGridPosition(&grid, work->entries[entry->mainTarget].row, work->entries[entry->mainTarget].column);
        aboveMark.x = grid.x;
        entry->effects[0] =
            SpawnStageItem(entry, action->castEffectCategory, action->castEffectIndex, action->castEffectAnimation,
                           &aboveMark, FALSE);
        if (entry->effects[0] != NULL) {
            aboveMark.x -= 8 * FX32_ONE;
            entry->effects[0]->model.position = aboveMark;
        }
        PlayStageSound(action->soundSeqArc, action->soundIndex, TRUE);
        entry->stateStep++;
    }
    case CAST_STATE_FROM_ABOVE + 2: {
        VecFx32 overhead;
        VecFx32 grid;

        if (Anim_GetFrame(&entry->effects[0]->model, 0) < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        entry->effects[1] = SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation,
                                           &entry->effects[0]->model.position, TRUE);
        TurnItemModel(&entry->effects[1]->model, YAW_TURNED);
        aboveShotStart = entry->effects[0]->model.position;
        GetEntryOverheadPosition(&overhead, &work->entries[entry->mainTarget]);
        aboveShotEnd = overhead;
        GetStageGridPosition(&grid, work->entries[entry->mainTarget].row, work->entries[entry->mainTarget].column);
        aboveShotEnd.x = grid.x;
        StartStageMotion(&entry->effects[1]->model.position, &entry->effects[1]->model.motion, &aboveShotStart,
                         &aboveShotEnd,
                         FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->effectFrame),
                         STAGE_MOTION_STEADY);
        entry->effects[0] = NULL;
        entry->stateStep++;
    }
    case CAST_STATE_FROM_ABOVE + 3:
        if (!StepStageMotion(&entry->effects[1]->model.position, &entry->effects[1]->model.motion, work->frameStep)) {
            break;
        }
        ReleaseStageItem(entry->effects[1]);
        entry->stateStep = CAST_STATE_HIT;
        again = TRUE;
        break;
    case CAST_STATE_STRIKE:
        ClearEntryActionState(entry);
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            entry->stateStep = CAST_STATE_END;
            return;
        }
        {
            VecFx32 overhead;
            VecFx32 grid;

            GetEntryOverheadPosition(&overhead, &work->entries[entry->mainTarget]);
            strikeMark = overhead;
            GetStageGridPosition(&grid, work->entries[entry->mainTarget].row, work->entries[entry->mainTarget].column);
            strikeMark.x = grid.x;
            entry->effects[0] =
                SpawnStageItem(entry, action->castEffectCategory, action->castEffectIndex, action->castEffectAnimation,
                               &strikeMark, FALSE);
            if (entry->effects[0] != NULL) {
                strikeMark.y += 8 * FX32_ONE;
                entry->effects[0]->model.position = strikeMark;
            }
        }
        PlayStageSound(action->soundSeqArc, action->soundIndex, TRUE);
        entry->stateStep++;
    case CAST_STATE_STRIKE + 1: {
        VecFx32 overhead;
        VecFx32 grid;

        if (Anim_GetFrame(&entry->effects[0]->model, 0) < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        entry->effects[1] = SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation,
                                           &entry->effects[0]->model.position, TRUE);
        strikeShotStart = entry->effects[0]->model.position;
        GetEntryOverheadPosition(&overhead, &work->entries[entry->mainTarget]);
        strikeShotEnd = overhead;
        GetStageGridPosition(&grid, work->entries[entry->mainTarget].row, work->entries[entry->mainTarget].column);
        strikeShotEnd.x = grid.x;
        StartStageMotion(&entry->effects[1]->model.position, &entry->effects[1]->model.motion, &strikeShotStart,
                         &strikeShotEnd,
                         FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->effectFrame),
                         STAGE_MOTION_STEADY);
        entry->effects[0] = NULL;
        entry->stateStep++;
    }
    case CAST_STATE_STRIKE + 2:
        if (!StepStageMotion(&entry->effects[1]->model.position, &entry->effects[1]->model.motion, work->frameStep)) {
            break;
        }
        SpawnStageItem(entry, action->shotCategory, (u8)(action->shotIndex + 1), action->shotAnimation,
                       &entry->effects[1]->model.position, FALSE);
        ReleaseStageItem(entry->effects[1]);
        entry->stateStep = CAST_STATE_HIT;
        again = TRUE;
        break;
    case CAST_STATE_AROUND_CASTER:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        {
            VecFx32 position;

            GetPositionAboveGround(&position, entry);
            entry->effects[0] =
                SpawnStageItem(entry, action->castEffectCategory, action->castEffectIndex, action->castEffectAnimation,
                               &position, FALSE);
            if (entry->effects[0] != NULL) {
                MI_Copy48B(&entry->slot.node.rotation, &entry->effects[0]->model.rotation);
            }
        }
        entry->stateStep++;
    case CAST_STATE_AROUND_CASTER + 1:
        PlayEntryActionSound(entry, frame);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = CAST_STATE_HIT;
        again = TRUE;
        break;
    case CAST_STATE_VOLLEY:
        if (frame < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        entry->stateStep++;
    case CAST_STATE_VOLLEY + 1: {
        u8 first = action->effectFrame;

        if ((frame - FRAME_TO_FX32(first)) >> FX32_SHIFT != 0) {
            int elapsed = frame - FRAME_TO_FX32(first);

            if ((elapsed >> FX32_SHIFT) % VOLLEY_INTERVAL(action, first) == 0) {
                /* the shot's slot in effects[], as a byte offset */
                int offset = (((frame - FRAME_TO_FX32(first)) >> FX32_SHIFT) / VOLLEY_INTERVAL(action, first) - 1) *
                             sizeof(StageResourceItem *);
                StageResourceItem **slot = (StageResourceItem **)((u8 *)entry->effects + offset);
                VecFx32 position;
                VecFx32 casterPosition;
                VecFx32 grid;

                GetEntryPosition(&position, entry);
                *slot = SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &position,
                                       FALSE);
                GetEntryPosition(&casterPosition, entry);
                volleyStart = casterPosition;
                GetStageGridPosition(&grid, 2, 1);
                volleyEnd = grid;
                volleyEnd.y = 16 * FX32_ONE;
                volleyStart.y += 0x22 << 10;
                volleyStart.z += FX32_ONE;
                StartStageMotion(&(*slot)->model.position, &(*slot)->model.motion, &volleyStart, &volleyEnd,
                                 FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->effectFrame),
                                 STAGE_MOTION_STEADY);
            }
        }
        for (i = 0; i < 5; i++) {
            if (entry->effects[i] != NULL) {
                StepStageMotion(&entry->effects[i]->model.position, &entry->effects[i]->model.motion,
                                work->frameStep);
            }
        }
        if (frame < FRAME_TO_FX32(action->returnFrame)) {
            break;
        }
        entry->stateStep++;
    }
    case CAST_STATE_VOLLEY + 2: {
        BOOL moving = FALSE;

        for (i = 0; i < 5; i++) {
            if (entry->effects[i] != NULL &&
                !StepStageMotion(&entry->effects[i]->model.position, &entry->effects[i]->model.motion,
                                 work->frameStep)) {
                moving = TRUE;
            }
        }
        if (moving) {
            break;
        }
        for (i = 0; i < 5; i++) {
            ReleaseStageItem(entry->effects[i]);
            entry->effects[i] = NULL;
        }
        data_ov041_020cff48.castWait = action->volleyPause;
        entry->stateStep++;
        break;
    }
    case CAST_STATE_VOLLEY + 3:
        if (data_ov041_020cff48.castWait > 0) {
            data_ov041_020cff48.castWait--;
            break;
        }
        data_ov041_020cff48.castWait = action->dropPause;
        entry->stateStep++;
    case CAST_STATE_VOLLEY + 4:
        if (data_ov041_020cff48.castWait > 0) {
            data_ov041_020cff48.castWait--;
            break;
        }
        ClearEntryActionState(entry);
        entry->stateStep++;
    case CAST_STATE_VOLLEY + 5: {
        VecFx32 overhead;
        VecFx32 position;
        VecFx32 position2;
        VecFx32 grid;

        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            entry->stateStep = CAST_STATE_END;
            return;
        }
        GetEntryOverheadPosition(&overhead, &work->entries[entry->mainTarget]);
        entry->effects[0] =
            SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &overhead, TRUE);
        GetEntryOverheadPosition(&position, &work->entries[entry->mainTarget]);
        dropStart = position;
        GetEntryOverheadPosition(&position2, &work->entries[entry->mainTarget]);
        dropEnd = position2;
        dropStart.y += 12 * FX32_ONE;
        GetStageGridPosition(&grid, work->entries[entry->mainTarget].row, work->entries[entry->mainTarget].column);
        dropEnd.x = grid.x;
        StartStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, &dropStart, &dropEnd,
                         FRAME_TO_FX32(action->effectLength) - FRAME_TO_FX32(action->returnFrame),
                         STAGE_MOTION_STEADY);
        entry->stateStep++;
    }
    case CAST_STATE_VOLLEY + 6:
        if (!StepStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, work->frameStep)) {
            break;
        }
        ReleaseStageItem(entry->effects[0]);
        entry->effects[0] = NULL;
        again = TRUE;
        SpawnPanelDriftPreset(1);
        entry->stateStep = CAST_STATE_HIT;
        break;
    case CAST_STATE_SWEEP:
        if (MatchesEitherSlotId(entry, action->animation) && IsEntryFlag2Set(entry)) {
            break;
        }
        entry->stateStep++;
    case CAST_STATE_SWEEP + 1: {
        BOOL done = FALSE;

        switch (data_ov041_020cff48.sweepStage) {
        case 0:
            if ((work->flags & 0x800) && work->entries[1].state != STAGE_ENTRY_OUT) {
                entry->targetCount = 1;
                entry->mainTarget = 1;
                entry->targets[0] = 1;
                data_ov041_020cff48.sweepStage = 1;
                break;
            }
        case 1:
            if (work->entries[0].state != STAGE_ENTRY_OUT) {
                entry->targetCount = 1;
                entry->mainTarget = 0;
                entry->targets[0] = 0;
                data_ov041_020cff48.sweepStage = 2;
                break;
            }
        case 2:
            if ((work->flags & 0x400) && work->entries[2].state != STAGE_ENTRY_OUT) {
                entry->targetCount = 1;
                entry->mainTarget = 2;
                entry->targets[0] = 2;
                break;
            }
            data_ov041_020cff48.castWait = 20;
            entry->stateStep = CAST_STATE_END;
            done = TRUE;
            break;
        }
        if (done) {
            break;
        }
        for (i = 0; i < entry->targetCount; i++) {
            work->entries[entry->targets[i]].flags |= STAGE_ENTRY_SHOW_HP;
        }
        {
            VecFx32 ground;

            GetPositionAboveGround(&ground, &work->entries[entry->mainTarget]);
            sweepMark = ground;
            sweepMark.y = gStageTurnEffectHeights[work->shadowHeightIndex];
            entry->effects[0] =
                SpawnStageItem(entry, action->castEffectCategory, action->castEffectIndex, action->castEffectAnimation,
                               &sweepMark, FALSE);
        }
        entry->stateStep++;
    }
    case CAST_STATE_SWEEP + 2:
        if (entry->effects[0] != NULL &&
            Anim_GetFrame(&entry->effects[0]->model, 0) < FRAME_TO_FX32(action->effectFrame)) {
            break;
        }
        {
            VecFx32 ground;

            GetPositionAboveGround(&ground, &work->entries[entry->mainTarget]);
            entry->effects[1] =
                SpawnStageItem(entry, action->shotCategory, action->shotIndex, action->shotAnimation, &ground, FALSE);
        }
        SpawnPanelDriftPreset(1);
        entry->stateStep++;
    case CAST_STATE_SWEEP + 3:
        if (entry->effects[1] != NULL &&
            Anim_GetFrame(&entry->effects[1]->model, 0) < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = CAST_STATE_HIT;
        again = TRUE;
        break;
    case CAST_STATE_HIT:
        ComputeEntryHit(entry, &entry->hit);
        ApplyActionToTargets(entry);
        entry->stateStep++;
    case CAST_STATE_HIT + 1:
        if (IsStageEntryFrozen(entry)) {
            break;
        }
        if (action->castStyle == CAST_SWEEP && entry->effects[1] != NULL &&
            Anim_GetFrame(&entry->effects[1]->model, 0) < FRAME_TO_FX32(action->returnFrame)) {
            break;
        }
        switch (action->castStyle) {
        case CAST_FROM_ABOVE:
            if (data_ov041_020cff48.castsDone < data_ov041_020cff48.castCount) {
                ClearEntryActionState(entry);
                data_ov041_020cff48.castsDone++;
                entry->stateStep = CAST_STATE_FROM_ABOVE;
                again = TRUE;
                data_ov041_020cff48.castDelay = 0;
                data_ov041_020cff48.castTimer = 0;
            }
            break;
        case CAST_STRIKE:
            if (data_ov041_020cff48.castsDone < data_ov041_020cff48.castCount) {
                data_ov041_020cff48.castWait = 5;
                data_ov041_020cff48.castsDone++;
                entry->stateStep = CAST_STATE_STRIKE;
                again = TRUE;
                waiting = TRUE;
            }
            break;
        case CAST_VOLLEY:
            if (data_ov041_020cff48.castsDone < data_ov041_020cff48.castCount) {
                data_ov041_020cff48.castsDone++;
                entry->stateStep = CAST_STATE_VOLLEY + 3;
                again = TRUE;
            }
            break;
        case CAST_SWEEP:
            if (data_ov041_020cff48.castsDone < data_ov041_020cff48.castCount) {
                ClearEntryActionState(entry);
                data_ov041_020cff48.castsDone++;
                entry->stateStep = CAST_STATE_SWEEP + 1;
                again = TRUE;
                data_ov041_020cff48.castDelay = 0;
            }
            break;
        }
        if (waiting || again) {
            break;
        }
        entry->stateStep++;
        switch (action->castStyle) {
        case CAST_FROM_ABOVE:
            data_ov041_020cff48.castWait = 20;
            break;
        case CAST_STRIKE:
            data_ov041_020cff48.castWait = 20;
            break;
        case CAST_AROUND_CASTER:
            data_ov041_020cff48.castWait = 0;
            break;
        case CAST_VOLLEY:
            data_ov041_020cff48.castWait = 20;
            break;
        }
    case CAST_STATE_END:
        if (MatchesEitherSlotId(entry, action->animation) && IsEntryFlag2Set(entry)) {
            break;
        }
        if (data_ov041_020cff48.castWait > 0) {
            data_ov041_020cff48.castWait--;
            break;
        }
        FinishEntryAction(entry);
        break;
    }
    switch (action->castStyle) {
    case CAST_FROM_ABOVE:
        break;
    case CAST_STRIKE:
        if (MatchesEitherSlotId(entry, action->animation)) {
            if (frame >= 10 * FX32_ONE && frame < 11 * FX32_ONE) {
                SetPanelState(5, 10 * FX32_ONE);
            }
            if (frame >= 50 * FX32_ONE && frame < 51 * FX32_ONE) {
                SetPanelState(work->panelState, 10 * FX32_ONE);
            }
        }
        break;
    case CAST_AROUND_CASTER:
        break;
    case CAST_VOLLEY:
        if (MatchesEitherSlotId(entry, action->animation)) {
            if (frame >= 23 * FX32_ONE && frame < 24 * FX32_ONE) {
                SetPanelState(4, 10 * FX32_ONE);
            }
            if (frame >= 50 * FX32_ONE && frame < 51 * FX32_ONE) {
                SetPanelState(work->panelState, 10 * FX32_ONE);
            }
        }
        break;
    case CAST_SWEEP:
        break;
    }
    if (MatchesEitherSlotId(entry, action->animation)) {
        if (IsEntryFlag2Set(entry)) {
            if (action->castStyle == CAST_SWEEP) {
                if (frame >= 34 * FX32_ONE && frame < 35 * FX32_ONE) {
                    GetEntryMoveEnds(entry, &returnStart, &returnEnd, FALSE);
                    StartStageEntryMotion(entry, &returnStart, &returnEnd, 5 * FX32_ONE, STAGE_MOTION_EASE_OUT);
                }
                if (frame >= 34 * FX32_ONE) {
                    StepEntryMotion(entry, work->frameStep);
                }
            }
        } else {
            SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
        }
    }
    if (action->castStyle == CAST_SWEEP && MatchesEitherSlotId(entry, action->animation) && frame >= 0 &&
        frame < FX32_ONE) {
        PlayStageSound(0x44, 3, TRUE);
    }
    if (again) {
        EntryActionCast(entryIndex);
    }
}
