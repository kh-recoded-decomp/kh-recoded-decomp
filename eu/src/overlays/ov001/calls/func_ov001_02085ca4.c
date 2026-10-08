#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObjectClass
{
    u8 pad_00[0x70];
    fx32 unk_70;
    fx32 unk_74;
    fx32 unk_78;
    s8 unk_7C;
} FieldObjectClass;

typedef struct FieldObjectWork
{
    u8 pad_000[0x1A8];
    u8 unk_1A8[0x10];
} FieldObjectWork;

typedef struct FieldObject
{
    struct FieldObject *prev;
    struct FieldObject *next;
    FieldObjectClass *objectClass;
    FieldObjectWork *work;
    u8 pad_10[0x8];
    u8 model[0x23];
    u8 unk_3B;
    u8 pad_3C[0x4];
    VecFx32 position;
    u16 unk_4C;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 unk_53;
    u8 pad_54[0x8];
    u16 unk_5C;
    u16 unk_5E;
    VecFx32 origin;
    int unk_6C;
} FieldObject;

extern FieldObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex);
extern void ShadowVolume_Init(void *dest, VecFx32 *position, int value, int mode);
extern void BuildCollisionShape(void *model, VecFx32 *position, int mode, fx32 x, fx32 y, fx32 z,
                                u16 angle, int flags, int layer);
extern void ResetFallingObjectSpawner(FieldObject *object);

FieldObject *func_ov001_02085ca4(FieldObjectClass *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount,
                                 int unk6C, u16 unk5C, VecFx32 *position)
{
    FieldObject *object = FieldObject_Create(objectClass, slotIndex);
    FieldObjectClass *cls = object->objectClass;

    object->position = *position;
    object->unk_4C = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->unk_53 = 0;
    object->unk_3B = (object->unk_3B & ~0xF0) | 0x70;
    ShadowVolume_Init(object->work->unk_1A8, position, 0x299A, 0);
    BuildCollisionShape(object->model, &object->position, cls->unk_7C, cls->unk_70, cls->unk_74, cls->unk_78,
                        object->unk_4C, 1, 3);
    object->unk_5C = unk5C;
    object->unk_6C = unk6C;
    object->origin = *position;
    object->unk_5E = 0;
    ResetFallingObjectSpawner(object);
    object->flags |= 0x4000;
    return object;
}
