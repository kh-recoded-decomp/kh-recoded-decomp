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

extern ObjectClass *CreateByteGrid_0207f380(int headerSize, int width, int height);
extern void func_ov001_0207f0d0(void);
extern void func_ov001_0207f128(void);
extern void FieldObject_RespawnIdle_020a09c4(void);
extern void func_ov001_0207f1e8(void);
extern void func_ov001_0207f20c(void);
extern void func_ov001_0207f244(void);
extern void _fp_init_020a0a64(void);
extern void func_ov010_020a0a68(void);
extern void _fp_init_020a0a6c(void);
extern void func_ov010_020a0a70(void);
extern void FSi_CloseFileCommand_020a0a78(void);
extern void FieldObject_DrawFrontView_020a0a7c(void);

ObjectClass *FieldObjectClass_CreateFrontView_020a0bd4(int height)
{
    ObjectClass *objectClass = CreateByteGrid_0207f380(0x84, 0x5c, height);

    objectClass->value = 0x10;
    objectClass->shapeKind = -1;
    objectClass->sizeX = 0;
    objectClass->sizeY = 0;
    objectClass->sizeZ = 0;
    objectClass->kind = 0xb3;
    objectClass->group = 0xff;
    objectClass->target = -1;
    objectClass->onCreate = func_ov001_0207f0d0;
    objectClass->onDestroy = func_ov001_0207f128;
    objectClass->onUpdate = FieldObject_RespawnIdle_020a09c4;
    objectClass->onDraw = func_ov001_0207f1e8;
    objectClass->onEnter = func_ov001_0207f20c;
    objectClass->onLeave = func_ov001_0207f244;
    objectClass->handler1c = NULL;
    objectClass->onTouch = _fp_init_020a0a64;
    objectClass->getField40 = func_ov010_020a0a68;
    objectClass->setPosition = _fp_init_020a0a6c;
    objectClass->getField50 = func_ov010_020a0a70;
    objectClass->handler38 = NULL;
    objectClass->onClose = FSi_CloseFileCommand_020a0a78;
    objectClass->handler34 = NULL;
    objectClass->onDrawExtra = FieldObject_DrawFrontView_020a0a7c;
    objectClass->layer = 0x11;
    return objectClass;
}
