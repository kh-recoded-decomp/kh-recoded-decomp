#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern void UpdateEntryStatusItem(u8 entryIndex);

/* Gives every entry under a status its status effect item. */
void UpdateEntryStatusItems(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;

    for (i = 0; i < work->entryCount; i++) {
        UpdateEntryStatusItem(i);
    }
}
