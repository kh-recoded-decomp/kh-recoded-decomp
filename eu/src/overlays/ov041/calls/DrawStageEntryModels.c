#include "src/overlays/ov041/StageEntryRender.h"

void DrawStageEntryModels(StageEntrySlot *slot, BOOL drawShadow)
{
    StageModelWork *work = gMovieContextState->stageWork;
    StageEntry *entry;
    int i;

    /* Installed only on the slots registered in work->entries. */
    for (i = 0; i < work->entryCount; ++i) {
        entry = &work->entries[i];
        if (slot == &entry->slot) {
            data_ov041_020cff48.entry = entry;
            break;
        }
    }
    if (drawShadow) {
        VecFx32 position;
        GetPositionAboveGround(&position, entry);
        slot->shadowPosition = position;
        ShadowVolume_Draw(&slot->shadowPosition);
    } else if (!(slot->flags & 0x20)) {
        SceneNode_Draw(&slot->node);
    }
    if (entry->kind != 0 && entry->kind != 0x11 && entry->kind != 0x12) {
        VecFx32 position;
        GetPositionAboveGround(&position, entry);
        entry->shadow.position = position;
        entry->shadow.position.y = gStageShadowHeights[work->shadowHeightIndex];
        SceneNode_Draw(&entry->shadow);
    }
}
