#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*ObjectCallback)(void);

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
    ObjectCallback onDrawExtra;
    u8 pad_40[0xc];
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
} ObjectClass;

extern ObjectClass *CreateByteGrid(int headerSize, int width, int height);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void FieldObject_RespawnIdle(void);
extern void FreeFieldObjectClassAnimationBuffers(void);
extern void ReleaseOwnerResource(void);
extern void FreeFieldObjectShapeStorage(void);
extern void FrontViewObject_OnEnabledChangedNoop(void);
extern void FrontViewObject_GetPosition(void);
extern void FrontViewObject_SetPositionNoop(void);
extern void FrontViewObject_GetClassHitResult(void);
extern void FrontViewObject_QueryHitFalse(void);
extern void FieldObject_DrawFrontView(void);

ObjectClass *FieldObjectClass_CreateFrontView(int height)
{
    ObjectClass *objectClass = CreateByteGrid(0x84, 0x5c, height);

    objectClass->value = 0x10;
    objectClass->shapeKind = -1;
    objectClass->sizeX = 0;
    objectClass->sizeY = 0;
    objectClass->sizeZ = 0;
    objectClass->kind = 0xb3;
    objectClass->group = 0xff;
    objectClass->target = -1;
    objectClass->onCreate = AcquireEffectRecordPair;
    objectClass->onDestroy = FieldObject_EnsureModelsLoaded;
    objectClass->onUpdate = FieldObject_RespawnIdle;
    objectClass->onDraw = FreeFieldObjectClassAnimationBuffers;
    objectClass->onEnter = ReleaseOwnerResource;
    objectClass->onLeave = FreeFieldObjectShapeStorage;
    objectClass->handler1c = NULL;
    objectClass->onTouch = FrontViewObject_OnEnabledChangedNoop;
    objectClass->getField40 = FrontViewObject_GetPosition;
    objectClass->setPosition = FrontViewObject_SetPositionNoop;
    objectClass->getField50 = FrontViewObject_GetClassHitResult;
    objectClass->handler38 = NULL;
    objectClass->onClose = FrontViewObject_QueryHitFalse;
    objectClass->handler34 = NULL;
    objectClass->onDrawExtra = FieldObject_DrawFrontView;
    objectClass->layer = 0x11;
    return objectClass;
}
