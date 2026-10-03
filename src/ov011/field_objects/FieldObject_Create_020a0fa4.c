#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*ObjectFunc)(void);

typedef struct FieldObject {
    ObjectFunc init;
    ObjectFunc release;
    ObjectFunc update;
    ObjectFunc destroy;
    ObjectFunc releaseChild;
    u8 pad_14[4];
    ObjectFunc reset;
    ObjectFunc onTouch;
    ObjectFunc onIdle;
    ObjectFunc setPosition;
    ObjectFunc getAnchor;
    ObjectFunc beginSpawn;
    ObjectFunc load;
    ObjectFunc getCenter;
    ObjectFunc onHit;
    ObjectFunc draw;
    u8 pad_40[0xc];
    fx32 radius;
    s32 state;
    u8 pad_54[0x10];
    u16 soundId;
    u8 pad_66[0xa];
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    u8 kind;
    u8 layer;
    u8 pad_7e[4];
    u8 hidden;
    u8 pad_83;
    s32 timer;
} FieldObject;

extern FieldObject *CreateByteGrid_0207f380(int headerSize, int width, int height);
extern void func_ov001_0207f0d0(void);
extern void func_ov001_0207f128(void);
extern void func_ov011_020a07bc(void);
extern void func_ov001_0207f1e8(void);
extern void ReleaseChildResourceAndForward_020a0910(void);
extern void func_ov001_0207f244(void);
extern void _fp_init_020a094c(void);
extern void func_ov011_020a0950(void);
extern void FieldObject_SetPositionAndSync_020a0954(void);
extern void FieldObject_BeginSpawn_020a0988(void);
extern void func_ov011_020a0d24(void);
extern void func_ov011_020a0fa0(void);
extern void FieldObject_Draw_020a0e30(void);

FieldObject *FieldObject_Create_020a0fa4(int height)
{
    FieldObject *object = CreateByteGrid_0207f380(0x18c, 0x68, height);

    object->state = 0;
    object->kind = 3;
    object->scaleX = 0x1800;
    object->scaleY = 0x1800;
    object->scaleZ = 0x1800;
    object->soundId = 0xbb;
    object->hidden = 0;
    object->radius = 0x3000;
    object->init = func_ov001_0207f0d0;
    object->release = func_ov001_0207f128;
    object->update = func_ov011_020a07bc;
    object->destroy = func_ov001_0207f1e8;
    object->releaseChild = ReleaseChildResourceAndForward_020a0910;
    object->reset = func_ov001_0207f244;
    object->onTouch = NULL;
    object->onIdle = _fp_init_020a094c;
    object->getAnchor = func_ov011_020a0950;
    object->setPosition = FieldObject_SetPositionAndSync_020a0954;
    object->beginSpawn = FieldObject_BeginSpawn_020a0988;
    object->onHit = NULL;
    object->load = func_ov011_020a0d24;
    object->getCenter = func_ov011_020a0fa0;
    object->draw = FieldObject_Draw_020a0e30;
    object->layer = 0xe;
    object->timer = 0;
    return object;
}
