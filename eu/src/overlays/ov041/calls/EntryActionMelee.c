#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define MELEE_COMBO 15 /* the step a combo hit starts again from */
#define MELEE_HIT 100

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void HandleTimedPressWindow(StageEntry *entry, int animation, fx32 hitFrame);
extern void PlayEntryActionSound(StageEntry *entry, fx32 frame);
extern void ChooseEntryMainTarget(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *dest);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *source, VecFx32 *dest);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void StartStagePanelTransition(const VecFx32 *target, fx32 distance, fx32 duration);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ApplyActionToTargets(StageEntry *entry);
extern u32 IsStageEntryFrozen(StageEntry *entry);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void ClearEntryActionState(StageEntry *entry);
extern void FinishStagePanelTransition(fx32 duration);

/*
 * Action handler for a melee attack: picks the target, runs up to it on the cast frame (the panel camera follows),
 * strikes on the action's hit frame and, while combo hits are left (two at most), strikes again; then walks back
 * to its place. Some steps chain into the next one in the same frame by calling the handler again.
 */
void EntryActionMelee(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    BOOL again = FALSE;
    int frame = GetEntryAnimationFrame(entry);
    VecFx32 start;
    VecFx32 end;
    VecFx32 grid;
    VecFx32 step;
    VecFx32 back;
    VecFx32 home;
    VecFx32 target;
    VecFx32 attacker;
    VecFx32 from;
    fx32 distance;

    HandleTimedPressWindow(entry, action->animation, FRAME_TO_FX32(action->effectLength));
    PlayEntryActionSound(entry, frame);
    switch (entry->stateStep) {
    case 0:
        data_ov041_020cff48.comboCount = 0;
        entry->stateStep++;
    case 1:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        entry->stateStep++;
    case 2:
        if (frame < FRAME_TO_FX32(action->castFrame)) {
            break;
        }
        entry->stateStep = 10;
        again = TRUE;
        break;
    case 10:
        SetSceneEntryAnimation(entry, (u8)(action->animation - 1), 1, 1);
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        GetStageGridPosition(&grid, 0, 1);
        end.z = grid.z;
        StartStageEntryMotion(entry, &start, &end, FRAME_TO_FX32(action->effectFrame) - FRAME_TO_FX32(action->castFrame),
                              STAGE_MOTION_EASE_OUT);
        GetPositionAboveGround(&target, work->entries);
        GetPositionAboveGround(&attacker, entry);
        VEC_Subtract(&target, &attacker, &step);
        distance = VEC_Mag(&step);
        VEC_NormalizeLength(&step, &step);
        ScaleVecFx32(FX_Mul(distance, 0xb33), &step, &step);
        GetPositionAboveGround(&from, entry);
        VEC_Add(&from, &step, &step);
        StartStagePanelTransition(&step, (work->flags & STAGE_WORK_PANEL_MOVING) ? 0x19 << 14 : 0x15 << 14,
                                  5 * FX32_ONE);
        entry->stateStep++;
    case 11:
        if (!StepEntryMotion(entry, work->frameStep)) {
            break;
        }
        SetSceneEntryAnimation(entry, action->animation, 1, 1);
        frame = GetEntryAnimationFrame(entry);
        PlayEntryActionSound(entry, frame);
        entry->stateStep++;
    case 12:
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = MELEE_HIT;
        again = TRUE;
        break;
    case MELEE_COMBO:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            entry->stateStep = MELEE_HIT + 2;
            return;
        }
        SetSceneEntryAnimation(entry, action->animation, 1, 1);
        frame = GetEntryAnimationFrame(entry);
        PlayEntryActionSound(entry, frame);
        entry->stateStep++;
    case 16:
        entry->stateStep++;
    case 17:
        if (frame < FRAME_TO_FX32(action->effectLength)) {
            break;
        }
        entry->stateStep = MELEE_HIT;
        again = TRUE;
        break;
    case MELEE_HIT:
        ComputeEntryHit(entry, &entry->hit);
        ApplyActionToTargets(entry);
        entry->stateStep++;
    case MELEE_HIT + 1:
        if (IsStageEntryFrozen(entry) || IsEntryFlag2Set(entry)) {
            break;
        }
        if (data_ov041_020cff48.comboCount < 2) {
            data_ov041_020cff48.comboCount++;
            entry->stateStep = MELEE_COMBO;
            again = TRUE;
            ClearEntryActionState(entry);
            break;
        }
        entry->stateStep++;
    case MELEE_HIT + 2:
        SetSceneEntryAnimation(entry, (u8)(action->animation + 1), 1, 0);
        GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &back, &home, FALSE);
        StartStageEntryMotion(entry, &back, &home,
                              FRAME_TO_FX32(action->returnEndFrame) - FRAME_TO_FX32(action->returnFrame),
                              STAGE_MOTION_EASE_OUT);
        FinishStagePanelTransition(5 * FX32_ONE);
        entry->stateStep++;
    case MELEE_HIT + 3:
        if (!StepEntryMotion(entry, work->frameStep) || IsEntryFlag2Set(entry)) {
            break;
        }
        entry->stateStep++;
    case MELEE_HIT + 4:
        FinishEntryAction(entry);
        return;
    }
    if (again) {
        EntryActionMelee(entryIndex);
    }
}
