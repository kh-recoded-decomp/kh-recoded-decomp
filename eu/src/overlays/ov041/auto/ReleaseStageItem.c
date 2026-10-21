#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

/* Frees an item, if there is one. */
void ReleaseStageItem(StageResourceItem *item)
{
    if (item != NULL) {
        item->flags = 0;
        item->variant = 0;
    }
}
