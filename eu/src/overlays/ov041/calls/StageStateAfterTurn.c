#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void SetStageState(int state, BOOL runNow);
extern void SetStageEntryState(u8 entryIndex, int state);

/*
 * Stage state 8: decides what follows the turn. Work flag 2 goes to state 9; flag 1 (while the first entry is in
 * the fight) back to state 6; flag 4 wakes the waiting enemies and goes to state 11; otherwise every waiting
 * entry is woken (the first one put back to waiting under flag 0x8000000) and state 9 follows.
 */
void StageStateAfterTurn(void)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry;

    if (work->flags & 2) {
        SetStageState(9, TRUE);
        return;
    }
    if ((work->flags & 1) && work->entries[0].state != STAGE_ENTRY_OUT) {
        work->unk04 = 1;
        SetStageState(6, FALSE);
        work->flags &= ~1;
        return;
    }
    if (work->flags & STAGE_WORK_NO_TIMED_INPUT) {
        for (i = 0; i < work->entryCount; i++) {
            entry = &work->entries[i];
            if ((entry->flags & STAGE_ENTRY_ENEMY) && entry->state == STAGE_ENTRY_WAITING) {
                SetStageEntryState(entry->index, STAGE_ENTRY_ACTIVE);
            }
        }
        work->currentEntry = 0;
        SetStageState(11, TRUE);
        return;
    }
    for (i = 0; i < work->entryCount; i++) {
        entry = &work->entries[i];
        if (entry->state == STAGE_ENTRY_WAITING) {
            SetStageEntryState(entry->index, STAGE_ENTRY_ACTIVE);
        }
        if (work->flags & 0x8000000) {
            SetStageEntryState(work->entries[0].index, STAGE_ENTRY_WAITING);
        }
    }
    work->currentEntry = 0;
    SetStageState(9, TRUE);
}
