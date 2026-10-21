#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern BOOL StageEntryHasActionInRange(u8 entryIndex);

/* TRUE when no secondary entry has an action in range. */
BOOL NoSecondaryEntryCanAct(void)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;
    BOOL done = TRUE;

    for (i = work->primaryCount; i < work->entryCount; i++) {
        if (StageEntryHasActionInRange(i)) {
            done = FALSE;
            break;
        }
    }
    return done;
}
