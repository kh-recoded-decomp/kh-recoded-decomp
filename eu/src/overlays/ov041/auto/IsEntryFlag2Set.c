#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* Flag 2 of an entry. */
u32 IsEntryFlag2Set(StageEntry *entry)
{
    return entry->flags & 2;
}
