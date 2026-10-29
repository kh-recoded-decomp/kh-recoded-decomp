#include "nitro/types.h"

typedef struct {
    u32 ids[8];
} FileIdTable;

typedef struct {
    u8 animState[0xb0];
    s32 scaleX;
    s32 scaleY;
    s32 scaleZ;
    u8 pad[0xd8 - 0xbc];
    u8 blendTable[0x104 - 0xd8];
} PanelModel;

typedef struct {
    int kind;
    PanelModel model;
} PanelModelSlot;

typedef struct {
    u8 pad0[8];
    int slotCount;
    u8 pad1[0x14 - 0xc];
    PanelModel model;
    PanelModelSlot slots[8];
    u8 projection[0x980 - 0x958];
    s32 projectionValue;
} PanelScene;

extern const FileIdTable data_ov087_020c7cfc;
extern const FileIdTable data_ov087_020c7d1c;

extern void LoadDefaultProjectionValues_0202a7b4(void *projection);
extern unsigned int BuildSlotImageParams_020bc220(int slot, unsigned int low);
extern void *func_0202c48c(u32 fileId, u32 param2);
extern void func_0202ed3c(void *dst, int a, void *info, int b);
extern void selectJointAnimationBlend_0202f2cc(void *animationState, unsigned short trackIndex, void *blendTable, short blendIndex);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

static inline void LoadPanelModel(PanelModel *model, void *file, int animFile, s32 scale)
{
    int track;

    func_0202ed3c(model, BuildSlotImageParams_020bc220(2, animFile), file, 0xe);
    for (track = 0; track < 5; track++) {
        selectJointAnimationBlend_0202f2cc(model, track, model->blendTable, 0);
    }
    model->scaleZ = scale;
    model->scaleY = scale;
    model->scaleX = scale;
    NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
}

void LoadPanelModels_020c6ab0(PanelScene *panel, int lastKind, int index)
{
    FileIdTable animIds = data_ov087_020c7cfc;
    FileIdTable modelIds = data_ov087_020c7d1c;
    int kind;
    void *file;

    LoadDefaultProjectionValues_0202a7b4(panel->projection);
    panel->projectionValue = 0x1c000;
    file = func_0202c48c(BuildSlotImageParams_020bc220(2, 4), 0xe);
    LoadPanelModel(&panel->model, file, 5, 0x2000);

    for (index = 0; index < panel->slotCount; index++) {
        if (lastKind != -1 && index == panel->slotCount - 1) {
            kind = lastKind;
        } else {
            kind = index;
        }
        panel->slots[index].kind = kind;
        file = func_0202c48c(BuildSlotImageParams_020bc220(2, modelIds.ids[kind]), 0xe);
        LoadPanelModel(&panel->slots[index].model, file, animIds.ids[kind], 0x800);
    }
}
