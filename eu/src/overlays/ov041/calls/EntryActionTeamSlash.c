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
#define TEAM_ACTION_KIND 0xf
#define SLASH_HEIGHT 0x19a /* how far above the end of the run the slash shows */

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
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void FaceStageItemAlong(StageResourceItem *item, const VecFx32 *direction);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ForEachActionTarget(StageEntry *entry, int seqArcNo, int soundIndex);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void SetStageActorFrame(StageEntry *entry, fx32 frame);
extern void FinishEntryAction(StageEntry *entry);

static inline void SpawnRunDust(StageEntry *entry)
{
    VecFx32 position;

    GetEntryPosition(&position, entry);
    SpawnStageItem(entry, 0xff, 0x26, 0, &position, FALSE);
}

/*
 * Action handler for a team slash (action kind 0xf): the second and third primary entries join as in the team
 * attack. In the first and third runs the entries leap to the target's column and slash through it, the slash
 * effect showing across their path; in the second the attacker charges up and a slash crosses the target's column,
 * then a second slash follows the first entry's path. The first player kind's hit plays a sound for the team that
 * joined; afterwards the entries ride back.
 */
void EntryActionTeamSlash(u8 entryIndex)
{
    StageEntry *entry;
    StageEntryAction *action;
    StageWork *work;
    int frame;
    BOOL again;
    int partners;

    work = gMovieContextState->stageWork;
    entry = &work->entries[entryIndex];
    action = GetEntryAction(entry);
    again = FALSE;
    partners = 0;
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
            entry->waitFrames = 0;
            break;
        case 1:
            entry->waitFrames = 0x16;
            break;
        case 2:
            entry->waitFrames = 0;
            break;
        case 3:
            entry->waitFrames = 0x16;
            break;
        }
        entry->stateStep++;
    case TEAM_RUN_TARGET + 1: {
        VecFx32 start;
        VecFx32 end;

        if (entry->waitFrames > 0) {
            entry->waitFrames--;
            break;
        }
        FillActionTargets(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 2, work->entries[entry->mainTarget].column);
        end.z -= FX32_ONE;
        end.x += 0x2800;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x35, 0, TRUE);
        }
        entry->stateStep++;
    }
    case TEAM_RUN_TARGET + 2: {
        VecFx32 start;
        VecFx32 end;

        if (!MoveEntryAlongPath(entry, work->frameStep)) {
            break;
        }
        SetSceneEntryAnimation(entry, (u8)(action->animation + 1), 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 0, work->entries[entry->mainTarget].column);
        end.z += FX32_ONE;
        end.x -= 0x800;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        entry->move.motion.start = start;
        entry->move.motion.end = end;
        entry->stateStep++;
    }
    case TEAM_RUN_TARGET + 3:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame >= 6 * FX32_ONE && frame < 7 * FX32_ONE) {
            VecFx32 direction;
            VecFx32 position;
            MtxFx33 turn;
            StageResourceItem *item;

            VEC_Subtract(&entry->move.motion.end, &entry->move.motion.start, &direction);
            MTX_RotY33_(&turn, -FX32_ONE, 0);
            MTX_MultVec33(&direction, &turn, &direction);
            position = entry->move.motion.end;
            position.y += SLASH_HEIGHT;
            item = SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position,
                                  FALSE);
            if (item != NULL) {
                FaceStageItemAlong(item, &direction);
            }
        }
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    case TEAM_RUN_LOW:
        FillActionTargets(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        SpawnRunDust(entry);
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x42, 2, TRUE);
        }
        entry->stateStep++;
    case TEAM_RUN_LOW + 1: {
        VecFx32 position;

        if (frame < 11 * FX32_ONE) {
            break;
        }
        GetStageGridPosition(&position, 2, work->entries[entry->mainTarget].column);
        position.z -= FX32_ONE;
        position.x += 0x2800;
        position.x -= FX32_ONE;
        position.y += SLASH_HEIGHT;
        SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position, FALSE);
        PlayStageSound(0x1a0, 0x2a, TRUE);
        entry->stateStep++;
    }
    case TEAM_RUN_LOW + 2:
        if (frame < 36 * FX32_ONE) {
            break;
        } else {
            VecFx32 direction;
            VecFx32 position;
            MtxFx33 turn;
            StageResourceItem *item;

            VEC_Subtract(&work->entries[0].move.motion.end, &work->entries[0].move.motion.start, &direction);
            MTX_RotY33_(&turn, -FX32_ONE, 0);
            MTX_MultVec33(&direction, &turn, &direction);
            position = work->entries[0].move.motion.end;
            position.y += SLASH_HEIGHT;
            item = SpawnStageItem(entry, action->aimEffectCategory, action->aimEffectIndex, action->aimEffectAnimation,
                                  &position, FALSE);
            if (item != NULL) {
                FaceStageItemAlong(item, &direction);
            }
        }
        entry->stateStep = TEAM_HIT + 3;
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
            entry->waitFrames = 0x16;
            break;
        }
        if (data_ov041_020cff48.teamLeader == entry->index) {
            PlayStageSound(0x43, 2, TRUE);
        }
        entry->stateStep++;
    case TEAM_RUN_FIELD + 1: {
        VecFx32 start;
        VecFx32 end;

        if (entry->waitFrames > 0) {
            entry->waitFrames--;
            break;
        }
        FillActionTargets(entry);
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 2, work->entries[entry->mainTarget].column);
        end.z += FX32_ONE;
        end.x += 0x2800;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        entry->stateStep++;
    }
    case TEAM_RUN_FIELD + 2: {
        VecFx32 start;
        VecFx32 end;

        if (!MoveEntryAlongPath(entry, work->frameStep)) {
            break;
        }
        SetSceneEntryAnimation(entry, (u8)(action->animation + 1), 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 0, work->entries[entry->mainTarget].column);
        end.z -= FX32_ONE;
        end.x -= 0x800;
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        entry->move.motion.start = start;
        entry->move.motion.end = end;
        entry->stateStep++;
    }
    case TEAM_RUN_FIELD + 3:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame >= 6 * FX32_ONE && frame < 7 * FX32_ONE) {
            VecFx32 direction;
            VecFx32 position;
            MtxFx33 turn;
            StageResourceItem *item;

            VEC_Subtract(&entry->move.motion.end, &entry->move.motion.start, &direction);
            MTX_RotY33_(&turn, -FX32_ONE, 0);
            MTX_MultVec33(&direction, &turn, &direction);
            position = entry->move.motion.end;
            position.y += SLASH_HEIGHT;
            item = SpawnStageItem(entry, action->effectCategory, action->effectIndex, action->effectAnimation, &position,
                                  FALSE);
            if (item != NULL) {
                FaceStageItemAlong(item, &direction);
            }
        }
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = TEAM_HIT;
        again = TRUE;
        break;
    case TEAM_HIT:
        if (entry->kind == 0xff) {
            int sound = 0x15;

            switch (partners) {
            case 0:
                sound = 0x15;
                break;
            case 1:
                sound = 0x16;
                break;
            case 2:
                sound = 0x24;
                break;
            case 3:
                sound = 0x17;
                break;
            }
            ComputeEntryHit(entry, &entry->hit);
            ForEachActionTarget(entry, 0x1a0, sound);
        }
        switch (action->variant) {
        case 0:
            entry->stateStep++;
            break;
        case 1:
            entry->stateStep = TEAM_HIT + 3;
            break;
        case 2:
            entry->stateStep++;
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
    case TEAM_HIT + 3:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        FinishEntryAction(entry);
        break;
    }
    if (again) {
        EntryActionTeamSlash(entryIndex);
    }
}
