#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* The action an entry is carrying out, or NULL. */
StageEntryAction *GetEntryAction(StageEntry *entry)
{
    if (entry->actionIndex >= 0) {
        return &entry->actions[entry->actionIndex];
    }
    return NULL;
}
