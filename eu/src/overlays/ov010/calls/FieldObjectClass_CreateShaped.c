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
extern void FreeFieldObjectClassAnimationBuffers(void);
extern void ReleaseOwnerResource(void);
extern void FreeFieldObjectShapeStorage(void);
extern void ShapedObject_OnEnabledChangedNoop(void);
extern void ShapedObject_GetPosition(void);
extern void FieldObject_SetPosition_020a07bc(void);
extern void ShapedObject_GetClassHitResult(void);
extern void ShapedObject_QueryHitFalse(void);

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
    objectClass->onDraw = FreeFieldObjectClassAnimationBuffers;
    objectClass->onEnter = ReleaseOwnerResource;
    objectClass->onLeave = FreeFieldObjectShapeStorage;
    objectClass->handler1c = NULL;
    objectClass->onTouch = ShapedObject_OnEnabledChangedNoop;
    objectClass->getField40 = ShapedObject_GetPosition;
    objectClass->setPosition = FieldObject_SetPosition_020a07bc;
    objectClass->getField50 = ShapedObject_GetClassHitResult;
    objectClass->handler38 = NULL;
    objectClass->onClose = ShapedObject_QueryHitFalse;
    objectClass->handler34 = NULL;
    objectClass->layer = 0x10;
    return objectClass;
}
