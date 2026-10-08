#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*ObjectCallback)(void);

typedef struct ShapedClassParams {
    int value;
    s16 kind;
    s8 blendIndex;
    s8 shapeKind;
    VecFx32 size;
} ShapedClassParams;

typedef struct ObjectClass {
    ObjectCallback onCreate;
    ObjectCallback onDestroy;
    ObjectCallback onUpdate;
    ObjectCallback onDraw;
    ObjectCallback onEnter;
    ObjectCallback unused14;
    ObjectCallback onLeave;
    ObjectCallback handler1c;
    ObjectCallback onTouch;
    ObjectCallback setPosition;
    ObjectCallback getField40;
    ObjectCallback getField50;
    ObjectCallback onClose;
    ObjectCallback handler34;
    ObjectCallback handler38;
    u8 pad_3c[0x10];
    int target;
    int value;
    u8 pad_54[0x10];
    s16 kind;
    u8 pad_66[0xa];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
    u8 layer;
    u8 pad_7e[4];
    u8 group;
    u8 pad_83;
    s8 blendIndex;
} ObjectClass;

extern ObjectClass *CreateByteGrid(int headerSize, int width, int height);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void FieldObject_RespawnShaped(void);
extern void func_ov001_0207f210(void);
extern void ReleaseOwnerResource(void);
extern void func_ov001_0207f26c(void);
extern void func_ov010_020a07b4(void);
extern void func_ov010_020a07b8(void);
extern void FieldObject_SetPosition_020a07bc(void);
extern void func_ov010_020a0828(void);
extern void func_ov010_020a0830(void);

ObjectClass *FieldObjectClass_CreateShaped(int height, const ShapedClassParams *params)
{
    ObjectClass *objectClass = CreateByteGrid(0x88, 0x58, height);

    objectClass->blendIndex = params->blendIndex;
    objectClass->value = params->value;
    objectClass->shapeKind = params->shapeKind;
    objectClass->sizeX = params->size.x;
    objectClass->sizeY = params->size.y;
    objectClass->sizeZ = params->size.z;
    objectClass->kind = params->kind;
    objectClass->group = 0xff;
    objectClass->target = -1;
    objectClass->onCreate = AcquireEffectRecordPair;
    objectClass->onDestroy = FieldObject_EnsureModelsLoaded;
    objectClass->onUpdate = FieldObject_RespawnShaped;
    objectClass->onDraw = func_ov001_0207f210;
    objectClass->onEnter = ReleaseOwnerResource;
    objectClass->onLeave = func_ov001_0207f26c;
    objectClass->handler1c = NULL;
    objectClass->onTouch = func_ov010_020a07b4;
    objectClass->getField40 = func_ov010_020a07b8;
    objectClass->setPosition = FieldObject_SetPosition_020a07bc;
    objectClass->getField50 = func_ov010_020a0828;
    objectClass->handler38 = NULL;
    objectClass->onClose = func_ov010_020a0830;
    objectClass->handler34 = NULL;
    objectClass->layer = 0x10;
    return objectClass;
}
