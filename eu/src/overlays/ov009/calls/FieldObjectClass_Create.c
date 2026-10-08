#include "nitro/types.h"

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
    ObjectCallback getPosition;
    ObjectCallback getField40;
    ObjectCallback getField50;
    ObjectCallback onClose;
    ObjectCallback getAlias;
    ObjectCallback onSpawn;
    u8 pad_3c[0x10];
    int size;
    int value;
    u8 pad_54[0x10];
    u16 kind;
    u8 pad_66[0xa];
    int radius;
    int scale;
    int offset;
    u8 active;
    u8 layer;
    u8 pad_7e[4];
    u8 visible;
} ObjectClass;

extern ObjectClass *CreateByteGrid(int headerSize, int width, int height);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void FieldObject_RespawnSwitch(void);
extern void func_ov001_0207f210(void);
extern void ReleaseOwnerResource(void);
extern void func_ov001_0207f26c(void);
extern void func_ov009_020a0908(void);
extern void GetFieldPtrAt0x40(void);
extern void FieldObject_SetLiftedPosition(void);
extern void GetIndirectFieldAt0x50(void);
extern void ScriptCmd_SpawnModeTwo(void);
extern void func_ov009_020a096c(void);
extern void GetFieldPtrAt0x40_020a0910(void);

ObjectClass *FieldObjectClass_Create(int height)
{
    ObjectClass *objectClass = CreateByteGrid(0x84, 0x60, height);

    objectClass->value = 0;
    objectClass->active = 1;
    objectClass->radius = 0x800;
    objectClass->scale = 0x1000;
    objectClass->offset = 0;
    objectClass->kind = 0x86;
    objectClass->visible = 1;
    objectClass->size = 0x3000;
    objectClass->onCreate = AcquireEffectRecordPair;
    objectClass->onDestroy = FieldObject_EnsureModelsLoaded;
    objectClass->onUpdate = FieldObject_RespawnSwitch;
    objectClass->onDraw = func_ov001_0207f210;
    objectClass->onEnter = ReleaseOwnerResource;
    objectClass->onLeave = func_ov001_0207f26c;
    objectClass->handler1c = NULL;
    objectClass->onTouch = func_ov009_020a0908;
    objectClass->getField40 = GetFieldPtrAt0x40;
    objectClass->getPosition = FieldObject_SetLiftedPosition;
    objectClass->getField50 = GetIndirectFieldAt0x50;
    objectClass->onSpawn = ScriptCmd_SpawnModeTwo;
    objectClass->onClose = func_ov009_020a096c;
    objectClass->getAlias = GetFieldPtrAt0x40_020a0910;
    objectClass->layer = 0xf;
    return objectClass;
}
