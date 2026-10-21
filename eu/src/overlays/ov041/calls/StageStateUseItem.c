#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define STAGE_ENTRY_ACTING 4
#define STAGE_ENTRY_ADVANCING 10
#define ITEM_ACTION 2 /* the slot of StageEntry.actions an item's action is copied to */

extern int data_ov041_020cff40;
extern void RequestFieldRefresh(void);
extern void ShowStageHudMessage(u8 kind, ...);
extern BOOL IsStageHudMessageShowing(void);
extern void SetStageEntryState(u8 entryIndex, int state);
extern void ShowHudCaption(int commandId);
extern void UpdateSelectionCount(int slot);
extern int GetConsumableSlotUses(int slot);
extern void SetFieldEntryEnabled(int slot, u16 uses);
extern void TickFieldMenuEntry(int arg, int slot);
extern BOOL HasEntryWithClearState(BOOL wantClear);
extern BOOL IsPrimaryEntryOutOfReach(void);
extern void UpdateEntryStatusItems(void);
extern void ForceHudState6IfActive(void);
extern void HideStageHudMessage(void);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 15: uses the chosen item. Shows its name (after a short pause for most items), hands its action to
 * the entries that use it (every primary entry for items 0xe4-0xe6), waits for everyone to settle, books the
 * item in the field menu, then ends the fight if one side is gone or goes back to the menu (state 6). The
 * current entry is updated first each frame.
 */
void StageStateUseItem(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL waiting = FALSE;
    int i;
    u16 uses;

    switch (work->stateStep) {
    case 0:
        RequestFieldRefresh();
        switch (work->itemActions[0].effect) {
        case 0xb7:
        case 0xb8:
            data_ov041_020cff40 = 0;
            break;
        default:
            ShowStageHudMessage(10);
            data_ov041_020cff40 = 15;
            break;
        }
        work->stateStep++;
    case 1:
        if (data_ov041_020cff40 > 0) {
            data_ov041_020cff40--;
            break;
        }
        ShowStageHudMessage(11, work->itemActions[0].effect, work->itemActions[0].effectArg);
        work->stateStep++;
    case 2:
        switch (work->itemActions[0].effect) {
        case 0xe4:
        case 0xe5:
        case 0xe6:
            for (i = 0; i < work->primaryCount; i++) {
                SetStageEntryState(i, STAGE_ENTRY_ACTING);
                work->entries[i].actions[ITEM_ACTION] = work->itemActions[i];
                work->entries[i].actionIndex = ITEM_ACTION;
            }
            break;
        case 0xec:
            if (IsStageHudMessageShowing()) {
                waiting = TRUE;
                break;
            }
            SetStageEntryState(0, 12);
            ShowHudCaption(work->commandId);
            break;
        default:
            SetStageEntryState(0, STAGE_ENTRY_ACTING);
            work->entries[0].actions[ITEM_ACTION] = work->itemActions[0];
            work->entries[0].actionIndex = ITEM_ACTION;
            break;
        }
        if (waiting) {
            break;
        }
        work->currentEntry = 0;
        work->stateStep++;
        break;
    case 3:
        ShowStageHudMessage(11, work->itemActions[0].effect, work->itemActions[0].effectArg);
        for (i = waiting; i < work->entryCount; i++) {
            if (work->entries[i].state != STAGE_ENTRY_WAITING && work->entries[i].state != STAGE_ENTRY_OUT) {
                waiting = TRUE;
            }
        }
        if (waiting) {
            break;
        }
        work->stateStep++;
    case 4:
        switch (work->itemActions[0].effect) {
        case 0xb7:
        case 0xb8:
            UpdateSelectionCount(work->itemActions[0].itemSlot);
            uses = GetConsumableSlotUses(work->itemActions[0].itemSlot);
            SetFieldEntryEnabled(work->itemActions[0].itemSlot, uses);
            break;
        default:
            TickFieldMenuEntry(0, work->itemActions[0].itemSlot);
            break;
        }
        i = 0;
        if (!HasEntryWithClearState(FALSE)) {
            SetStageState(0x11, TRUE);
            return;
        }
        if (!HasEntryWithClearState(TRUE)) {
            SetStageState(0x12, TRUE);
            return;
        }
        if (IsPrimaryEntryOutOfReach() && !(work->flags & 0x20)) {
            for (; i < work->primaryCount; i++) {
                if (work->entries[i].state != STAGE_ENTRY_OUT) {
                    SetStageEntryState(work->entries[i].index, STAGE_ENTRY_ADVANCING);
                }
            }
        }
        UpdateEntryStatusItems();
        ForceHudState6IfActive();
        HideStageHudMessage();
        SetStageState(6, FALSE);
        break;
    }
    UpdateStageEntry(work->currentEntry);
    for (i = 0; i < work->entryCount; i++) {
        if (i != work->currentEntry) {
            UpdateStageEntry(i);
        }
    }
}
