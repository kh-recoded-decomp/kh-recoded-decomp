#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* Sets flag 0x800 on the entry at an index. */
void SetStageEntryFlag800(u8 entryIndex)
{
    StageEntry *entry = &gMovieContextState->stageWork->entries[entryIndex];

    entry->flags |= STAGE_ENTRY_FLAG_800;
}
