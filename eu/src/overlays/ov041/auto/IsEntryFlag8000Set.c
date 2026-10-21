#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* Flag 0x8000 of an entry. */
u32 IsEntryFlag8000Set(StageEntry *entry)
{
    return entry->flags & 0x8000;
}
