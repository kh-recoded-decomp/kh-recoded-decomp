#include "src/overlays/ov087/CarouselModels.h"

extern void LoadDefaultProjectionValues(void *projection);
extern u32 BuildSlotImageParams(int slot, u32 low);
extern void *func_0202c4a0(u32 fileId, u32 param2);
extern void InitSharedRecordAndDispatchAlt(void *dst, int params, void *info, int b);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

/* Bind one carousel model to its record, start its five animation tracks, scale it and free the info file. */
static inline void LoadCarouselModel(CarouselModelView *model, void *info, int recordId, fx32 scale)
{
    int track;

    InitSharedRecordAndDispatchAlt(model, BuildSlotImageParams(2, recordId), info, 0xe);
    for (track = 0; track < 5; track++) {
        selectJointAnimationBlend(model, track, model->animationTable, 0);
    }
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    NNSi_FndFreeFromDefaultHeap(info);
}

/*
 * Load the centre model and one model per carousel entry; with lockedId != -1 the last entry
 * shows that id instead of its own.
 *
 * The definition takes a third parameter, `entry`, that neither caller passes (InitPanelScene
 * calls with two arguments and leaves r2 holding whatever it last computed). It is only the loop
 * counter, reset before use, but the ROM's register assignment proves the original declared it
 * here: the counter shares the incoming parameter's register number, which places it in r8 after
 * the info file and the entry offset. No local variable reproduces that.
 */
void LoadCarouselModels(CarouselSceneView *scene, int lockedId, int entry)
{
    CarouselResourceIds recordIds = data_ov087_020c7d1c;
    CarouselResourceIds infoIds = data_ov087_020c7d3c;
    int id;
    void *info;

    LoadDefaultProjectionValues(scene->projection);
    scene->projection[10] = 0x1c000;
    info = func_0202c4a0(BuildSlotImageParams(2, 4), 0xe);
    LoadCarouselModel(&scene->centerModel, info, 5, 0x2000);

    for (entry = 0; entry < scene->entryCount; entry++) {
        if (lockedId != -1 && entry == scene->entryCount - 1) {
            id = lockedId;
        } else {
            id = entry;
        }
        scene->entries[entry].id = id;
        info = func_0202c4a0(BuildSlotImageParams(2, infoIds.ids[id]), 0xe);
        LoadCarouselModel(&scene->entries[entry].model, info, recordIds.ids[id], 0x800);
    }
}
