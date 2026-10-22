#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole frame count as fx32, rounded half away from zero (converted once, after the rounding). */
#define FRAME_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define COMBO_ATTACK 10 /* runs one of the follow-up attacks */
#define COMBO_HIT 100
#define COMBO_FINISHER 3

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern s32 GetHudLabelId(int labelIndex);
extern void ShowFieldMessageLine_02072ad0(int kind, ...);
extern int func_0202a9e4(u16 range);
extern void ChooseEntryMainTarget(StageEntry *entry);
extern void FinishEntryAction(StageEntry *entry);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetEntryMoveEnds(StageEntry *entry, VecFx32 *start, VecFx32 *end, BOOL toTarget);
extern void AimEntryPathModel(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, BOOL reverse,
                              const fx32 *scale);
extern BOOL MoveEntryAlongPath(StageEntry *entry, fx32 delta);
extern BOOL IsStageEntryFrozen(StageEntry *entry);
extern void ComputeEntryHit(StageEntry *entry, StageEntryHit *hit);
extern void ForEachActionTarget(StageEntry *entry, int seqArcNo, int soundIndex);
extern void StartSceneFadeIn(fx32 duration);
extern void MI_Copy48B(const void *src, void *dest);
extern u8 CountActiveStageEntries(BOOL primary);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void ClearEntryActionState(StageEntry *entry);
extern void SetStageActorFrame(StageEntry *entry, fx32 frame);
extern void SetAnimationFrameIfChanged(StageEntry *entry, int frame);

static inline void PlayAttackVoice(StageEntry *entry)
{
    int pick = func_0202a9e4(2000) / 1000;

    PlayStageSound(gAttackVoices[0xff - entry->kind][pick].seqArc, gAttackVoices[0xff - entry->kind][pick].index, TRUE);
}

/*
 * Action handler for a special combo: shows its caption and opening effect, then runs at the main target with the
 * first attack. Each hit lands with hit effect 0x2e for the finisher; while A keeps being pressed in time another
 * attack follows (a random one, or the finisher for the last of the combo's hits, which also hits in mid-swing
 * and shows a slash), up to minRepeats..maxRepeats hits. Afterwards the attacker walks back and the action ends.
 */
void EntryActionSpecialCombo(u8 entryIndex)
{
    int frame;
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    StageEntryAction *action = GetEntryAction(entry);
    BOOL again = FALSE;
    fx32 reach;
    VecFx32 start;
    VecFx32 end;
    VecFx32 from;
    VecFx32 to;
    VecFx32 backStart;
    VecFx32 backEnd;

    frame = GetEntryAnimationFrame(entry);
    entry->flags |= STAGE_ENTRY_PRESS_PANEL | STAGE_ENTRY_PRESSED_ATTACK;
    switch (entry->stateStep) {
    case 0:
        data_ov041_020cff48.comboHit = 1;
        data_ov041_020cff48.comboStage = 0;
        data_ov041_020cff48.comboLength =
            func_0202a9e4((action->maxRepeats - action->minRepeats) * 1000) / 1000 + action->minRepeats - 1;
        entry->stateStep++;
    case 1: {
        VecFx32 position;

        GetPositionAboveGround(&position, entry);
        entry->effects[0] = SpawnStageItem(entry, 0xff, 0x14, 0, &position, FALSE);
        PlayStageSound(0x1a0, 6, TRUE);
        ShowFieldMessageLine_02072ad0(0x11, GetHudLabelId(0xed));
        entry->stateStep++;
    }
    case 2:
        if (entry->effects[0]->flags & 4) {
            break;
        }
        entry->stateStep++;
    case 3:
        ChooseEntryMainTarget(entry);
        if (entry->mainTarget == entry->index) {
            FinishEntryAction(entry);
            return;
        }
        SetSceneEntryAnimation(entry, action->comboAnimations[data_ov041_020cff48.comboStage], 1, 1);
        frame = GetEntryAnimationFrame(entry);
        GetEntryMoveEnds(entry, &start, &end, TRUE);
        AimEntryPathModel(entry, &start, &end, TRUE, NULL);
        PlayAttackVoice(entry);
        entry->stateStep++;
    case 4:
        MoveEntryAlongPath(entry, work->frameStep);
        if (frame < FRAME_TO_FX32(action->comboEndFrames[data_ov041_020cff48.comboStage])) {
            break;
        }
        entry->stateStep = COMBO_HIT;
        again = TRUE;
        break;
    case COMBO_ATTACK:
        SetSceneEntryAnimation(entry, action->comboAnimations[data_ov041_020cff48.comboStage], 1, 1);
        frame = GetEntryAnimationFrame(entry);
        switch (data_ov041_020cff48.comboStage) {
        case 1:
            switch (action->comboStyle) {
            case 0:
                reach = 0x12 << 10;
                break;
            case 1:
                reach = 3 * FX32_ONE;
                break;
            case 2:
                reach = 3 * FX32_ONE;
                break;
            }
            break;
        case 2:
            switch (action->comboStyle) {
            case 0:
                reach = 3 * FX32_ONE;
                break;
            case 1:
                reach = 6 << 10;
                break;
            case 2:
                reach = 6 << 10;
                break;
            }
            break;
        case COMBO_FINISHER:
            switch (action->comboStyle) {
            case 0:
                reach = 6 << 10;
                break;
            case 1:
                reach = 0x12 << 10;
                break;
            case 2:
                reach = 0x12 << 10;
                break;
            }
            break;
        }
        GetEntryMoveEnds(entry, &from, &to, FALSE);
        AimEntryPathModel(entry, &from, &to, FALSE, &reach);
        if (data_ov041_020cff48.comboStage == COMBO_FINISHER) {
            PlayStageSound(0x35, 0, TRUE);
        } else {
            PlayAttackVoice(entry);
        }
        entry->stateStep++;
    case COMBO_ATTACK + 1:
        MoveEntryAlongPath(entry, work->frameStep);
        if (data_ov041_020cff48.comboStage == COMBO_FINISHER && !IsStageEntryFrozen(entry) &&
            frame >= 8 * FX32_ONE && frame < 9 * FX32_ONE) {
            ComputeEntryHit(entry, &entry->hit);
            entry->hit.effect.category = 0xff;
            entry->hit.effect.index = 0x2e;
            entry->hit.effect.animation = 0;
            entry->hit.altEffect.category = 0xff;
            entry->hit.altEffect.index = 0x2e;
            entry->hit.altEffect.animation = 0;
            ForEachActionTarget(entry, work->hitSeqArc, 4);
            StartSceneFadeIn(10 * FX32_ONE);
        }
        if (data_ov041_020cff48.comboStage == COMBO_FINISHER && frame >= 6 * FX32_ONE && frame < 7 * FX32_ONE) {
            VecFx32 position;
            StageResourceItem *item;

            GetPositionAboveGround(&position, entry);
            item = SpawnStageItem(entry, 0xff, 0x2d, 0, &position, FALSE);
            if (item != NULL) {
                MI_Copy48B(&entry->slot.node.rotation, &item->model.rotation);
            }
            entry->effects[0] = item;
        }
        if (frame < FRAME_TO_FX32(action->comboEndFrames[data_ov041_020cff48.comboStage])) {
            break;
        }
        entry->stateStep = COMBO_HIT;
        again = TRUE;
        break;
    case COMBO_HIT:
        ComputeEntryHit(entry, &entry->hit);
        if (data_ov041_020cff48.comboStage == COMBO_FINISHER) {
            entry->hit.effect.category = 0xff;
            entry->hit.effect.index = 0x2e;
            entry->hit.effect.animation = 0;
            entry->hit.altEffect.category = 0xff;
            entry->hit.altEffect.index = 0x2e;
            entry->hit.altEffect.animation = 0;
        }
        if (data_ov041_020cff48.comboHit == data_ov041_020cff48.comboLength + 1 &&
            (entry->flags & STAGE_ENTRY_PRESS_PANEL)) {
            entry->flags |= STAGE_ENTRY_COMBO_FINISHED;
        }
        ForEachActionTarget(entry, work->hitSeqArc, 4);
        if ((entry->flags & STAGE_ENTRY_PRESSED_ATTACK) && !(entry->flags & STAGE_ENTRY_MISSED)) {
            StartSceneFadeIn(10 * FX32_ONE);
        }
        entry->stateStep++;
    case COMBO_HIT + 1:
        if (IsStageEntryFrozen(entry)) {
            break;
        }
        if (data_ov041_020cff48.comboHit <= data_ov041_020cff48.comboLength &&
            (entry->flags & STAGE_ENTRY_PRESSED_ATTACK) && CountActiveStageEntries(FALSE) != 0) {
            entry->flags &= ~STAGE_ENTRY_PRESSED_ATTACK;
            if (work->entries[entry->mainTarget].state != STAGE_ENTRY_OUT) {
                if (data_ov041_020cff48.comboHit == data_ov041_020cff48.comboLength) {
                    data_ov041_020cff48.comboStage = COMBO_FINISHER;
                } else if (data_ov041_020cff48.comboHit < data_ov041_020cff48.comboLength) {
                    data_ov041_020cff48.comboStage = func_0202a9e4(2) + 1;
                }
            } else {
                data_ov041_020cff48.comboStage = 0;
            }
            data_ov041_020cff48.comboHit++;
        } else {
            data_ov041_020cff48.comboHit = 0;
        }
        entry->stateStep++;
    case COMBO_HIT + 2:
        if (MatchesEitherSlotId(entry, action->comboAnimations[0])) {
            if ((data_ov041_020cff48.comboHit == 0 || data_ov041_020cff48.comboHit == data_ov041_020cff48.comboLength) &&
                frame < FRAME_TO_FX32(action->comboRecoverFrame)) {
                break;
            }
        } else if (IsEntryFlag2Set(entry)) {
            MoveEntryAlongPath(entry, work->frameStep);
            break;
        }
        if (data_ov041_020cff48.comboHit != 0) {
            ClearEntryActionState(entry);
            if (data_ov041_020cff48.comboStage == 0) {
                entry->stateStep = 3;
                entry->mainTarget = entry->index;
            } else {
                entry->stateStep = COMBO_ATTACK;
            }
            again = TRUE;
            break;
        }
        entry->stateStep++;
    case COMBO_HIT + 3:
        if (!MatchesEitherSlotId(entry, action->comboAnimations[0])) {
            SetSceneEntryAnimation(entry, action->comboAnimations[0], 0, 0);
            SetStageActorFrame(entry, FRAME_TO_FX32(action->comboRecoverFrame));
        } else {
            SetAnimationFrameIfChanged(entry, frame);
        }
        GetEntryMoveEnds(entry, &backStart, &backEnd, FALSE);
        AimEntryPathModel(entry, &backStart, &backEnd, FALSE, NULL);
        entry->stateStep++;
    case COMBO_HIT + 4:
        MoveEntryAlongPath(entry, work->frameStep);
        if (!IsEntryFlag2Set(entry)) {
            FinishEntryAction(entry);
        }
        break;
    }
    if (again) {
        EntryActionSpecialCombo(entryIndex);
    }
}
