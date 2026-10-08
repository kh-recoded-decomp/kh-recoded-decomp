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
extern void func_ov001_0207f210(void);
extern void ReleaseOwnerResource(void);
extern void func_ov001_0207f26c(void);
extern void func_ov010_020a0a84(void);
extern void func_ov010_020a0a88(void);
extern void func_ov010_020a0a8c(void);
extern void func_ov010_020a0a90(void);
extern void func_ov010_020a0a98(void);
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
    objectClass->onDraw = func_ov001_0207f210;
    objectClass->onEnter = ReleaseOwnerResource;
    objectClass->onLeave = func_ov001_0207f26c;
    objectClass->handler1c = NULL;
    objectClass->onTouch = func_ov010_020a0a84;
    objectClass->getField40 = func_ov010_020a0a88;
    objectClass->setPosition = func_ov010_020a0a8c;
    objectClass->getField50 = func_ov010_020a0a90;
    objectClass->handler38 = NULL;
    objectClass->onClose = func_ov010_020a0a98;
    objectClass->handler34 = NULL;
    objectClass->onDrawExtra = FieldObject_DrawFrontView;
    objectClass->layer = 0x11;
    return objectClass;
}
