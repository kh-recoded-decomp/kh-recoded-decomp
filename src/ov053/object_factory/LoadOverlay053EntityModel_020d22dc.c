#include "nitro/types.h"

typedef struct ModelSetupDesc {
    u32 file;
    u32 palette;
    void *animData;
    void *partData;
    s32 partMask;
    void *extraData;
} ModelSetupDesc;

typedef struct EntryGroupDesc {
    u32 unk_00;
    u32 paletteParams;
    u32 mode;
    u32 vramParams;
    u32 unk_10;
} EntryGroupDesc;

typedef struct SelectionModelInfo {
    u8 unk_00;
    u8 modelFile;
    u8 paletteIndex;
} SelectionModelInfo;

typedef struct SelectionRecord {
    u8 pad_00[0x10];
    SelectionModelInfo model;
} SelectionRecord;

typedef struct FieldState {
    u8 pad_0000[0x27b6];
    u8 lowBits : 6;
    u8 pendingSubModels : 1;
    u8 highBit : 1;
} FieldState;

typedef struct Entity {
    u8 pad_000[0x230];
    u8 *resourceHeader;
    u8 pad_234[0x6cc - 0x234];
    u8 partData[0x72c - 0x6cc];
    u8 extraData[0x9b4 - 0x72c];
    u8 selection;
    u8 pad_9b5[3];
    u32 pendingIndex;
    u8 pad_9bc[0xb68 - 0x9bc];
    u8 modelObject[0xfc8 - 0xb68];
    u8 unitResources[0x101c - 0xfc8];
    u8 animData[0x1100 - 0x101c];
    u16 entryGroupId;
} Entity;

extern FieldState *data_ov001_020a0460;
extern SelectionRecord *func_0204f768(u32 index);
extern void InitUnitResources_020aa264(void *unit, void *arg, int kind, u32 selection, int extra);
extern void SetPendingFromTable_020a9598(int index);
extern BOOL func_ov001_0206e31c(void);
extern BOOL IsPlayerEntryFlagSet_02050014(u32 selection, int flag);
extern BOOL func_ov001_0206e2b0(void);
extern void LoadModelObject_020a998c(void *object, ModelSetupDesc *desc);
extern void ZeroBytes0x14_020a8adc(EntryGroupDesc *desc);
extern u32 MakePaletteUploadParams130_020a9744(u32 index);
extern u32 MakePaletteUploadParams145_020a976c(u32 index);
extern u16 func_ov021_020a89a8(EntryGroupDesc *desc);
extern void ClearPendingWord_020a95b4(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void SetSubModelsEnabled_020ceaf4(Entity *entity, int enable);

void LoadOverlay053EntityModel_020d22dc(Entity *entity)
{
    ModelSetupDesc desc;
    EntryGroupDesc group;
    SelectionModelInfo *info;

    info = &func_0204f768(entity->selection)->model;
    InitUnitResources_020aa264(entity->unitResources, entity->resourceHeader + 4, entity->pendingIndex, entity->selection, 0);
    SetPendingFromTable_020a9598(entity->pendingIndex);
    desc.file = info->modelFile;
    desc.palette = 0;
    desc.animData = entity->animData;
    desc.partData = entity->partData;
    desc.extraData = entity->extraData;
    desc.partMask = 0x23;
    if (!func_ov001_0206e31c()) {
        desc.partMask |= 4;
    } else {
        desc.partMask |= 8;
    }
    if (IsPlayerEntryFlagSet_02050014(entity->selection, 0xc) && !func_ov001_0206e2b0()) {
        desc.partMask |= 0x80;
    }
    LoadModelObject_020a998c(entity->modelObject, &desc);
    ZeroBytes0x14_020a8adc(&group);
    group.vramParams = MakePaletteUploadParams130_020a9744(info->paletteIndex);
    group.paletteParams = MakePaletteUploadParams145_020a976c(info->paletteIndex);
    group.mode = 3;
    entity->entryGroupId = func_ov021_020a89a8(&group);
    ClearPendingWord_020a95b4();
    if (func_ov001_020645c8(0x351f) || data_ov001_020a0460->pendingSubModels) {
        SetSubModelsEnabled_020ceaf4(entity, 1);
    }
}
