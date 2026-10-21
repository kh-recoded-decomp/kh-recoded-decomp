#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern BOOL CheckStageEntryActions(u8 entryIndex);

/* TRUE when no secondary entry is still active (CheckStageEntryActions). */
BOOL AreSecondaryEntriesIdle(void)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;
    BOOL done = TRUE;

    for (i = work->primaryCount; i < work->entryCount; i++) {
        if (CheckStageEntryActions(i)) {
            done = FALSE;
            break;
        }
    }
    return done;
}
