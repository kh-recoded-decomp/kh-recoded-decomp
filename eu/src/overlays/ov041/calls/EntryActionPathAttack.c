#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define PATH_RUN_TARGET 10 /* variant 0: run through the target */
#define PATH_RUN_COLUMN 20 /* variant 1: run along the target's column */
#define PATH_RUN_FIELD 30 /* variant 2: run across the middle of the field */
#define PATH_HIT 100

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void ReleaseEntryStatusItem(u8 entryIndex);
extern void func_ov041_020c3c88(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void AimEntryPathModel(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, BOOL reverse,
                              const fx32 *scale);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern BOOL MoveEntryAlongPath(StageEntry *entry, fx32 delta);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void SpawnPanelDriftPreset(int preset);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void StartSceneFadeIn(fx32 duration);
extern void SetStageActorFrame(StageEntry *entry, fx32 frame);
extern void FinishEntryAction(StageEntry *entry);

/*
 * Action handler for a path attack: in one of three runs (through the target, along its column, or across the
 * middle of the field) the entry follows its path model, then the hit lands with the action's effect item and
 * a sound per run, and it rides the path back while its recover animation plays. Some steps chain into the
 * next one in the same frame by calling the handler again.
 */
void EntryActionPathAttack(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    BOOL again = FALSE;
    int frame = GetEntryAnimationFrame(entry);
    int sound;

    switch (entry->stateStep) {
    case 0:
        ReleaseEntryStatusItem(entry->index);
        entry->stateStep++;
    case 1:
        switch (action->variant) {
        case 0:
            entry->stateStep = PATH_RUN_TARGET;
            break;
        case 1:
            entry->stateStep = PATH_RUN_COLUMN;
            break;
        case 2:
            entry->stateStep = PATH_RUN_FIELD;
            break;
        }
        again = TRUE;
        break;
    case PATH_RUN_TARGET: {
        VecFx32 start;
        VecFx32 end;

        func_ov041_020c3c88(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        PlayStageSound(0x30, 3, TRUE);
        entry->stateStep++;
    }
    case PATH_RUN_TARGET + 1:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = PATH_HIT;
        again = TRUE;
        break;
    case PATH_RUN_COLUMN: {
        VecFx32 start;
        VecFx32 end;

        func_ov041_020c3c88(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        GetEntryAnimationFrame(entry);
        PlayStageSound(0x30, 3, TRUE);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 2, work->entries[entry->mainTarget].column);
        end.x = 0;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        entry->stateStep++;
    }
    case PATH_RUN_COLUMN + 1: {
        VecFx32 start;
        VecFx32 end;

        if (!MoveEntryAlongPath(entry, work->frameStep)) {
            break;
        }
        SetSceneEntryAnimation(entry, (u8)(action->animation + 1), 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 0, work->entries[entry->mainTarget].column);
        end.x -= FX32_ONE;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        entry->stateStep++;
    }
    case PATH_RUN_COLUMN + 2:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = PATH_HIT;
        again = TRUE;
        break;
    case PATH_RUN_FIELD: {
        VecFx32 start;
        VecFx32 end;

        func_ov041_020c3c88(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        PlayStageSound(0x35, 0, TRUE);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 1, 1);
        end.x += FX_Mul(entry->radius, 0x199a);
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        entry->stateStep++;
    }
    case PATH_RUN_FIELD + 1:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        again = TRUE;
        SpawnPanelDriftPreset(1);
        entry->stateStep = PATH_HIT;
        break;
    case PATH_HIT: {
        VecFx32 position;

        ComputeEntryHit(entry, &entry->hit);
        ApplyActionToTargets(entry);
        sound = 0xff;
        switch (action->variant) {
        case 0:
            GetPositionAboveGround(&position, &work->entries[entry->mainTarget]);
            position.y += 0x19a;
            sound = 0xf;
            break;
        case 1:
            GetStageGridPosition(&position, 1, work->entries[entry->mainTarget].column);
            sound = 0x10;
            break;
        case 2:
            GetStageGridPosition(&position, 1, 1);
            sound = 0x11;
            break;
        }
        SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position, FALSE);
        PlayStageSound(0x1a0, sound, TRUE);
        entry->stateStep++;
    }
    case PATH_HIT + 1: {
        VecFx32 start;
        VecFx32 end;

        MoveEntryAlongPath(entry, work->frameStep);
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        if (action->variant == 2) {
            StartSceneFadeIn(10 * FX32_ONE);
        }
        SetSceneEntryAnimation(entry, action->recoverAnimation, 0, 0);
        SetStageActorFrame(entry, FRAME_TO_FX32(action->returnFrame));
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, FALSE);
        AimEntryPathModel(entry, &start, &end, FALSE, NULL);
        entry->stateStep++;
    }
    case PATH_HIT + 2:
        MoveEntryAlongPath(entry, work->frameStep);
        if (!IsEntryFlag2Set(entry)) {
            FinishEntryAction(entry);
        }
        break;
    }
    if (again) {
        EntryActionPathAttack(entryIndex);
    }
}
