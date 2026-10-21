#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern u8 CountActiveStageEntries(BOOL primary);
extern void func_ov041_020c0e38(u8 entryIndex, int arg);

/*
 * TRUE when no entry is active or waiting on something; also TRUE once no primary entry is left, in which
 * case every still active entry is stopped (func_ov041_020c0e38).
 */
BOOL AreStageEntriesSettled(void)
{
    StageWork *work = gMovieContextState->stageWork;
    BOOL settled = TRUE;
    int i;
    StageEntry *entry;

    for (i = 0; i < work->entryCount; i++) {
        entry = &work->entries[i];
        if (entry->state == STAGE_ENTRY_ACTIVE || (entry->state == STAGE_ENTRY_WAITING && entry->pending)) {
            settled = FALSE;
            break;
        }
    }
    if (CountActiveStageEntries(TRUE) == 0) {
        settled = TRUE;
        for (i = 0; i < work->entryCount; i++) {
            if (work->entries[i].state == STAGE_ENTRY_ACTIVE) {
                func_ov041_020c0e38(i, 1);
            }
        }
    }
    return settled;
}
