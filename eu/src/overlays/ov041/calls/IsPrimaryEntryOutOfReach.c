#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern u8 GetFarthestEnemyRow(void);

/* TRUE when a primary entry still in the fight is more than three rows off the farthest enemy row. */
BOOL IsPrimaryEntryOutOfReach(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;
    StageEntry *entry;
    u8 row;

    for (i = 0; i < work->primaryCount; i++) {
        entry = &work->entries[i];
        row = entry->row;
        if ((u8)(row - GetFarthestEnemyRow()) > 3 && entry->state != STAGE_ENTRY_OUT) {
            return TRUE;
        }
    }
    return FALSE;
}
