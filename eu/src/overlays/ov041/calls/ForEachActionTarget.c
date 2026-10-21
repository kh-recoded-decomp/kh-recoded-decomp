#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void ApplyActionHitWithSound(StageEntry *entry, u8 targetIndex, BOOL pressCheck, int seqArcNo, int soundIndex);

/* Applies an entry's hit to each of its targets, with the given hit sound. */
void ForEachActionTarget(StageEntry *entry, int seqArcNo, int soundIndex)
{
    int i;

    for (i = 0; i < entry->targetCount; i++) {
        ApplyActionHitWithSound(entry, entry->targets[i], TRUE, seqArcNo, soundIndex);
    }
}
