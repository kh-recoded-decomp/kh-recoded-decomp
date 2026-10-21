#include "nitro/types.h"
#include "src/overlays/ov001/FieldProgressState.h"
#include "src/overlays/ov001/SceneEntryContext.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern FieldProgressState *data_ov001_020a0480;
extern s32 IsScreenModeIdle(void);
extern void UpdateStageEntry(u8 entryIndex);
extern void SumStageTotals(StageWork **work, int *totals);
extern void StoreMovieCounter(int index, int value);
extern void AddSessionCounter(int index, int amount);
extern void TallyStageCharacter(int character, BOOL counted);
extern void func_ov001_02067a6c(void);
extern void func_ov035_020bb66c(void);
extern void SetSessionFlag(u32 id);
extern void ClearSessionPackedBit(int id);
extern BOOL IsSessionFlagSet(int id);
extern void SetFieldStateValue(u32 a, u32 b);
extern void MarkFieldValueNegative(void);
extern void ForceHudState6IfActive(void);
extern void ReleaseSeqArcHeapLevel(int index);
extern void SetStageState(int state, BOOL runNow);

/*
 * Stage state 21: once the screen has faded, books the stage totals (three counters, experience and a session
 * counter), tallies the defeated enemies, and sets up how the field resumes (won, retreated or neither), then
 * moves on to state 22. Until then the entries keep being updated.
 */
void StageStateFinish(void)
{
    StageContext *context = gMovieContextState;
    StageWork *work = context->stageWork;
    int totals[5];
    int i;
    int value;
    StageEntry *entry;

    if (!IsScreenModeIdle()) {
        for (i = 0; i < work->entryCount; i++) {
            UpdateStageEntry(i);
        }
        return;
    }
    SumStageTotals(&context->stageWork, totals);
    for (i = 0; i < 3; i++) {
        value = totals[i];
        if (value <= 0) {
            value = 1;
        }
        StoreMovieCounter(i, value);
    }
    data_ov001_020a0480->pendingExperience += totals[3];
    AddSessionCounter(0, totals[4]);
    if (work->flags & 0x2000) {
        for (i = work->primaryCount; i < work->entryCount; i++) {
            entry = &work->entries[i];
            if (!(entry->flags & STAGE_ENTRY_NOT_TALLIED)) {
                TallyStageCharacter(entry->kind, entry->countsForProgress);
            }
        }
    }
    context->flags &= 0xfff3;
    func_ov001_02067a6c();
    data_ov001_020a048c->unk10b8 = 0;
    func_ov035_020bb66c();
    context->pendingChoice = 2;
    if (work->flags & 0x8000) {
        context->cooldown = 60;
        context->effectTimer = 90;
        SetSessionFlag(0x3533);
        context->endKind = 1;
        ClearSessionPackedBit(0x379c);
    } else if (work->flags & 0x4000) {
        gMovieContextState->flags |= 0x10;
        SetFieldStateValue(-3, 3);
        MarkFieldValueNegative();
        context->pendingChoice = -1;
        context->endKind = 3;
        ClearSessionPackedBit(0x379c);
    } else {
        context->cooldown = 60;
        context->endKind = 2;
        if (IsSessionFlagSet(0x379c)) {
            context->pendingChoice = -1;
        }
    }
    context->sceneReady = 0;
    context->unk28 = context->unk26;
    ForceHudState6IfActive();
    ReleaseSeqArcHeapLevel(2);
    SetStageState(0x16, FALSE);
}
