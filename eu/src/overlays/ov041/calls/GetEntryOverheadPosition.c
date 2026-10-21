#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

/* The point above an entry where markers and effects are shown. */
void GetEntryOverheadPosition(VecFx32 *out, StageEntry *entry)
{
    VecFx32 position = entry->slot.node.position;

    VEC_Add(&position, &entry->overheadOffset, &position);
    *out = position;
}
