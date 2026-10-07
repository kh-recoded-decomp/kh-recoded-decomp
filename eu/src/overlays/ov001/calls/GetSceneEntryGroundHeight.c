#include "src/overlays/ov001/SceneEntryContext.h"

fx32 GetSceneEntryGroundHeight(int index)
{
    return gSceneEntryContext->table->entries[index]->groundHeight;
}
