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
#define TEAM_ACTION_KIND 0xe

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void ReleaseEntryStatusItem(u8 entryIndex);
extern int func_0202a9e4(u16 range);
extern void func_ov041_020c3c88(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void AimEntryPathModel(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, BOOL reverse,
                              const fx32 *scale);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern BOOL MoveEntryAlongPath(StageEntry *entry, fx32 delta);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void SetStageActorFrame(StageEntry *entry, fx32 frame);
extern void FinishEntryAction(StageEntry *entry);

/*
 * Action handler for a team attack: the second and third primary entries join when they picked the same kind of
 * action (bits 1 and 2 of partners), which staggers the runs and picks the leader whose voice plays. In one of
 * three runs each entry follows its path model; the leader's hit spawns the effect item with a cheer for the
 * team that joined, then the entries ride back. Some steps chain into the next one in the same frame.
 */
void EntryActionTeamAttack(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame;
    BOOL again = FALSE;
    int partners = 0;
    VecFx32 start;
    VecFx32 end;
    VecFx32 lowStart;
    VecFx32 lowEnd;
    VecFx32 backStart;
    VecFx32 backEnd;

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
        entry->waitFrames = 0;
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
    case TEAM_RUN_TARGET:
        switch (partners) {
        case 0:
            break;
        case 1:
            entry->waitFrames = 11;
            break;
        case 2:
            entry->waitFrames = 2;
            break;
        case 3:
            entry->waitFrames = 11;
            break;
        }
        entry->stateStep++;
    case TEAM_RUN_TARGET + 1:
        if (entry->waitFrames > 0) {
            entry->waitFrames--;
            break;
        }
        func_ov041_020c3c88(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        end.z += 0x99a;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x35, 0, TRUE);
        }
        entry->stateStep++;
    case TEAM_RUN_TARGET + 2:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    case TEAM_RUN_LOW:
        entry->stateStep++;
    case TEAM_RUN_LOW + 1:
        func_ov041_020c3c88(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &lowStart, &lowEnd, TRUE);
        lowEnd.z -= 0x99a;
        AimEntryPathModel(entry, &lowStart, &lowEnd, TRUE, NULL);
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x42, 2, TRUE);
        }
        entry->stateStep++;
    case TEAM_RUN_LOW + 2:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    case TEAM_RUN_FIELD:
        switch (partners) {
        case 0:
        case 1:
            break;
        case 2:
            entry->waitFrames = 0;
            break;
        case 3:
            entry->waitFrames = 9;
            break;
        }
        entry->stateStep++;
    case TEAM_RUN_FIELD + 1:
        if (entry->waitFrames > 0) {
            entry->waitFrames--;
            break;
        }
        func_ov041_020c3c88(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x43, 2, TRUE);
        }
        entry->stateStep++;
    case TEAM_RUN_FIELD + 2:
        if (frame >= 5 * FX32_ONE && frame < 6 * FX32_ONE) {
            VecFx32 position;

            GetEntryPosition(&position, entry);
            SpawnStageItem(entry, 0xff, 0x22, 0, &position, FALSE);
        }
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    case TEAM_HIT: {
        VecFx32 position;

        if (entry->kind == 0xff) {
            ComputeEntryHit(entry, &entry->hit);
            ApplyActionToTargets(entry);
        }
        GetPositionAboveGround(&position, &work->entries[entry->mainTarget]);
        SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position, FALSE);
        PlayStageSound(0x1a0, action->soundIndex, TRUE);
        switch (partners) {
        case 0:
            PlayStageSound(0x1a0, 0x12, TRUE);
            break;
        case 1:
            if (entry->kind == 0xfe) {
                PlayStageSound(0x1a0, 0x13, TRUE);
            }
            break;
        case 2:
            if (entry->kind == 0xff) {
                PlayStageSound(0x1a0, 0x23, TRUE);
            }
            break;
        case 3:
            if (entry->kind == 0xfe) {
                PlayStageSound(0x1a0, 0x14, TRUE);
            }
            break;
        }
        switch (action->variant) {
        case 0:
            entry->stateStep++;
            break;
        case 1:
            entry->stateStep++;
            break;
        case 2:
            entry->stateStep = TEAM_HIT + 3;
            break;
        }
        again = TRUE;
        break;
    }
    case TEAM_HIT + 1:
        MoveEntryAlongPath(entry, work->frameStep);
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        SetSceneEntryAnimation(entry, action->recoverAnimation, 0, 0);
        SetStageActorFrame(entry, FRAME_TO_FX32(action->returnFrame));
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &backStart, &backEnd, FALSE);
        AimEntryPathModel(entry, &backStart, &backEnd, FALSE, NULL);
        entry->stateStep++;
    case TEAM_HIT + 2:
        MoveEntryAlongPath(entry, work->frameStep);
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        FinishEntryAction(entry);
        break;
    case TEAM_HIT + 3:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        FinishEntryAction(entry);
        break;
    }
    if (again) {
        EntryActionTeamAttack(entryIndex);
    }
}
