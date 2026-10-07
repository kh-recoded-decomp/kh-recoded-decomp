#include "src/overlays/ov001/SceneEntryContext.h"

u16 GetCurrentSceneEntrySlotId(void)
{
    return gSceneEntryContext->table->entries[gSceneEntryContext->currentEntry]->slotId;
}
