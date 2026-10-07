#include "src/overlays/ov001/SceneEntryContext.h"

u8 SetSceneEntrySecondaryDisplayId(int index, u8 value)
{
    SceneEntry *entry = gSceneEntryContext->table->entries[index];
    u8 previous = entry->secondaryDisplayId;

    entry->secondaryDisplayId = value;
    return previous;
}
