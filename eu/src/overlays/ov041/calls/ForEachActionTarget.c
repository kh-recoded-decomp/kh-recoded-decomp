#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void func_ov041_020c48e0(StageEntry *entry, u8 targetIndex, BOOL arg, int a, int b);

/* Runs func_ov041_020c48e0 on each of an entry's targets. */
void ForEachActionTarget(StageEntry *entry, int a, int b)
{
    int i;

    for (i = 0; i < entry->targetCount; i++) {
        func_ov041_020c48e0(entry, entry->targets[i], TRUE, a, b);
    }
}
