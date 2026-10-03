#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    struct FieldObject *prev;
    struct FieldObject *next;
    void *objectClass;
    u8 *work;
    u8 pad_10[0x2b];
    u8 layerLow : 4;
    u8 layerHigh : 4;
    u8 pad_3c[4];
    VecFx32 position;
    u16 timer;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u8 state;
} FieldObject;

extern const VecFx32 data_02053438;
extern FieldObject *FieldObject_Create_0207f440(void *objectClass, int slotIndex);

FieldObject *FieldObject_CreateAtOrigin_020a0c78(void *objectClass, int slotIndex, u16 saveBitOffset, u8 saveBitCount)
{
    FieldObject *object = FieldObject_Create_0207f440(objectClass, slotIndex);

    object->position = data_02053438;
    object->timer = 0;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->state = 0;
    object->layerHigh = 0;
    object->flags |= 0x4000;
    return object;
}
