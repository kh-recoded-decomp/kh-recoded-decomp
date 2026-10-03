#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[4];
    void *owner;
    u8 pad_08[0x50];
    s16 parentIndex;
} FieldObject;

extern FieldObject *func_ov001_0208635c(void *owner, int index);

static inline FieldObject *GetParentObject(FieldObject *object)
{
    return func_ov001_0208635c(object->owner, object->parentIndex);
}

FieldObject *FindRootObject_020a5124(FieldObject *object)
{
    while (object->parentIndex >= 0) {
        object = GetParentObject(object);
    }
    return object;
}
