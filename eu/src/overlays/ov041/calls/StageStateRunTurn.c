#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void RequestFieldRefresh(void);
extern BOOL HasEntryWithClearState(BOOL wantClear);
extern BOOL AreStageEntriesSettled(void);
extern BOOL NoSecondaryEntryCanAct(void);
extern BOOL StageEntryHasActionInRange(u8 entryIndex);
extern BOOL RollStageChance(void);
extern void SetStageEntryFlag800(u8 entryIndex);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 11: once the current entry has finished acting, ends the fight when one side is gone (state 17 or
 * 18), moves on to state 10 when everyone has settled, or hands the turn to the next active entry (state 19 when
 * no secondary entry can act, or by chance). Every entry is updated each frame, the current one first.
 */
void StageStateRunTurn(void)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *current;

    switch (work->stateStep) {
    case 0:
        RequestFieldRefresh();
        work->stateStep++;
    case 1:
        current = &work->entries[work->currentEntry];
        if (current->state == 4 || current->state == 3) {
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
        if (AreStageEntriesSettled()) {
            SetStageState(10, TRUE);
            return;
        }
        for (; i < work->entryCount; i++) {
            if (work->entries[i].state == STAGE_ENTRY_ACTIVE) {
                work->currentEntry = i;
                if (NoSecondaryEntryCanAct()) {
                    SetStageState(0x13, TRUE);
                    return;
                }
                if (StageEntryHasActionInRange(work->currentEntry) && RollStageChance()) {
                    SetStageState(0x13, TRUE);
                    return;
                }
                SetStageEntryFlag800(work->currentEntry);
                break;
            }
        }
        break;
    }
    UpdateStageEntry(work->currentEntry);
    for (i = 0; i < work->entryCount; i++) {
        if (i != work->currentEntry) {
            UpdateStageEntry(i);
        }
    }
}
