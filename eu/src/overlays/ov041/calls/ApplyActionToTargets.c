#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void func_ov041_020c46e8(StageEntry *entry, u8 targetIndex, BOOL arg);

/* Applies an entry's action to each of its targets. */
void ApplyActionToTargets(StageEntry *entry)
{
    int i;

    for (i = 0; i < entry->targetCount; i++) {
        func_ov041_020c46e8(entry, entry->targets[i], TRUE);
    }
}
