#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* Where an entry stands. */
void GetEntryPosition(VecFx32 *position, StageEntry *entry)
{
    *position = entry->slot.node.position;
}
