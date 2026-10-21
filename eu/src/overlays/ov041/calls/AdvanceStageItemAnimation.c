#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern u16 AdvanceAnimationTracks(void *animation, int delta);

/* Advances the animation tracks of an item's model; nonzero once they have ended. */
BOOL AdvanceStageItemAnimation(StageResourceItem *item, int delta)
{
    return AdvanceAnimationTracks(&item->model, delta);
}
