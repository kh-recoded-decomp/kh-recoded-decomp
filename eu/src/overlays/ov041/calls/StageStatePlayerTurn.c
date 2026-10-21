#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL HasEntryWithClearState(BOOL wantClear);
extern BOOL IsPrimaryEntryOutOfReach(void);
extern void SetStageEntryState(u8 entryIndex, int state);
extern BOOL AreStageEntriesSettled(void);
extern void SetStageEntryFlag800(u8 entryIndex);
extern void HideHudCaption(void);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 9: once the current entry is not acting and no primary entry is advancing (state 10), ends the
 * fight when one side is gone, sends every primary entry still in it forward when they are out of reach, moves
 * on to state 10 when everyone has settled, or hands the turn to the next active entry (taking the HUD caption
 * down the first time it is not the first entry). Every entry is updated each frame, the current one first.
 */
void StageStatePlayerTurn(void)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;
    BOOL busy = TRUE;
    StageEntry *current = &work->entries[work->currentEntry];

    if (current->state != 4 && current->state != 3) {
        busy = FALSE;
    }
    for (i = 0; i < work->primaryCount; i++) {
        if (work->entries[i].state == 10) {
            busy = TRUE;
            break;
        }
    }
    if (!busy) {
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
                    SetStageEntryState(work->entries[i].index, 10);
                }
            }
        } else if (AreStageEntriesSettled()) {
            work->flags &= ~STAGE_WORK_CAPTION_DOWN;
            SetStageState(10, TRUE);
            return;
        } else {
            for (i = 0; i < work->entryCount; i++) {
                if (work->entries[i].state == STAGE_ENTRY_ACTIVE) {
                    work->currentEntry = i;
                    SetStageEntryFlag800(work->currentEntry);
                    break;
                }
            }
            if (!(work->flags & STAGE_WORK_CAPTION_DOWN) && work->currentEntry != 0) {
                HideHudCaption();
                work->flags |= STAGE_WORK_CAPTION_DOWN;
            }
        }
    }
    UpdateStageEntry(work->currentEntry);
    for (i = 0; i < work->entryCount; i++) {
        if (i != work->currentEntry) {
            UpdateStageEntry(i);
        }
    }
}
