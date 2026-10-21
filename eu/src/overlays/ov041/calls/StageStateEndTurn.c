#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void SetStageEntryState(u8 entryIndex, int state);
extern void ShowStageHudMessage(u8 kind, ...);
extern void UpdateEntryStatusItems(void);
extern void HideStageHudMessage(void);
extern void FaceStageEntryAcross(u8 entryIndex);
extern void TickEntryStatuses(u8 entryIndex);
extern void ForceHudState6IfActive(void);
extern void func_ov001_02078680(void);
extern void InvokeFieldModeOp428(void);
extern void ResetSlotHandles(void);
extern void HideHudCaption(void);
extern void SelectFieldMenuPage(int page);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state at the end of a turn: on turn 6 the kind 0x15 entries drop out; waits for the entries going out,
 * puts the out primary entries with status 3 into state 0xd (message 0xce) and those with status 4 into state 0xe
 * (message 0xcf), waiting for each; then ticks the statuses (faces everyone across on the first turn), counts
 * the turn and goes on to state 6, or to state 8 once the first entry is out. Entries are updated while it waits.
 */
void StageStateEndTurn(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL waiting = FALSE;
    int i;

    switch (work->stateStep) {
    case 0:
        for (i = 0; i < work->entryCount; i++) {
            StageEntry *entry = &work->entries[i];

            if (entry->kind == 0x15 && entry->state != STAGE_ENTRY_OUT && work->turn == 6) {
                entry->flags |= STAGE_ENTRY_NOT_TALLIED;
                work->entries[i].shownHp = 0;
                work->entries[i].hp = 0;
                SetStageEntryState(i, STAGE_ENTRY_OUT);
            }
        }
        work->stateStep++;
    case 1:
        for (i = 0; i < work->entryCount; i++) {
            if (work->entries[i].state == STAGE_ENTRY_OUT && work->entries[i].stateStep != 3) {
                waiting = TRUE;
            }
        }
        if (waiting) {
            break;
        }
        work->stateStep++;
    case 2:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state == STAGE_ENTRY_OUT && work->entries[i].statuses[STAGE_ENTRY_STATUS_3] > 0) {
                SetStageEntryState(i, 0xd);
            }
        }
        work->stateStep++;
    case 3:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state == 0xd) {
                waiting = TRUE;
                ShowStageHudMessage(0xb, 0xce, 0);
            }
        }
        if (waiting) {
            break;
        }
        UpdateEntryStatusItems();
        work->stateStep++;
    case 4:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].statuses[4] > 0) {
                SetStageEntryState(i, 0xe);
            }
        }
        work->stateStep++;
    case 5:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state == 0xe) {
                waiting = TRUE;
                ShowStageHudMessage(0xb, 0xcf, 0);
            }
        }
        if (waiting) {
            break;
        }
        work->stateStep++;
    case 6:
        HideStageHudMessage();
        for (i = 0; i < work->entryCount; i++) {
            if (work->turn == 0) {
                FaceStageEntryAcross(i);
                work->flags &= ~2;
            } else {
                TickEntryStatuses(i);
            }
        }
        work->turn++;
        if (work->entries[0].state != STAGE_ENTRY_OUT) {
            ForceHudState6IfActive();
            for (i = 0; i < 15; i++) {
                func_ov001_02078680();
            }
            if (work->entries[0].statuses[7] != 0) {
                for (i = 0; i < 15; i++) {
                    func_ov001_02078680();
                }
            }
        }
        if (work->entries[0].state != STAGE_ENTRY_OUT) {
            work->flags |= 1;
            work->flags &= ~STAGE_WORK_NO_TIMED_INPUT;
            work->flags &= ~STAGE_WORK_SKIP_CHANCE_B;
            InvokeFieldModeOp428();
            ResetSlotHandles();
            HideHudCaption();
            SelectFieldMenuPage(0);
            SetStageState(6, TRUE);
            work->flags &= ~1;
        } else {
            SetStageState(8, TRUE);
        }
        return;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
