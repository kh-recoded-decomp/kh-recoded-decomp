#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* Whether an entry is frozen (FreezeStageEntry). */
u32 IsStageEntryFrozen(StageEntry *entry)
{
    return entry->flags & STAGE_ENTRY_FROZEN;
}
