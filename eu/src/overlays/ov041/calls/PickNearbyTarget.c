#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern int PickTargetInRange(StageEntry *entry, int range);

/* Picks a random opposing entry at most two rows away. */
void PickNearbyTarget(StageEntry *entry)
{
    PickTargetInRange(entry, 2);
}
