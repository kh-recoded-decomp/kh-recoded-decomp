#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x14];
    void (*update)(struct FieldObject *object);
    u8 pad_18[0x28];
    VecFx32 position;
    u16 angle;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 unk_53;
    u32 unk_54;
    u32 counter : 16;
    u32 unk_58_16 : 16;
    u8 pad_5c[8];
    u16 timer;
    u8 active;
    u8 latched : 1;
    u8 unk_67_1 : 1;
    u8 phase : 6;
    u32 unk_68;
    VecFx32 velocity;
} FieldObject;

extern FieldObject *FieldObject_Create_0207f440(void *objectClass, u8 slotIndex);
extern void func_ov001_02082c50(FieldObject *object);
extern const VecFx32 data_02053438;

FieldObject *FieldObject_CreateWithTimer_02083648(void *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount, const VecFx32 *position)
{
    FieldObject *object = FieldObject_Create_0207f440(objectClass, slotIndex);

    object->position = *position;
    object->angle = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->unk_53 = 0;
    object->timer = 0;
    object->active = 1;
    object->velocity = data_02053438;
    object->counter = 0;
    object->update = func_ov001_02082c50;
    object->latched = 0;
    object->phase = 0;
    object->unk_68 = 0;
    return object;
}
