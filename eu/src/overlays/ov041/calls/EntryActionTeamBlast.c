#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define TEAM_RUN_TARGET 10
#define TEAM_RUN_LOW 20
#define TEAM_RUN_FIELD 30
#define TEAM_HIT 100
#define TEAM_LOW_RETURN 110 /* variant 1 rides back, then waits for its second effect */
#define TEAM_FIELD_END 120
#define TEAM_ACTION_KIND 0x10

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void ReleaseEntryStatusItem(u8 entryIndex);
extern int func_0202a9e4(u16 range);
extern void FillActionTargets(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void AimEntryPathModel(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, BOOL reverse,
                              const fx32 *scale);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern BOOL MoveEntryAlongPath(StageEntry *entry, fx32 delta);
extern void FreezeStageEntry(StageEntry *entry, int frames);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void SpawnPanelDriftPreset(int preset);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern void StartSceneFadeIn(fx32 duration);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void SetStageActorFrame(StageEntry *entry, fx32 frame);
extern void FinishEntryAction(StageEntry *entry);
extern int Anim_GetFrame(void *anim, int track);
extern void ReleaseStageItem(StageResourceItem *item);

static inline void SpawnRunDust(StageEntry *entry)
{
    VecFx32 position;

    GetEntryPosition(&position, entry);
    SpawnStageItem(entry, 0xff, 0x2a, 0, &position, FALSE);
}

/*
 * Action handler for a team blast (action kind 0x10): like the team attack, the second and third primary entries
 * join when they picked the same kind of action, which sets how long the leader waits and freezes. In one of
 * three runs the entries gather, the action's effect bursts in the middle of the field and the first entry's hit
 * lands on every target; then they ride back. For the second player kind, the burst is followed by its second
 * effect item (animation + 1), and the action ends only once that one has played.
 */
void EntryActionTeamBlast(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame;
    BOOL again = FALSE;
    int partners = 0;
    int freeze;

    if ((work->flags & 0x800) && work->entries[1].state != STAGE_ENTRY_OUT &&
        work->entries[1].actions[work->entries[1].actionIndex].kind == TEAM_ACTION_KIND) {
        partners++;
    }
    if ((work->flags & 0x400) && work->entries[2].state != STAGE_ENTRY_OUT &&
        work->entries[2].actions[work->entries[2].actionIndex].kind == TEAM_ACTION_KIND) {
        partners += 2;
    }
    frame = GetEntryAnimationFrame(entry);
    switch (entry->stateStep) {
    case 0:
        ReleaseEntryStatusItem(entry->index);
        entry->stateStep++;
    case 1:
        switch (action->variant) {
        case 0:
            entry->stateStep = TEAM_RUN_TARGET;
            switch (partners) {
            case 0:
                data_ov041_020cff48.teamLeader = 0;
                break;
            case 1:
                data_ov041_020cff48.teamLeader = 1;
                break;
            case 2:
                data_ov041_020cff48.teamLeader = 2;
                break;
            case 3:
                data_ov041_020cff48.teamLeader = func_0202a9e4(2000) / 1000 + 1;
                break;
            }
            break;
        case 1:
            entry->stateStep = TEAM_RUN_LOW;
            break;
        case 2:
            entry->stateStep = TEAM_RUN_FIELD;
            break;
        }
        again = TRUE;
        break;
    case TEAM_RUN_TARGET: {
        VecFx32 start;
        VecFx32 end;

        FillActionTargets(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 1, 1);
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x35, 0, TRUE);
        }
        entry->stateStep++;
    }
    case TEAM_RUN_TARGET + 1:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < 20 * FX32_ONE) {
            break;
        }
        freeze = 0;
        switch (partners) {
        case 0:
            freeze = 7;
            break;
        case 1:
            freeze = 0x24;
            break;
        case 2:
            freeze = 0x17;
            break;
        case 3:
            freeze = 0x30;
            break;
        }
        FreezeStageEntry(entry, FRAME_TO_FX32(freeze));
        entry->stateStep++;
    case TEAM_RUN_TARGET + 2: {
        VecFx32 middle;

        if (IsStageEntryFrozen(entry)) {
            break;
        }
        GetStageGridPosition(&middle, 1, 1);
        SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &middle, FALSE);
        if (partners == 0) {
            PlayStageSound(0x1a0, 0x18, TRUE);
        }
        entry->stateStep++;
    }
    case TEAM_RUN_TARGET + 3:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    case TEAM_RUN_LOW: {
        VecFx32 start;
        VecFx32 end;

        FillActionTargets(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 1, 1);
        end.x += 0xe66;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x42, 2, TRUE);
        }
        entry->stateStep++;
    }
    case TEAM_RUN_LOW + 1: {
        VecFx32 middle;

        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        GetStageGridPosition(&middle, 1, 1);
        entry->effects[0] =
            SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &middle, FALSE);
        if (partners == 1) {
            PlayStageSound(0x1a0, 0x19, TRUE);
        } else if (partners == 3) {
            PlayStageSound(0x1a0, 0x1a, TRUE);
        }
        SpawnPanelDriftPreset(0);
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    }
    case TEAM_RUN_FIELD:
        switch (partners) {
        case 0:
        case 1:
            break;
        case 2:
            entry->waitFrames = 0xe;
            break;
        case 3:
            entry->waitFrames = 0x27;
            break;
        }
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x43, 2, TRUE);
        }
        entry->stateStep++;
    case TEAM_RUN_FIELD + 1: {
        VecFx32 middle;

        if (entry->waitFrames > 0) {
            entry->waitFrames--;
            break;
        }
        FillActionTargets(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        SpawnRunDust(entry);
        GetStageGridPosition(&middle, 1, 1);
        SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &middle, FALSE);
        if (partners == 2) {
            PlayStageSound(0x1a0, 0x25, TRUE);
        }
        entry->stateStep++;
    }
    case TEAM_RUN_FIELD + 2:
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    case TEAM_HIT:
        if (entry->kind == 0xff) {
            ComputeEntryHit(entry, &entry->hit);
            ApplyActionToTargets(entry);
            SpawnPanelDriftPreset(1);
            StartSceneFadeIn(10 * FX32_ONE);
        }
        switch (action->variant) {
        case 0:
            entry->stateStep++;
            break;
        case 1:
            entry->stateStep = TEAM_LOW_RETURN;
            break;
        case 2:
            entry->stateStep = TEAM_FIELD_END;
            break;
        }
        again = TRUE;
        break;
    case TEAM_HIT + 1: {
        VecFx32 backStart;
        VecFx32 backEnd;

        if (!MoveEntryAlongPath(entry, work->frameStep) || IsEntryFlag2Set(entry)) {
            break;
        }
        SetSceneEntryAnimation(entry, action->recoverAnimation, 0, 0);
        SetStageActorFrame(entry, FRAME_TO_FX32(action->returnFrame));
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &backStart, &backEnd, FALSE);
        AimEntryPathModel(entry, &backStart, &backEnd, FALSE, NULL);
        entry->stateStep++;
    }
    case TEAM_HIT + 2:
        MoveEntryAlongPath(entry, work->frameStep);
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        FinishEntryAction(entry);
        break;
    case TEAM_LOW_RETURN: {
        VecFx32 backStart;
        VecFx32 backEnd;

        if (!MoveEntryAlongPath(entry, work->frameStep) || IsEntryFlag2Set(entry)) {
            break;
        }
        SetSceneEntryAnimation(entry, action->recoverAnimation, 0, 0);
        SetStageActorFrame(entry, FRAME_TO_FX32(action->returnFrame));
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &backStart, &backEnd, FALSE);
        AimEntryPathModel(entry, &backStart, &backEnd, FALSE, NULL);
        entry->stateStep++;
    }
    case TEAM_LOW_RETURN + 1:
        MoveEntryAlongPath(entry, work->frameStep);
        if (!IsEntryFlag2Set(entry)) {
            SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
            entry->stateStep++;
        }
        break;
    case TEAM_LOW_RETURN + 2:
        break;
    case TEAM_LOW_RETURN + 3:
        FinishEntryAction(entry);
        break;
    case TEAM_FIELD_END:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        FinishEntryAction(entry);
        break;
    }
    if (entry->kind == 0xfe) {
        if (entry->effects[0] != NULL) {
            if (partners == 1) {
                int effectFrame = Anim_GetFrame(&entry->effects[0]->model, 0);

                if (effectFrame >= 0x1f * FX32_ONE && effectFrame < 0x20 * FX32_ONE) {
                    VecFx32 middle;

                    ReleaseStageItem(entry->effects[0]);
                    entry->effects[0] = NULL;
                    GetStageGridPosition(&middle, 1, 1);
                    entry->effects[1] = SpawnStageItem(entry, action->effectCategory, action->effectIndex,
                                                       action->effectAnimation + 1, &middle, FALSE);
                }
            } else if (!(entry->effects[0]->flags & 4)) {
                VecFx32 middle;

                GetStageGridPosition(&middle, 1, 1);
                entry->effects[1] = SpawnStageItem(entry, action->effectCategory, action->effectIndex,
                                                   action->effectAnimation + 1, &middle, FALSE);
                entry->effects[0] = NULL;
            }
        }
        if (entry->effects[1] != NULL && !(entry->effects[1]->flags & 4) &&
            entry->stateStep == TEAM_LOW_RETURN + 2) {
            entry->stateStep++;
        }
    }
    if (again) {
        EntryActionTeamBlast(entryIndex);
    }
}
