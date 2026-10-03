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

extern ObjectClass *CreateByteGrid_0207f380(int headerSize, int width, int height);
extern void func_ov001_0207f0d0(void);
extern void func_ov001_0207f128(void);
extern void func_ov009_020a0778(void);
extern void func_ov001_0207f1e8(void);
extern void func_ov001_0207f20c(void);
extern void func_ov001_0207f244(void);
extern void func_ov009_020a08e8(void);
extern void GetFieldPtrAt0x40_020a08ec(void);
extern void FieldObject_SetLiftedPosition_020a08f4(void);
extern void GetIndirectFieldAt0x50_020a0944(void);
extern void ScriptCmd_SpawnModeTwo_020a0950(void);
extern void func_ov009_020a094c(void);
extern void GetFieldPtrAt0x40_020a08f0(void);

ObjectClass *FieldObjectClass_Create_020a0ad0(int height)
{
    ObjectClass *objectClass = CreateByteGrid_0207f380(0x84, 0x60, height);

    objectClass->value = 0;
    objectClass->active = 1;
    objectClass->radius = 0x800;
    objectClass->scale = 0x1000;
    objectClass->offset = 0;
    objectClass->kind = 0x86;
    objectClass->visible = 1;
    objectClass->size = 0x3000;
    objectClass->onCreate = func_ov001_0207f0d0;
    objectClass->onDestroy = func_ov001_0207f128;
    objectClass->onUpdate = func_ov009_020a0778;
    objectClass->onDraw = func_ov001_0207f1e8;
    objectClass->onEnter = func_ov001_0207f20c;
    objectClass->onLeave = func_ov001_0207f244;
    objectClass->handler1c = NULL;
    objectClass->onTouch = func_ov009_020a08e8;
    objectClass->getField40 = GetFieldPtrAt0x40_020a08ec;
    objectClass->getPosition = FieldObject_SetLiftedPosition_020a08f4;
    objectClass->getField50 = GetIndirectFieldAt0x50_020a0944;
    objectClass->onSpawn = ScriptCmd_SpawnModeTwo_020a0950;
    objectClass->onClose = func_ov009_020a094c;
    objectClass->getAlias = GetFieldPtrAt0x40_020a08f0;
    objectClass->layer = 0xf;
    return objectClass;
}
