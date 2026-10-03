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

extern ObjectClass *CreateByteGrid_0207f380(int headerSize, int width, int height);
extern void func_ov001_0207f0d0(void);
extern void func_ov001_0207f128(void);
extern void func_ov010_020a069c(void);
extern void func_ov001_0207f1e8(void);
extern void func_ov001_0207f20c(void);
extern void func_ov001_0207f244(void);
extern void _fp_init_020a0794(void);
extern void func_ov010_020a0798(void);
extern void FieldObject_SetPosition_020a079c(void);
extern void func_ov010_020a0808(void);
extern void FSi_CloseFileCommand_020a0810(void);

ObjectClass *FieldObjectClass_CreateShaped_020a0884(int height, const ShapedClassParams *params)
{
    ObjectClass *objectClass = CreateByteGrid_0207f380(0x88, 0x58, height);

    objectClass->blendIndex = params->blendIndex;
    objectClass->value = params->value;
    objectClass->shapeKind = params->shapeKind;
    objectClass->sizeX = params->size.x;
    objectClass->sizeY = params->size.y;
    objectClass->sizeZ = params->size.z;
    objectClass->kind = params->kind;
    objectClass->group = 0xff;
    objectClass->target = -1;
    objectClass->onCreate = func_ov001_0207f0d0;
    objectClass->onDestroy = func_ov001_0207f128;
    objectClass->onUpdate = func_ov010_020a069c;
    objectClass->onDraw = func_ov001_0207f1e8;
    objectClass->onEnter = func_ov001_0207f20c;
    objectClass->onLeave = func_ov001_0207f244;
    objectClass->handler1c = NULL;
    objectClass->onTouch = _fp_init_020a0794;
    objectClass->getField40 = func_ov010_020a0798;
    objectClass->setPosition = FieldObject_SetPosition_020a079c;
    objectClass->getField50 = func_ov010_020a0808;
    objectClass->handler38 = NULL;
    objectClass->onClose = FSi_CloseFileCommand_020a0810;
    objectClass->handler34 = NULL;
    objectClass->layer = 0x10;
    return objectClass;
}
