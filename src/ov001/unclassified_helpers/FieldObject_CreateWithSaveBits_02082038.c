#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x14];
    int (*handler)(void);
    u8 pad_18[0x28];
    VecFx32 position;
    u8 pad_4c[0x4];
    u16 saveBitOffset;
    u8 saveBitCount;
} FieldObject;

extern FieldObject *FieldObject_Create_0207f440(void *objectClass, u8 slotIndex);
extern int FSi_CloseFileCommand_02081f80(void);
extern const VecFx32 data_02053438;

FieldObject *FieldObject_CreateWithSaveBits_02082038(void *objectClass, u8 slotIndex, u16 saveBitOffset, u8 saveBitCount)
{
    FieldObject *object = FieldObject_Create_0207f440(objectClass, slotIndex);

    object->position = data_02053438;
    object->saveBitOffset = saveBitOffset;
    object->saveBitCount = saveBitCount;
    object->handler = FSi_CloseFileCommand_02081f80;
    return object;
}
