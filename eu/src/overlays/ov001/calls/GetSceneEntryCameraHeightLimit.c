#include "src/overlays/ov001/SceneEntryContext.h"

fx32 GetSceneEntryCameraHeightLimit(int index)
{
    return gSceneEntryContext->table->entries[index]->cameraHeightLimit;
}
