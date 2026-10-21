#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define STAGE_ENTRY_CHEERING 7

extern void InvokeFieldModeOp428(void);
extern void SetStageEntryState(u8 entryIndex, int state);
extern void SumStageTotals(StageWork **work, int *totals);
extern void ShowStageHudMessage(u8 kind, ...);
extern BOOL IsStageHudMessageShowing(void);
extern void func_ov001_02078680(void);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 17 (won): the primary entries still in the fight cheer (entry state 7), the experience gained is
 * shown, then they step back; once every order has played out the HUD is advanced 15 steps (30 with status 7
 * on the first entry) and state 20 follows. Every entry is updated each frame.
 */
void StageStateWon(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL busy = FALSE;
    int totals[5];
    BOOL allBack = TRUE;
    int i;
    int j;

    switch (work->stateStep) {
    case 0:
        work->flags |= 0x2000;
        InvokeFieldModeOp428();
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state != STAGE_ENTRY_OUT) {
                SetStageEntryState(i, STAGE_ENTRY_CHEERING);
            }
        }
        work->stateStep++;
    case 1:
        SumStageTotals(&work, totals);
        if (totals[3] > 0) {
            ShowStageHudMessage(5, totals[3]);
        }
        work->stateStep++;
    case 2:
        if (IsStageHudMessageShowing()) {
            break;
        }
        work->stateStep++;
    case 3:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state == STAGE_ENTRY_CHEERING) {
                work->entries[i].flags |= STAGE_ENTRY_STEP_BACK;
            }
        }
        work->stateStep++;
    case 4:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state == STAGE_ENTRY_CHEERING && (work->entries[i].flags & STAGE_ENTRY_STEP_BACK)) {
                allBack = FALSE;
                break;
            }
        }
        if (!allBack) {
            break;
        }
        work->stateStep++;
    case 5:
        for (i = 0; i < work->entryCount; i++) {
            for (j = 0; j < 3; j++) {
                if (work->entries[i].orders[j].pending) {
                    busy = TRUE;
                    break;
                }
            }
        }
        if (busy) {
            break;
        }
        for (i = 0; i < 15; i++) {
            func_ov001_02078680();
        }
        if (work->entries[0].statuses[7] != 0) {
            for (i = 0; i < 15; i++) {
                func_ov001_02078680();
            }
        }
        SetStageState(0x14, FALSE);
        break;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
