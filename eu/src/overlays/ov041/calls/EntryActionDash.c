#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* This handler is built without common subexpression elimination or loop rotation. */
#pragma opt_common_subs off
#pragma opt_rotateloops off

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

extern const char data_ov041_020cf720[];
extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern s32 GetHudLabelId(int labelIndex);
extern void ShowFieldMessageLine_02072ad0(int kind, ...);
extern int PickStageTarget(int mode);
extern void func_ov041_020c3c88(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void GetEntryPosition(VecFx32 *position, StageEntry *entry);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void AimEntryPathModel(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, BOOL reverse,
                              const fx32 *scale);
extern int NNS_G3dGetResDictIdxByName(const void *dict, const char *name);
extern BOOL MoveEntryAlongPath(StageEntry *entry, fx32 delta);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionHit(StageEntry *entry, u8 targetIndex, BOOL pressCheck);
extern void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry);
extern StageResourceItem *SpawnStageResourceItem(int category, u8 index, u8 animation, const VecFx32 *position,
                                                 BOOL persistent);

static inline VecFx32 AboveGroundOf(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    return position;
}

/*
 * Action handler for a dash: shows its caption and opening effect, then the attacker steps to the front row of
 * the target's column and runs across the field along its path, a burst flaring from its root bone just before
 * the cast frame. Every target it passes is hit once (STAGE_ENTRY_STRUCK) with a spark over it; afterwards it plays
 * its windup animation again and walks back.
 */
void EntryActionDash(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    int frame = GetEntryAnimationFrame(entry);
    BOOL again = FALSE;
    VecFx32 start;
    VecFx32 end;
    VecFx32 from;
    VecFx32 to;
    VecFx32 shown;
    VecFx32 burst;
    VecFx32 backStart;
    VecFx32 backEnd;
    int i;

    switch (entry->stateStep) {
    case 0:
        again = FALSE;
        data_ov041_020cff48.comboCount = 0;
        data_ov041_020cff48.unk00 = 0;
        data_ov041_020cff48.castTimer = 0;
        entry->stateStep++;
    case 1: {
        VecFx32 position;

        GetPositionAboveGround(&position, entry);
        entry->effects[0] = SpawnStageItem(entry, 0xff, 0x14, 0, &position, FALSE);
        PlayStageSound(0x1a0, 6, TRUE);
        ShowFieldMessageLine_02072ad0(0x11, GetHudLabelId(0xee));
        entry->stateStep++;
    }
    case 2:
        if (entry->effects[0]->flags & 4) {
            break;
        }
        entry->mainTarget = PickStageTarget(action->targetKind);
        func_ov041_020c3c88(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        SetSceneEntryAnimation(entry, action->windupAnimation, 1, 0);
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&end, 2, work->entries[entry->mainTarget].column);
        end.x += 3 * FX32_ONE;
        StartStageEntryMotion(entry, &start, &end,
                              FRAME_TO_FX32(action->returnEndFrame) - FRAME_TO_FX32(action->returnFrame),
                              STAGE_MOTION_EASE_OUT);
        PlayStageSound(0x42, 2, TRUE);
        entry->stateStep++;
    case 3:
        if (!StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        entry->stateStep++;
    case 4:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        SetSceneEntryAnimation(entry, action->animation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        GetEntryPosition(&from, entry);
        GetPositionAboveGround(&to, &work->entries[entry->mainTarget]);
        to.x = -8 * FX32_ONE;
        if (gMovieContextState->stageWork->flags & 0x40) {
            to.x = FX_Mul(to.x, 0x1ccd);
        }
        entry->move.motion.start = from;
        entry->move.motion.end = to;
        AimEntryPathModel(entry, &entry->move.motion.start, &entry->move.motion.end, TRUE, NULL);
        {
            VecFx32 position;

            GetPositionAboveGround(&position, entry);
            shown = position;
        }
        SpawnStageItem(entry, 0xff, 0x2f, 0, &shown, FALSE);
        PlayStageSound(0x1a0, 0x28, TRUE);
        entry->stateStep++;
    case 5:
        if (frame < FRAME_TO_FX32(action->castFrame)) {
            if (frame == FRAME_TO_FX32(action->castFrame - 1)) {
                VecFx32 position;
                void *dict;

                GetPositionAboveGround(&position, entry);
                burst = position;
                dict = NULL;
                burst.x -= 0x2666;
                entry->effects[0] = SpawnStageItem(entry, 0xff, 0x30, 0, &burst, FALSE);
                if (entry->slot.node.modelResource != NULL) {
                    dict = (u8 *)entry->slot.node.modelResource + 0x40;
                }
                entry->effects[0]->variant = dict != NULL ? NNS_G3dGetResDictIdxByName(dict, data_ov041_020cf720) : -1;
                entry->effects[0]->flags |= 0x10;
            }
            MoveEntryAlongPath(entry, work->frameStep);
            break;
        }
        entry->stateStep++;
    case 6:
        for (i = 0; i < entry->targetCount; i++) {
            StageEntry *target = &work->entries[entry->targets[i]];

            if (target->state != STAGE_ENTRY_OUT && !(target->flags & STAGE_ENTRY_STRUCK)) {
                VecFx32 here;
                VecFx32 there;

                GetPositionAboveGround(&here, entry);
                GetPositionAboveGround(&there, &work->entries[entry->targets[i]]);
                if (here.x - entry->radius < there.x) {
                    VecFx32 overhead;

                    ComputeEntryHit(entry, &entry->hit);
                    ApplyActionHit(entry, entry->targets[i], FALSE);
                    GetEntryOverheadPosition(&overhead, &work->entries[entry->targets[i]]);
                    SpawnStageResourceItem(0xff, 0x31, 0, &overhead, FALSE);
                    work->entries[entry->targets[i]].flags |= STAGE_ENTRY_STRUCK;
                }
            }
        }
        if (!MoveEntryAlongPath(entry, work->frameStep)) {
            break;
        }
        entry->stateStep++;
    case 7:
        SetSceneEntryAnimation(entry, action->windupAnimation, 1, 0);
        frame = GetEntryAnimationFrame(entry);
        entry->stateStep++;
    case 8:
        if (frame < FRAME_TO_FX32(action->returnFrame)) {
            break;
        }
        GetEntryMoveEnds(entry, &backStart, &backEnd, FALSE);
        StartStageEntryMotion(entry, &backStart, &backEnd,
                              FRAME_TO_FX32(action->returnEndFrame) - FRAME_TO_FX32(action->returnFrame),
                              STAGE_MOTION_EASE_OUT);
        entry->stateStep++;
    case 9:
        if (!StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        entry->stateStep++;
    case 10:
        if (!IsEntryFlag2Set(entry)) {
            FinishEntryAction(entry);
        }
        break;
    }
    if (again) {
        EntryActionDash(entryIndex);
    }
}
