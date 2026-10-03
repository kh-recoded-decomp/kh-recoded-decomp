#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x66];
    s16 nextIndex;
} FieldObject;

extern FieldObject *func_ov001_0208635c(void *owner, int index);

BOOL IsObjectInChain_020a3914(FieldObject *object, FieldObject *target)
{
    s16 index = object->nextIndex;
    FieldObject *current;

    while (index != -1) {
        current = func_ov001_0208635c(object->owner, index);
        if (current == target) {
            return TRUE;
        }
        index = current->nextIndex;
    }
    return FALSE;
}
