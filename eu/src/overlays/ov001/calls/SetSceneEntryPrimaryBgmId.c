#include "src/overlays/ov001/SceneEntryContext.h"

u8 SetSceneEntryPrimaryBgmId(int index, u8 value)
{
    SceneEntry *entry = gSceneEntryContext->table->entries[index];
    u8 previous = entry->primaryBgmId;

    entry->primaryBgmId = value;
    return previous;
}
