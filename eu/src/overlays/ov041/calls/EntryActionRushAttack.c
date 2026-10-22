#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define RUSH_STEP 10 /* attackStyle 0: step in (kind 0x10 runs its path instead) */
#define RUSH_EFFECT 20 /* attackStyle 1: rush in behind the rush effect */
#define RUSH_DASH 30 /* attackStyle 2: dash in with the rush effect */
#define RUSH_LEAP 40 /* attackStyle 3: leap to the front row */
#define RUSH_HIT 100

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void PlayEntryActionSound(StageEntry *entry, fx32 frame);
extern void HandleTimedPressWindow(StageEntry *entry, int animation, fx32 hitFrame);
extern void ReleaseEntryStatusItem(u8 entryIndex);
extern void ChooseEntryMainTarget(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void AimEntryPathModel(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, BOOL reverse,
                              const fx32 *scale);
extern BOOL MoveEntryAlongPath(StageEntry *entry, fx32 delta);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern void GetStrikePosition(VecFx32 *out, StageEntry *attacker, StageEntry *target, StageEntryAction *action);
extern void StartStagePanelTransition(const VecFx32 *target, fx32 distance, fx32 duration);
extern void FinishStagePanelTransition(fx32 duration);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void MI_Copy48B(const void *src, void *dest);
extern void StartStageMotion(VecFx32 *position, StageMotion *motion, const VecFx32 *start, const VecFx32 *end,
                             fx32 duration, int profile);
extern BOOL StepStageMotion(VecFx32 *position, StageMotion *motion, fx32 step);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void SpawnPanelDriftPreset(int preset);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern u32 IsEntryFlag2Set(StageEntry *entry);

static inline StageResourceItem *SpawnRushEffect(StageEntry *entry, StageEntryAction *action)
{
    VecFx32 position;

    GetEntryPosition(&position, entry);
    return SpawnStageItem(entry, action->rushEffectCategory, action->rushEffectIndex, action->rushEffectAnimation,
                          &position, FALSE);
}

/* Moves the rush effect along with the attacker until its animation is over, then lets go of it. */
static inline void StepRushEffect(StageEntry *entry, StageWork *work)
{
    StageResourceItem *item = entry->effects[0];

    if (item != NULL) {
        if (item->flags & 4) {
            StepStageMotion(&item->model.position, &item->model.motion, work->frameStep);
        } else {
            entry->effects[0] = NULL;
        }
    }
}

/*
 * Action handler for an enemy's rush attack: after the cast frame the attacker closes in by its attackStyle -
 * stepping (kind 0x10 follows its path), rushing behind the rush effect, dashing with it, or leaping to the front
 * row and leaving it behind - while the panel moves toward the strike position. On the effect frame count the hit
 * lands on every target; after the return frame the attacker goes back (kind 3 and path movers stay) and the
 * action ends.
 */
void EntryActionRushAttack(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame;
    BOOL again = FALSE;
    int profile;

    frame = GetEntryAnimationFrame(entry);
    PlayEntryActionSound(entry, frame);
    HandleTimedPressWindow(entry, action->animation, FRAME_TO_FX32(action->effectLength));
    switch (entry->stateStep) {
    case 0: {
        VecFx32 start;
        VecFx32 end;

        ReleaseEntryStatusItem(entry->index);
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        PlayEntryActionSound(entry, frame);
        if (entry->kind == 3 || (entry->kind == 0x10 && action->attackStyle == 0)) {
            GetEntryMoveEnds(entry, &start, &end, TRUE);
            AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        }
        entry->stateStep++;
    }
    case 1:
        if (entry->kind == 3 || (entry->kind == 0x10 && action->attackStyle == 0)) {
            MoveEntryAlongPath(entry, work->frameStep);
        }
        if (frame < FRAME_TO_FX32(action->castFrame)) {
            break;
        }
        switch (action->attackStyle) {
        case 0:
            entry->stateStep = RUSH_STEP;
            break;
        case 1:
            entry->stateStep = RUSH_EFFECT;
            break;
        case 2:
            entry->stateStep = RUSH_DASH;
            break;
        case 3:
            entry->stateStep = RUSH_LEAP;
            break;
        }
        again = TRUE;
        break;
    case RUSH_STEP: {
        VecFx32 start;
        VecFx32 end;
        VecFx32 strike;

        if (entry->kind != 0x10 || action->attackStyle != 0) {
            profile = STAGE_MOTION_EASE_OUT;
            if (entry->kind == 0xb) {
                profile = STAGE_MOTION_STEADY;
            }
            GetEntryMoveEnds(entry, &start, &end, TRUE);
            StartStageEntryMotion(entry, &start, &end,
                                  FRAME_TO_FX32(action->effectFrame) - FRAME_TO_FX32(action->castFrame), profile);
        }
        GetStrikePosition(&strike, entry, &work->entries[entry->mainTarget], action);
        StartStagePanelTransition(&strike, (work->flags & STAGE_WORK_PANEL_MOVING) ? 0x19 << 14 : 0x15 << 14,
                                  5 * FX32_ONE);
        entry->stateStep++;
    }
    case RUSH_STEP + 1:
        if ((entry->kind != 0x10 || action->attackStyle != 0) && !StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        entry->stateStep++;
    case RUSH_STEP + 2:
        if (entry->kind == 0x10 && action->attackStyle == 0) {
            MoveEntryAlongPath(entry, work->frameStep);
        }
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = RUSH_HIT;
        again = TRUE;
        break;
    case RUSH_EFFECT: {
        VecFx32 start;
        VecFx32 end;
        VecFx32 strike;

        entry->effects[0] = SpawnRushEffect(entry, action);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        if (entry->kind != 3) {
            StartStageEntryMotion(entry, &start, &end,
                                  FRAME_TO_FX32(action->effectFrame) - FRAME_TO_FX32(action->castFrame),
                                  STAGE_MOTION_STEADY);
        }
        if (entry->effects[0] != NULL) {
            MI_Copy48B(&entry->slot.node.rotation, &entry->effects[0]->model.rotation);
            StartStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, &start, &end,
                             FRAME_TO_FX32(action->effectFrame) - FRAME_TO_FX32(action->castFrame),
                             STAGE_MOTION_STEADY);
        }
        GetStrikePosition(&strike, entry, &work->entries[entry->mainTarget], action);
        StartStagePanelTransition(&strike, (work->flags & STAGE_WORK_PANEL_MOVING) ? 0x19 << 14 : 0x15 << 14,
                                  5 * FX32_ONE);
        entry->stateStep++;
    }
    case RUSH_EFFECT + 1:
        if (entry->kind != 3) {
            StepRushEffect(entry, work);
            if (!StepEntryMotion(entry, work->frameStep)) {
                break;
            }
        }
        entry->stateStep++;
    case RUSH_EFFECT + 2:
        if (entry->kind == 3) {
            MoveEntryAlongPath(entry, work->frameStep);
            StepRushEffect(entry, work);
        }
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = RUSH_HIT;
        again = TRUE;
        break;
    case RUSH_DASH: {
        VecFx32 start;
        VecFx32 end;

        entry->effects[0] = SpawnRushEffect(entry, action);
        MI_Copy48B(&entry->slot.node.rotation, &entry->effects[0]->model.rotation);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        StartStageEntryMotion(entry, &start, &end,
                              FRAME_TO_FX32(action->effectFrame) - FRAME_TO_FX32(action->castFrame),
                              STAGE_MOTION_EASE_OUT);
        StartStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, &start, &end,
                         FRAME_TO_FX32(action->effectFrame) - FRAME_TO_FX32(action->castFrame), STAGE_MOTION_EASE_OUT);
        entry->stateStep++;
    }
    case RUSH_DASH + 1:
        StepStageMotion(&entry->effects[0]->model.position, &entry->effects[0]->model.motion, work->frameStep);
        if (!StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        entry->stateStep++;
    case RUSH_DASH + 2:
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = RUSH_HIT;
        again = TRUE;
        break;
    case RUSH_LEAP: {
        VecFx32 start;
        VecFx32 end;
        VecFx32 grid;

        GetEntryMoveEnds(entry, &start, &grid, TRUE);
        end.x = grid.x - (6 << 10);
        GetStageGridPosition(&grid, 0, 1);
        end.y = 0;
        end.z = grid.z;
        StartStageEntryMotion(entry, &start, &end,
                              FRAME_TO_FX32(action->effectFrame) - FRAME_TO_FX32(action->castFrame),
                              STAGE_MOTION_EASE_OUT);
        entry->stateStep++;
    }
    case RUSH_LEAP + 1:
        if (!StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        entry->stateStep++;
    case RUSH_LEAP + 2:
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        SpawnRushEffect(entry, action);
        again = TRUE;
        SpawnPanelDriftPreset(1);
        entry->stateStep = RUSH_HIT;
        break;
    case RUSH_HIT:
        entry->stateStep++;
    case RUSH_HIT + 1:
        ComputeEntryHit(entry, &entry->hit);
        ApplyActionToTargets(entry);
        entry->stateStep++;
    case RUSH_HIT + 2: {
        VecFx32 backStart;
        VecFx32 backEnd;

        if (IsStageEntryFrozen(entry)) {
            break;
        }
        if (frame < FRAME_TO_FX32(action->returnFrame)) {
            MoveEntryAlongPath(entry, work->frameStep);
            break;
        }
        if (!(entry->kind == 3 && action->attackStyle == 1) && !(entry->kind == 0x10 && action->attackStyle == 0)) {
            profile = STAGE_MOTION_EASE_OUT;
            GetEntryMoveEnds(entry, &backStart, &backEnd, FALSE);
            if (entry->kind == 3) {
                profile = STAGE_MOTION_STEADY;
            }
            StartStageEntryMotion(entry, &backStart, &backEnd,
                                  FRAME_TO_FX32(action->returnEndFrame) - FRAME_TO_FX32(action->returnFrame), profile);
        }
        FinishStagePanelTransition(5 * FX32_ONE);
        entry->stateStep++;
    }
    case RUSH_HIT + 3:
        MoveEntryAlongPath(entry, work->frameStep);
        if (!StepEntryMotion(entry, work->frameStep) || IsEntryFlag2Set(entry)) {
            break;
        }
        entry->stateStep++;
    case RUSH_HIT + 4:
        FinishEntryAction(entry);
        break;
    }
    if (again) {
        EntryActionRushAttack(entryIndex);
    }
}
