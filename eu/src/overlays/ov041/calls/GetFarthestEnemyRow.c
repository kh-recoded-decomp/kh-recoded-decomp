#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* The farthest row any enemy still in the fight stands on. */
u8 GetFarthestEnemyRow(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;
    u8 row = 0;
    StageEntry *entry;

    for (i = 0; i < work->entryCount; i++) {
        entry = &work->entries[i];
        if ((entry->flags & STAGE_ENTRY_ENEMY) && row < entry->row && entry->state != STAGE_ENTRY_OUT) {
            row = entry->row;
        }
    }
    return row;
}
