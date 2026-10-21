#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL HasActionInRange(StageEntry *entry);

/* Whether the entry at an index has an action in range (HasActionInRange). */
BOOL StageEntryHasActionInRange(u8 entryIndex)
{
    return HasActionInRange(&gMovieContextState->stageWork->entries[entryIndex]);
}
