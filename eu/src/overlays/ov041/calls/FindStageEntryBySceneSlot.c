#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* The entry on a scene slot, or NULL. */
StageEntry *FindStageEntryBySceneSlot(int sceneSlot)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;
    StageEntry *entry;

    for (i = 0; i < work->entryCount; i++) {
        entry = &work->entries[i];
        if (entry->sceneSlot == sceneSlot) {
            return entry;
        }
    }
    return NULL;
}
