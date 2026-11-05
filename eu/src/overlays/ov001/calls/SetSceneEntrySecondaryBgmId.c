#include "src/overlays/ov001/SceneEntryContext.h"

u8 SetSceneEntrySecondaryBgmId(int index, u8 value)
{
    SceneEntry *entry = gSceneEntryContext->table->entries[index];
    u8 previous = entry->secondaryBgmId;

    entry->secondaryBgmId = value;
    return previous;
}
