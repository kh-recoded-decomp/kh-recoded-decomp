#include "src/overlays/ov001/SceneEntryContext.h"

u8 GetSceneEntryPatrolPointCount(int index)
{
    return gSceneEntryContext->table->entries[index]->patrolPointCount;
}
