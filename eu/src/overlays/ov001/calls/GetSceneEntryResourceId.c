#include "src/overlays/ov001/SceneEntryContext.h"

u32 GetSceneEntryResourceId(int index)
{
    return gSceneEntryContext->table->entries[index]->resourceId;
}
