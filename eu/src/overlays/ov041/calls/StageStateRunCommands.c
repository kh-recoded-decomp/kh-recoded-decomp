#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern int data_ov041_020cff40[2];
extern void SetMenuEntryHighlight(int listKind, int entryId, BOOL highlighted);
extern int InvokeFieldModeOp150(void);
extern void ResetSlotHandles(void);
extern void InvokeFieldModeOp268(void);
extern void RequestFieldRefresh(void);
extern void SetStageState(int state, BOOL runNow);
extern void TickFieldMenuEntry(int listKind, int entryId);
extern int InvokeFieldModeOp1d8(void);
extern StageFieldCommand *InvokeFieldModeOp1a4(StageFieldCommand *command);
extern void StartQueuedItemCommand(StageFieldCommand *command);
extern BOOL HasEntryWithClearState(BOOL enemies);
extern BOOL IsPrimaryEntryOutOfReach(void);
extern void SetStageEntryState(u8 entryIndex, int state);
extern void UpdateEntryStatusItems(void);
extern void InvokeFieldModeOp340(void);
extern void InvokeFieldModeOp428(void);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state that carries out the commands chosen in the menu: closes the menu (letting the highlighted
 * entries tick), then takes the queued commands one at a time (StartQueuedItemCommand), waiting for every entry to
 * be idle or out between them; ends the fight when a side is gone (states 17 and 18) and goes back to the menu
 * (state 8) when the queue is empty or a stop was asked for. Entries are updated every frame.
 */
void StageStateRunCommands(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL busy = FALSE;
    int i;
    StageFieldCommand command;

    switch (work->stateStep) {
    case 0:
        if (work->entries[0].statuses[0] == 2) {
            for (i = 0; i < work->menuDepth; i++) {
                SetMenuEntryHighlight(0, work->menuStack[i], TRUE);
                InvokeFieldModeOp150();
            }
            ResetSlotHandles();
        }
        InvokeFieldModeOp268();
        work->flags &= ~STAGE_WORK_RUNNING_COMMANDS;
        RequestFieldRefresh();
        work->stateStep++;
    case 1:
        if (work->menuDepth == 0) {
            SetStageState(8, FALSE);
            return;
        }
        for (i = 0; i < 3; i++) {
            if (work->menuStack[i] != -1) {
                TickFieldMenuEntry(0, work->menuStack[i]);
                SetMenuEntryHighlight(0, work->menuStack[i], TRUE);
            }
        }
        data_ov041_020cff40[0] = 30;
        work->stateStep++;
    case 2:
        if (work->flags & STAGE_WORK_RUNNING_COMMANDS) {
            work->menuDepth = InvokeFieldModeOp1d8();
            work->menuStack[work->menuDepth] = -1;
        }
        work->stateStep++;
    case 3:
        if (data_ov041_020cff40[0] > 0) {
            data_ov041_020cff40[0]--;
            break;
        }
        work->stateStep++;
    case 4:
        if (work->menuDepth == 0) {
            SetStageState(8, FALSE);
            return;
        }
        work->flags |= STAGE_WORK_RUNNING_COMMANDS;
        work->stateStep++;
    case 5:
        if (InvokeFieldModeOp1a4(&command) == NULL) {
            break;
        }
        StartQueuedItemCommand(&command);
        work->stateStep++;
    case 6:
        for (i = 0; i < work->entryCount; i++) {
            if (work->entries[i].state != STAGE_ENTRY_WAITING && work->entries[i].state != STAGE_ENTRY_OUT) {
                busy = TRUE;
            }
        }
        if (busy) {
            break;
        }
        if (!HasEntryWithClearState(FALSE)) {
            SetStageState(0x11, TRUE);
            return;
        }
        if (!HasEntryWithClearState(TRUE)) {
            SetStageState(0x12, TRUE);
            return;
        }
        if (IsPrimaryEntryOutOfReach() && !(work->flags & 0x20)) {
            for (i = 0; i < work->primaryCount; i++) {
                if (work->entries[i].state != STAGE_ENTRY_OUT) {
                    SetStageEntryState(work->entries[i].index, 10);
                }
            }
        } else {
            UpdateEntryStatusItems();
        }
        work->stateStep++;
        break;
    case 7:
        for (i = 0; i < work->entryCount; i++) {
            if (work->entries[i].state != STAGE_ENTRY_WAITING && work->entries[i].state != STAGE_ENTRY_OUT) {
                busy = TRUE;
            }
        }
        if (busy) {
            break;
        }
        if (InvokeFieldModeOp1a4(&command)->id == 0xec) {
            InvokeFieldModeOp340();
        }
        if (work->flags & STAGE_WORK_STOP_COMMANDS) {
            work->flags &= ~STAGE_WORK_STOP_COMMANDS;
            InvokeFieldModeOp428();
            ResetSlotHandles();
            InvokeFieldModeOp268();
            work->flags &= ~STAGE_WORK_RUNNING_COMMANDS;
            RequestFieldRefresh();
            SetStageState(8, FALSE);
            return;
        }
        work->stateStep = 2;
        data_ov041_020cff40[0] = 10;
        break;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
