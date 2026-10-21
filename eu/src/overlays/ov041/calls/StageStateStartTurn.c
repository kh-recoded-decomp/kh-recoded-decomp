#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void SetStageEntryState(u8 entryIndex, int state);
extern int TickSlotTimer(int slot);
extern void TickFieldMenuEntry(int arg, int slot);
extern void UpdateEntryStatusItems(void);
extern void InvokeFieldModeOp340(void);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 13: puts the first entry in state 12 and waits for it to be waiting again, then starts the turn
 * (state 19 after command 0xd3, state 6 otherwise). Every entry is updated each frame.
 */
void StageStateStartTurn(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;

    switch (work->stateStep) {
    case 0:
        work->stateStep++;
    case 1:
        work->stateStep++;
    case 2:
        SetStageEntryState(0, 12);
        work->stateStep++;
        break;
    case 3:
        if (work->entries[0].state != STAGE_ENTRY_WAITING) {
            break;
        }
        work->stateStep++;
    case 4:
        work->flags |= STAGE_WORK_TURN_STARTED;
        TickSlotTimer(work->fieldSlot);
        TickFieldMenuEntry(1, work->fieldSlot);
        UpdateEntryStatusItems();
        if (work->commandId == 0xd3) {
            SetStageState(0x13, FALSE);
            return;
        }
        InvokeFieldModeOp340();
        SetStageState(6, FALSE);
        break;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
