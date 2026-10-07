#include "src/overlays/ov001/SceneEntryContext.h"

u8 SetSceneEntryPrimaryDisplayId(int index, u8 value)
{
    SceneEntry *entry = gSceneEntryContext->table->entries[index];
    u8 previous = entry->primaryDisplayId;

    entry->primaryDisplayId = value;
    return previous;
}
