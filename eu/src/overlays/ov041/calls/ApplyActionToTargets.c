#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void ApplyActionHit(StageEntry *entry, u8 targetIndex, BOOL pressCheck);

/* Applies an entry's action to each of its targets. */
void ApplyActionToTargets(StageEntry *entry)
{
    int i;

    for (i = 0; i < entry->targetCount; i++) {
        ApplyActionHit(entry, entry->targets[i], TRUE);
    }
}
