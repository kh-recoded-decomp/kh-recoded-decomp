#include "nitro/types.h"

typedef struct {
    u8 pad_00;
    u8 modelFile;
    u8 paletteId;
} ModelInfo;

typedef struct {
    u8 pad_00[0x10];
    ModelInfo model;
} SelectionRecord;

typedef struct {
    u32 file;
    u32 palette;
    void *texture;
    void *user;
    s32 partMask;
    void *extra;
} ModelSetupDesc;

typedef struct {
    u8 pad_00[4];
    u8 data[4];
} ResourceOwner;

typedef struct {
    u8 pad_000[0x230];
    ResourceOwner *owner;
    u8 pad_234[0x6cc - 0x234];
    u8 modelUser[0x72c - 0x6cc];
    u8 modelExtra[0x930 - 0x72c];
    u8 kind;
    u8 pad_931[0x9d4 - 0x931];
    u8 modelSets[0xe34 - 0x9d4];
    u8 unit[0xe88 - 0xe34];
    u8 texture[4];
} Actor;

extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern void InitUnitResources_020aa264(void *unit, void *arg, int kind, u32 selection, int extra);
extern void SetPendingFromTable_020a9598(int index);
extern void LoadModelObject_020a998c(void *obj, ModelSetupDesc *desc);
extern void ClearPendingWord_020a95b4(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void Actor_SetModelSetsVisible_020cd078(Actor *actor, BOOL enable);

void LoadActorModel_020c7510(Actor *actor)
{
    ModelInfo *info = &GetOverlaySelectionRecord(actor->kind)->model;
    ModelSetupDesc setup;

    InitUnitResources_020aa264(actor->unit, actor->owner->data, 0, actor->kind, 0);
    SetPendingFromTable_020a9598(0);
    setup.file = info->modelFile;
    setup.palette = 0;
    setup.texture = actor->texture;
    setup.user = actor->modelUser;
    setup.extra = actor->modelExtra;
    setup.partMask = 0x13;
    LoadModelObject_020a998c(actor->modelSets, &setup);
    ClearPendingWord_020a95b4();
    if (func_ov001_020645c8(0x351f)) {
        Actor_SetModelSetsVisible_020cd078(actor, TRUE);
    }
}
