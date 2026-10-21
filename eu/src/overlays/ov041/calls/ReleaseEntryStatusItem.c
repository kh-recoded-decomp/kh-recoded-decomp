#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void ReleaseStageItem(StageResourceItem *item);

/* Frees an entry's status effect item. */
void ReleaseEntryStatusItem(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;

    if (work->entries[entryIndex].statusItem != NULL) {
        ReleaseStageItem(work->entries[entryIndex].statusItem);
        work->entries[entryIndex].statusItem = NULL;
    }
}
