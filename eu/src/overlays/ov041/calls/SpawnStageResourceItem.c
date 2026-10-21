#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageResources.h"

extern void selectJointAnimationBlend(void *model, u16 track, void *blend, int animation);
extern void func_01ffb2f8(void *model, u16 track, int frame);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);

/*
 * Takes the first free item of a resource list (lists of category 0x1b and up are stand-alone, the others
 * belong to a category group), starts its five animation tracks, places it and marks it in use.
 */
StageResourceItem *SpawnStageResourceItem(int category, u8 index, u8 animation, const VecFx32 *position,
                                       BOOL persistent)
{
    StageWork *work = gMovieContextState->stageWork;
    int slot = -1;
    StageResourceList *list;
    StageResourceItem *item;
    StageItemModel *model;
    int i;

    if (category < 0) {
        return NULL;
    }
    if (category == 200) {
        return NULL;
    }
    if (category >= 0x1b) {
        list = work->lists[index];
    } else {
        list = &work->groups[category]->lists[index];
    }
    for (i = 0; i < list->count; i++) {
        item = &list->items[i];
        if (!(item->flags & STAGE_ITEM_IN_USE)) {
            slot = i;
            break;
        }
    }
    model = &list->items[slot].model;
    for (i = 0; i < 5; i++) {
        selectJointAnimationBlend(model, i, model->blend, animation);
        func_01ffb2f8(model, i, 0);
    }
    model->position = *position;
    MTX_RotY33_(&model->rotation, 0, FX32_ONE);
    item->flags |= STAGE_ITEM_VISIBLE;
    item->flags |= STAGE_ITEM_DRAW;
    item->flags |= STAGE_ITEM_IN_USE;
    if (persistent) {
        item->flags |= STAGE_ITEM_PERSISTENT;
    }
    return &list->items[slot];
}
