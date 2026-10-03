#include "nitro/types.h"

typedef struct ModelInfo {
    u8 pad_00;
    u8 modelFile;
    u8 paletteId;
} ModelInfo;

typedef struct SelectionRecord {
    u8 pad_00[0x10];
    ModelInfo model;
} SelectionRecord;

typedef struct ModelSetupDesc {
    u32 file;
    u32 palette;
    u32 pad_08;
    u32 userValue;
    s32 partMask;
    u32 hasExtra;
} ModelSetupDesc;

typedef struct EntryGroupDesc {
    int resourceId;
    u32 animationName;
    s32 slotCount;
    u32 modelName;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct ResourceOwner {
    u8 pad_00[4];
    u8 data[4];
} ResourceOwner;

typedef struct Entity {
    u8 pad_000[0x230];
    ResourceOwner *owner;
    u8 pad_234[0x6cc - 0x234];
    u8 modelUser[4];
    u8 pad_6d0[0x9b4 - 0x6d0];
    u8 kind;
    u8 pad_9b5[3];
    int tableIndex;
    u8 pad_9bc[0xb68 - 0x9bc];
    u32 model[(0xfc8 - 0xb68) / 4];
    u8 unit[0x1100 - 0xfc8];
    u16 groupId;
} Entity;

extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern void InitUnitResources_020aa264(void *unit, void *arg, int kind, u32 selection, int extra);
extern void SetPendingFromTable_020a9598(int index);
extern void LoadModelObject_020a998c(void *obj, ModelSetupDesc *desc);
extern void ZeroBytes0x14_020a8adc(void *obj);
extern u32 MakePaletteUploadParams130_020a9744(u32 index);
extern u32 MakePaletteUploadParams145_020a976c(u32 index);
extern int func_ov021_020a89a8(EntryGroupDesc *desc);
extern void ClearPendingWord_020a95b4(void);
extern void SetBit1WhenBit0Set_020a9ce8(u32 *flags, s32 enable);

void LoadOverlay057EntityModel_020d4004(Entity *entity)
{
    ModelInfo *info = &GetOverlaySelectionRecord(entity->kind)->model;
    ModelSetupDesc setup;
    EntryGroupDesc group;

    InitUnitResources_020aa264(entity->unit, entity->owner->data, entity->tableIndex, entity->kind, 0);
    SetPendingFromTable_020a9598(entity->tableIndex);
    setup.file = info->modelFile;
    setup.palette = 0;
    setup.pad_08 = 0;
    setup.userValue = (u32)entity->modelUser;
    setup.partMask = 0x100;
    setup.hasExtra = 0;
    LoadModelObject_020a998c(entity->model, &setup);
    ZeroBytes0x14_020a8adc(&group);
    group.modelName = MakePaletteUploadParams130_020a9744(info->paletteId);
    group.animationName = MakePaletteUploadParams145_020a976c(info->paletteId);
    group.slotCount = 3;
    entity->groupId = func_ov021_020a89a8(&group);
    ClearPendingWord_020a95b4();
    SetBit1WhenBit0Set_020a9ce8(entity->model, 1);
}
