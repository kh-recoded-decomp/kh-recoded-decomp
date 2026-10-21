#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void SetEntryState(StageEntry *entry, int state);

/* Moves the entry at an index to another state. */
void SetStageEntryState(u8 entryIndex, int state)
{
    SetEntryState(&gMovieContextState->stageWork->entries[entryIndex], state);
}
