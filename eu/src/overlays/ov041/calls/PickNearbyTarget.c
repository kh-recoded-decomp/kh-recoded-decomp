#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void func_ov041_020c2d4c(StageEntry *entry, int range);

/* Picks a random opposing entry at most two rows away. */
void PickNearbyTarget(StageEntry *entry)
{
    func_ov041_020c2d4c(entry, 2);
}
