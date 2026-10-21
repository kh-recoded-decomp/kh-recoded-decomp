#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern u8 GetFarthestEnemyRow(void);

/*
 * How many rows an entry's action has to reach: for an enemy, how far it stands in front of the farthest enemy
 * row (0-2); for a player entry 0 (the checks on stages with flags 0x20 and 0x400000 all end in 0 as well).
 */
int GetEntryNeededRange(StageEntry *entry)
{
    StageWork *stage;
    StageWork *work;
    int range;
    int i;
    int farthest;
    BOOL found;

    work = gMovieContextState->stageWork;
    farthest = GetFarthestEnemyRow();
    if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
        range = 0;
        if (!(entry->flags & STAGE_ENTRY_ENEMY) && (work->flags & 0x20)) {
            stage = work;
            found = FALSE;
            if (stage->flags & 0x400000) {
                for (i = stage->primaryCount; i < stage->entryCount; i++) {
                    if (stage->entries[i].kind == 0 && stage->entries[i].state != STAGE_ENTRY_OUT) {
                        found = TRUE;
                    }
                }
                if (!found) {
                    return 0;
                }
            } else {
                return found;
            }
        }
    } else {
        switch (farthest - entry->row) {
        case 0:
            range = 0;
            break;
        case 1:
            range = 1;
            break;
        case 2:
            range = 2;
            break;
        }
    }
    return range;
}
