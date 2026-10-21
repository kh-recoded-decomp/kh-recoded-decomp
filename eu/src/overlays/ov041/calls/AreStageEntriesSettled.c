#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern u8 CountActiveStageEntries(BOOL primary);
extern void SetStageEntryState(u8 entryIndex, int arg);

/*
 * TRUE when no entry is active or waiting part-way through; also TRUE once no primary entry is left, in which
 * case every active entry is set back to waiting.
 */
BOOL AreStageEntriesSettled(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL settled = TRUE;
    int i;
    StageEntry *entry;

    for (i = 0; i < work->entryCount; i++) {
        entry = &work->entries[i];
        if (entry->state == STAGE_ENTRY_ACTIVE || (entry->state == STAGE_ENTRY_WAITING && entry->stateStep)) {
            settled = FALSE;
            break;
        }
    }
    if (CountActiveStageEntries(TRUE) == 0) {
        settled = TRUE;
        for (i = 0; i < work->entryCount; i++) {
            if (work->entries[i].state == STAGE_ENTRY_ACTIVE) {
                SetStageEntryState(i, 1);
            }
        }
    }
    return settled;
}
