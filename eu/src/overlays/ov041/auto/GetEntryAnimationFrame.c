#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* The frame an entry's animation is on. */
int GetEntryAnimationFrame(StageEntry *entry)
{
    return entry->animationFrame;
}
