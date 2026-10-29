/* Pending func_ov087_020c6ad0; excluded from the linked build and C coverage. */
#include "src/overlays/ov087/CarouselModels.h"

extern void LoadDefaultProjectionValues(u32 *);
extern u32 BuildSlotImageParams(int, u32);
extern void *func_0202c4a0(u32, int);
extern void InitSharedRecordAndDispatchAlt(CarouselModelView *, u32, void *, int);
extern void selectJointAnimationBlend(CarouselModelView *, u16, void *, s16);
extern void NNSi_FndFreeFromDefaultHeap(void *);

static inline void BindInitialAnimations(CarouselModelView *model)
{
    int track;
    for (track = 0; track < 5; track++) {
        selectJointAnimationBlend(model, (u16)track, &model->animationTable, 0);
    }
}

void LoadCarouselModels(CarouselSceneView *scene, int lockedId)
{
    CarouselResourceIds recordResources = data_ov087_020c7d1c;
    CarouselResourceIds infoResources = data_ov087_020c7d3c;
    void *info;
    int entry;
    int id;

    LoadDefaultProjectionValues(scene->projection);
    scene->projection[10] = 0x1c000;
    info = func_0202c4a0(BuildSlotImageParams(2, 4), 14);
    InitSharedRecordAndDispatchAlt(&scene->centerModel,
        BuildSlotImageParams(2, 5), info, 14);
    BindInitialAnimations(&scene->centerModel);
    scene->centerModel.scale.z = 0x2000;
    scene->centerModel.scale.y = 0x2000;
    scene->centerModel.scale.x = 0x2000;
    NNSi_FndFreeFromDefaultHeap(info);

    for (entry = 0; entry < scene->entryCount; entry++) {
        if (lockedId != -1 && entry == scene->entryCount - 1) {
            id = lockedId;
        } else {
            id = entry;
        }
        scene->entries[entry].id = id;
        void *entryInfo = func_0202c4a0(BuildSlotImageParams(2,
            infoResources.ids[id]), 14);
        InitSharedRecordAndDispatchAlt(&scene->entries[entry].model,
            BuildSlotImageParams(2, recordResources.ids[id]), entryInfo, 14);
        BindInitialAnimations(&scene->entries[entry].model);
        scene->entries[entry].model.scale.z = 0x800;
        scene->entries[entry].model.scale.y = 0x800;
        scene->entries[entry].model.scale.x = 0x800;
        NNSi_FndFreeFromDefaultHeap(entryInfo);
    }
}
