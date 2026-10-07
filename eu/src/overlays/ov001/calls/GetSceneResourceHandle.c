#include "src/overlays/ov001/SceneEntryContext.h"

void *GetSceneResourceHandle(void)
{
    return gSceneEntryContext->table->resourceHandle;
}
