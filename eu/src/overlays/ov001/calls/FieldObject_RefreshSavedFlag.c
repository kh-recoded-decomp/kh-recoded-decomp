#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x4E];
    u16 stateFlags;
    u8 pad_50[0x08];
    u8 pendingUpdate;
    s8 configFlags;
} FieldObject;

extern u16 FieldObject_GetSavedValue(FieldObject *object);

void FieldObject_RefreshSavedFlag(FieldObject *object)
{
    if ((object->configFlags & 0x80) || FieldObject_GetSavedValue(object) == 0) {
        object->stateFlags |= 0x10;
    } else {
        object->stateFlags &= ~0x10;
    }
    object->pendingUpdate = 0;
}
