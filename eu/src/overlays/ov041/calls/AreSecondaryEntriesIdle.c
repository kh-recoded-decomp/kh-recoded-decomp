#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern BOOL func_ov041_020c0e58(u8 entryIndex);

/* TRUE when no secondary entry is still active (func_ov041_020c0e58). */
BOOL AreSecondaryEntriesIdle(void)
{
    int i;
    StageWork *work = gMovieContextState->stageWork;
    BOOL done = TRUE;

    for (i = work->primaryCount; i < work->entryCount; i++) {
        if (func_ov041_020c0e58(i)) {
            done = FALSE;
            break;
        }
    }
    return done;
}
